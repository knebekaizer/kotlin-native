#include "simd_lib.h"
#include <Accelerate/Accelerate.h>
#include <simd/simd.h>


#include <stdio.h>
//typedef __attribute__((__ext_vector_type__(2))) float simd_float2
simd_float2 getSimd8(float f1, float f2) {
	simd_float2 f = {f1, f2};
	return f;
}

float length(simd_float2 f) {
    fprintf(stderr, "length> (%f, %f)\n", f[0], f[1]);
	float len = simd_length((simd_float2)f);
    fprintf(stderr, "length(%f, %f) = %f!\n", f[0], f[1], len);
    return len;
}


//float foo(float x[4]) {
//	fprintf(stderr, "foo> (%f, %f)\n", x[0], x[1]);
//	return x[0];
//}

//float str(struct Str* s) {
//	return 42.42;
//}

#ifdef MAIN

int main(void) {
	length( getSimd8(3, 4) );
//	vFloat a;
//	vFloat b = {3, 4};
//	float dist = simd_distance(a, b);
//    fprintf(stderr, "simd_distance( (%f, %f), (%f, %f) ) = %f!\n", a[0], a[1], b[0], b[1], dist);
//
//	t1();
//	t2();
//
//	xFloat x = {1,2,3,4};
//	foo(x);
	return 0;
}

#endif
