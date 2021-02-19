import skia.sample.*
import kotlinx.cinterop.*

fun example(canvas: SkCanvas) {

    val paint: SkPaint = SkPaint()
    paint.setColor(SK_ColorGREEN)

    canvas.clear(SK_ColorRED);

    for (i in 0..200) {
        for (j in 0..i) {
            // TODO: get rid of `.pointed` dereference
            canvas.drawPoint(i.toFloat(), j.toFloat(), paint.ptr);
        }
    }

    // TODO: need memory management.
    // nativeHeap.free(paint)
}

fun raster(width: Int, height: Int, path: String) {

        val rasterSurface: SkSurface = SkSurface.MakeRasterN32Premul(width, height, null)
            ?: error("No surface")

        // TODO: get rid of `.pointed` dereference
        val rasterCanvas: SkCanvas = rasterSurface.getCanvas()?.pointed 
            ?: error("Could not get canvas")

        example(rasterCanvas)

        val img = rasterSurface.makeImageSnapshot()
            ?: error("no snapshot")
        val png = img.encodeToData()
            ?: error("no data")

   
        val out2 = SkFILEWStream(path.cstr)
        out2.write(png.data(), png.size())
}


fun main() {
    val fileName = "picture.png"
    raster(640, 480, fileName)
    println("Look at $fileName")
}

