package org.jetbrains.kotlin.backend.konan

import org.jetbrains.kotlin.backend.konan.ir.konanLibrary
import org.jetbrains.kotlin.cli.common.messages.CompilerMessageLocation
import org.jetbrains.kotlin.cli.common.messages.CompilerMessageSeverity
import org.jetbrains.kotlin.cli.common.messages.MessageCollector
import org.jetbrains.kotlin.ir.declarations.IrModuleFragment
import org.jetbrains.kotlin.konan.exec.Command
import org.jetbrains.kotlin.konan.file.*
import org.jetbrains.kotlin.konan.library.KonanLibrary
import org.jetbrains.kotlin.konan.library.impl.KonanLibraryImpl
import org.jetbrains.kotlin.konan.target.ClangArgs
import org.jetbrains.kotlin.konan.target.Family
import org.jetbrains.kotlin.konan.target.KonanTarget

internal class CStubsManager(val context: Context, private val target: KonanTarget) {

    // TODO: don't make IR visible here.
    val klibs: List<KonanLibrary>
        get() = context.irModules.map{ it.value.descriptor.konanLibrary }.filterIsInstance<KonanLibrary>()

    init {
        println("CREATED CStubsManager")
    }
    fun getUniqueName(prefix: String) = "$prefix${counter++}"

    fun addStub(kotlinLocation: CompilerMessageLocation?, lines: List<String>, klib: KonanLibrary?) {
        stubs += Stub(kotlinLocation, lines, klib)
    }

    fun compile(clang: ClangArgs, messageCollector: MessageCollector, verbose: Boolean): List<File> {
        if (stubs.isEmpty()) return emptyList()
        println("COMPILE CStubsManager: ${stubs.size} C stubs")
        stubs.forEach {
            println("C STUB for ${it.kotlinLocation}")
            println(it.lines.map{"\t$it"}.joinToString("\n"))
            println()
        }

        val klibStubIndex = stubs.groupBy { it.klib }

        klibStubIndex[null]?.forEach {
            println("NULL KLIB: ${it.lines.joinToString("\n")}")
        }

        val klibBitcodeIndex = mutableMapOf<KonanLibrary?, File>()

        klibStubIndex.keys.forEach { klib ->

            val compilerOptions = mutableListOf<String>()
            val sourceFileExtension = when {
                klib?.manifestProperties?.getProperty("language") == "C++" -> ".cpp"
                target.family.isAppleFamily -> {
                    compilerOptions += "-fobjc-arc"
                    ".m" // TODO: consider managing C and Objective-C stubs separately.
                }
                else -> ".c"
            }

            val preamble = klib?.preamblePath?.let { File(it) }?.readStrings() ?: emptyList()

            println("KLIB: $klib")
            println("AND ITS PREAMBLE:")
            println(preamble)
            println("AND ITS STUBS:")
            println((klibStubIndex[klib]!!.flatMap { it.lines }).map{"\t$it"}.joinToString("\n"))

            val cSource = createTempFile("cstubs", sourceFileExtension)//.deleteOnExit()
            cSource.writeLines(preamble + (klibStubIndex[klib]!!.flatMap { it.lines }))

            val bitcode = createTempFile("cstubs", ".bc")//.deleteOnExit()

            val cSourcePath = cSource.absolutePath
            println("C SOURCE: $cSourcePath")
            println("BRIDGE COMPILE: ")

            val clangCommand = clang.clangC(
                *compilerOptions.toTypedArray(), "-O2",
                cSourcePath, "-emit-llvm", "-c", "-o", bitcode.absolutePath
            ) + (klib?.manifestProperties?.getProperty("compilerOpts")?.split(" ") ?: emptyList()) // TODO: This is got get "-I"s
            println("BRIDGE COMPILE: ${clangCommand.joinToString(" ")}")

            val result = Command(clangCommand).getResult(withErrors = true)
            if (result.exitCode != 0) {
                reportCompilationErrors(cSourcePath, result, messageCollector, verbose)
            }

            klibBitcodeIndex.put(klib, bitcode)
        }
        return klibBitcodeIndex.values.toList()
    }

    private fun reportCompilationErrors(
            cSourcePath: String,
            result: Command.Result,
            messageCollector: MessageCollector,
            verbose: Boolean
    ): Nothing {
        val regex = Regex("${Regex.escape(cSourcePath)}:([0-9]+):[0-9]+: error: .*")
        val errorLines = result.outputLines.mapNotNull { line ->
            regex.matchEntire(line)?.let { matchResult ->
                matchResult.groupValues[1].toInt()
            }
        }

        val lineToStub = ArrayList<Stub>()
        stubs.forEach { stub ->
            repeat(stub.lines.size) { lineToStub.add(stub) }
        }

        val cSourceCopyPath = "cstubs.c"
        if (verbose) {
            File(cSourcePath).copyTo(File(cSourceCopyPath))
        }

        if (errorLines.isNotEmpty()) {
            errorLines.forEach {
                messageCollector.report(
                        CompilerMessageSeverity.ERROR,
                        "Unable to compile C bridge" + if (verbose) " at $cSourceCopyPath:$it" else "",
                        lineToStub[it - 1].kotlinLocation
                )
            }
        } else {
            messageCollector.report(
                    CompilerMessageSeverity.ERROR,
                    "Unable to compile C bridges",
                    null
            )
        }

        throw KonanCompilationException()
    }

    private val stubs = mutableListOf<Stub>()
    private class Stub(val kotlinLocation: CompilerMessageLocation?, val lines: List<String>, val klib: KonanLibrary?)
    private var counter = 0
}