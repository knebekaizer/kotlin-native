import kotlinx.cinterop.*
import kotlin.test.*

import union.*


fun main() {
    val x = retByValue()
            .useContents{
                println("x.first = ${first.toChar()}")
                println("x.a = [${a[0]}, ${a[1]}]")
                println("b1 = ${b1.toString(16)}")
                println("x.last = ${last.toChar()}")
            }
}