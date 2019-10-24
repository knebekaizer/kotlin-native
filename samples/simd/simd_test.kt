import kotlinx.cinterop.*
import kotlin.test.*

import simd_wrapper.*

import kotlin.math.*
import platform.Accelerate.*

fun test_dist() {
    var v1 = vectorOf(-1f, 0f, 0f, -7f)
    var v2 = vectorOf(1f, 4f, 3f, 7f);
    val len = my_simd_distance(v1, v2)
    println(len)
}


fun main() {

    val v = vectorOf(42f, 1f, 2f, 3f)
    printVFloat(v)

    test_dist()

    val ln = kotlin.math.ln(2.718)
    println("log(2.718) = $ln")

    val f2 = vectorOf(1f, 3.162f, 10f, 31f)
    val lg = vlog10f(f2)
    printVFloat(lg)
}
