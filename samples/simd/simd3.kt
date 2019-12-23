import kotlinx.cinterop.*
import simd.*


// Custom print
fun Vector128.toStringHex(): String {
    return "0x" + (0 until 16).map { getUByteAt(it).toString(16) }.joinToString("")
}

// Custom print
fun Vector128.toStringFloat(): String {
    return "(${(0 until 4).map { getFloatAt(it).toString() }.joinToString(", ")})"
}


fun main() {

    val z = getZZZ()
    println("foo(z) = ${foo(z)}")
}
