import kotlinx.cinterop.*
import kotlin.test.*

import simd_wrapper.*

/*
fun test_struct() {
    memScoped {
        val p0 = alloc<VFloat>()
        p0.v[0] = 0f
        p0.v[1] = 0f
        val p1 = alloc<VFloat>()
        p1.v[0] = 3f
        p1.v[1] = 4f
        val dist = distance(p0.readValue(), p1.readValue())
        println("dist = $dist")
    }
}
*/

/*
fun test_wrapper() {
    memScoped {
        val p0 = alloc<VectorVar>()
        p0.v[0] = 0f
        p0.v[1] = 0f
        val p1 = alloc<VectorVar>()
        p1.v[0] = 12f
        p1.v[1] = 16f
        val dist = my_simd_distance(p0.v, p1.v)
        println("dist = $dist")

    }
}
*/

fun test_builtin() {
    val v = getSimd8(3f, 4f)
    val len = length(v)
    println(len)
}

//fun test_array1() {
//    memScoped {
//        val p0 = floatArrayOf(0f, 0f, 0f, 0f)
//        val p1 = floatArrayOf(3f, 4f, 0f, 0f)
//        val dist = dist_arr(p0.toCValues().getPointer(memScope), p1.toCValues().getPointer(memScope))
//        println("dist_arr = $dist")
//    }
//}

//fun test_array2() {
//    memScoped {
//        val p0 = floatArrayOf(0f, 0f, 0f, 0f)
//        val p1 = floatArrayOf(3f, 4f, 0f, 0f)
//        val dist = my_simd_distance(p0.toCValues().getPointer(memScope), p1.toCValues().getPointer(memScope))
//        println("dist = $dist")
//    }
//}

fun main() {

    test_builtin()


//
//    memScoped {
//        val q0 = alloc<vFloat>()
//        q0[0] = 0f
//        q0[1] = 0f
//        val p1 = alloc<vFloat>()
//        q1[0] = 3f
//        q1[1] = 4f
//        val dist = simd_distance(p0.readValue(), p1.readValue())
//        println("dist = $dist")
//    }

}
