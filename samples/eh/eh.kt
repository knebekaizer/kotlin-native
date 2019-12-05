// ../../dist/bin/kotlinc -o eh -l eh -linker-options _build/CMakeFiles/eh.dir/main.cpp.o eh.kt && ./eh.kexe
import kotlinx.cinterop.*
import eh.*

fun foo(): Int {
    exc_throw()
    println("Greetings from kotlin!")
    return 0
}

fun main() {
//    foo()
//    exc_wrapper(staticCFunction(::exc_throw))
    exc_wrapper(staticCFunction(::foo))
}
