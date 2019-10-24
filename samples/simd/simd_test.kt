import kotlinx.cinterop.*
import kotlin.test.*

import simd_wrapper.*



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
}
