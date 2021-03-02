
# To draw a somple picture

cinterop -def samples/skia/Canvas.def -o Canvas -compiler-options "-I$SKIAHOME"

konanc samples/skia/src/skiaMain/kotlin/Picture.kt -l Canvas 

./program.kexe

You've got a picture.png


# More samples

   g++ -std=c++14 main.cpp  -I$HOME/work/cpptools/skia /Users/vdi/work/cpptools/skia/out/Static/libskia.a -framework CoreServices -framework CoreText -framework CoreGraphics
	
	../../dist/bin/cinterop -def Skia.def -o Skia -compiler-options "-I/Volumes/vdi/work/cpptools/skia"

	../../dist/bin/kotlinc src/skiaMain/kotlin/test_SkString.kt  -o test_SkString -l Skia  -linker-options "$HOME/work/cpptools/skia/out/Static/libskia.a"  -linker-options "-framework CoreServices" -linker-options "-framework CoreText" -linker-options "-framework CoreGraphics"
