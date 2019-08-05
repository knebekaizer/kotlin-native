	
	../../dist/bin/cinterop -def SkTime.def -o SkTime -compiler-options "-I/Users/vdi/work/cpptools/skia"

	g++ -std=c++14 main.cpp  -I/Users/vdi/work/cpptools/skia /Users/vdi/work/cpptools/skia/out/Static/libskia.a -framework CoreServices -framework CoreText -framework CoreGraphic
	
	../../dist/bin/kotlinc src/skiaMain/kotlin/sktimeSample.kt  -o sktimeSample.kt -l SkTime  -linker-options "/Users/vdi/work/cpptools/skia/out/Static/libskia.a"  -linker-options "-framework CoreServices" -linker-options "-framework CoreText" -linker-options "-framework CoreGraphic"
