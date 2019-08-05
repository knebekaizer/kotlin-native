import kotlinx.cinterop.*
import SkTime.*

fun main() {
    println("Skia sample")
    println("${SkTime.GetNSecs()}")
    println("${SkTime.GetNSecs()}")
    println("${SkTime.GetNSecs()}")
}

fun test_GetDateTime() {
    memScoped {
        val dateTime = alloc<SkTime__DateTime>()
    }

}