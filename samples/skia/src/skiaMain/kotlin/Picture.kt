import skia.sample.*
import kotlinx.cinterop.*

fun example(canvas: SkCanvas) {
    memScoped {
        val paint = alloc<SkPaint>()

        canvas.clear(SK_ColorBLACK);

        for (i in 0..200) {
            for (j in 0..i) {
                canvas.drawPoint(i.toFloat(), j.toFloat(), paint.ptr);
            }
        }
    }
}

fun raster(width: Int, height: Int, path: String) {

        val rasterSurface: SkSurface = SkSurface.MakeRasterN32Premul(width, height, null)?.pointed 
            ?: error("No surface")
        val rasterCanvas: SkCanvas = rasterSurface.getCanvas()?.pointed 
            ?: error("Could not get canvas")

        example(rasterCanvas)

        val img = rasterSurface.makeImageSnapshot()?.pointed 
            ?: error("no snapshot")
        val png = img.encodeToData()?.pointed 
            ?: error("no data")

        memScoped {
            val out: SkFILEWStream = alloc<SkFILEWStream>() {
                SkFILEWStream.__init__(ptr, path.cstr)
            }
            out.write(png.data(), png.size())
        }
}


fun main() {
    val fileName = "picture.png"
    raster(640, 480, fileName)
    println("Look at $fileName")
}

