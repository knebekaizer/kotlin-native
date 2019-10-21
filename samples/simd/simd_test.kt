import kotlinx.cinterop.*
import kotlin.test.*

import simd_wrapper.*


fun test_8() {
    val v = getSimd8(3f, 4f)
    val len = length(v)
    println(len)
}

//fun test_16() {
//    var v1 = getVFloat(-1f, 0f, 0f, -7f); //  {-1,0,0,-7};
//    var v2 = getVFloat(1f, 4f, 3f, 7f);
//    val len = my_simd_distance(v1, v2)
//    println(len)
//}


fun main() {

//    test_16()
    test_8()

    val x = getDouble(42.0, 1.0)

}
