import skia.sample.*
import kotlinx.cinterop.*

fun example(canvas: SkCanvas) {
    // TODO: need convenient constructors for managed classes
    val paint = nativeHeap.alloc<SkPaint>()

    canvas.clear(SK_ColorBLACK);

    for (i in 0..200) {
        for (j in 0..i) {
            canvas.drawPoint(i.toFloat(), j.toFloat(), paint.ptr);
        }
    }

    // TODO: need memory management.
    nativeHeap.free(paint)
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

        // TODO: get rid of memScoped
        memScoped {
            val out: SkFILEWStream = alloc<SkFILEWStream>() {
                // TODO: make convenient constructors
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

