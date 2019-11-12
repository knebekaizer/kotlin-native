#include "simd_lib.h"
#include <Accelerate/Accelerate.h>
#include <simd/simd.h>

#include <stdio.h>


simd_int4 myVar4i32 = {1, 4, 9, 25};


float length(simd_float4 f) {
    return simd_length(f);
}

simd_float4 vfadd(simd_float4 v1, simd_float4 v2) {
	return v1 + v2;
}

simd_float4 vfsub(simd_float4 v1, simd_float4 v2) {
	return v1 - v2;
}

float my_simd_distance(vFloat v1, vFloat v2) {
	return simd_distance(v1, v2);
}


#ifdef MAIN

#include <iostream>
using namespace std;


ostream& operator<<(ostream& os, vFloat v) {
	return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

int main(void) {

	vFloat v1 = {-1,0,0,-7};
	vFloat v2 = {1,4,3,7};
	auto vSum = v1 + v2;
	cerr << "vSum" << vSum << endl;

	auto d2 = (v2 -v1) * (v2 -v1);
	auto norm = sqrt(d2[0] + d2[1] + d2[2] + d2[3]);
	cerr << "norm = " << norm << endl;

	float dist = my_simd_distance(v1, v2);

	vFloat f = {0.1, 1.3, 2.6, 3.8};
	vFloat ceil = vceilf(f);
	cerr << "ceil" << ceil << endl;

	vFloat f2 = {1, 3.162, 10, 31};
//	vFloat lg = vlog10f(f2);

	return 0;
}

#endif
