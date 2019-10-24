import kotlinx.cinterop.*
import kotlin.test.*

import simd_wrapper.*



fun test_init() {
    var v1 = vectorOf(-1f, 0f, 0f, -7f)
    var v2 = vectorOf(1f, 4f, 3f, 7f);
    val len = my_simd_distance(v1, v2)
    println(len)
}


fun main() {

    val v = vectorOf(42f, 1f, 2f, 3f)
    printVFloat(v)
    v.set(-1f, 0f, 0f, -7f)
////    v[1] = 44f
    printVFloat(v)


//    test_16()
    test_init()
}
