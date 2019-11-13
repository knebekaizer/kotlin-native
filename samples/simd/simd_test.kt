import kotlinx.cinterop.*
import kotlin.test.*

import simd_wrapper.*

import platform.Accelerate.*
import platform.darwin.*


// Custom print
fun Vector128.toStringHex(): String {
    return "0x" + (0 until 16).map { getByteAt(it).toString(16) }.joinToString("")
}

// Custom print
fun Vector128.toStringFloat(): String {
    return "(${(0 until 4).map { getFloatAt(it).toString() }.joinToString(", ")})"
}


fun main() {

    // Use interop types and variables:
    println(myVar4i32)
    myVar4i32 = vectorOf(2, 12, 850, 6)
    println(myVar4i32)
    println( myVar4i32.toStringHex() )

    // Using library function (MacOS Accelerate framework)
    val sum = vS128Add(vectorOf(1,2,3,4), vectorOf(4,3,2,1))
    println(sum)

    var v1 = vectorOf(-1f, 0f, 0f, -7f)
    var v2 = vectorOf(1f, 4f, 3f, 7f)
    println("length(vfsub(v1, v2)) = ${length(vfsub(v1, v2))}")

    val f2 = vectorOf(1f, 3.162f, 10f, 31f)
    println(f2.getFloatAt(1))
    println(f2.getIntAt(0))
    println(f2.getByteAt(3))

    println("vlog10f($f2) = ${vlog10f(f2).toStringFloat()}")

    // Try equality
    var x1 = vectorOf(-1f, 0f, 0f, -7f)
    var x2 = vectorOf(1f, 4f, 3f, 7f)
    println("(x1 == x2) is ${(x1 == x2)}")
    x1 = x2
    println("Now (x1 == x1) is ${(x1 == x1)}")

    // try Accelerate framework
    val q = vectorOf(1f, 9f, 25f, 49f)
    val sq = vsqrtf(q)
    println("vsqrtf$q = ${sq.toStringFloat()}")

    try {
        println(myVar4i32.getIntAt(4))
        println("FAILED")
    } catch (e: IndexOutOfBoundsException) {
        println("Handling $e")
    }

}
