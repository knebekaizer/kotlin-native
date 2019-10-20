#ifndef SIMD_WRAPPER_SIMD_LIB_H
#define SIMD_WRAPPER_SIMD_LIB_H

//#include <Accelerate/Accelerate.h>
//#include <simd/geometry.h>

//typedef struct VFloat {
//	float v[4];
//} VFloat;
//
//float distance(VFloat f0, VFloat f1);
//
//float foo(float x[4]);

//typedef float Float;
//void foo(Float f);

//typedef float xFloat[4];
//void bar(xFloat x);
//void bar(float x[4]) {
//	foo(x);
//}
//
//float dist_arr(xFloat a, xFloat b);

//typedef float vFloat __attribute__ ((__vector_size__ (16)));
//vFloat getVFloat(void);
//float my_simd_distance(vFloat f1, vFloat f2);

//typedef __attribute__((__ext_vector_type__(2))) float simd_float2; // doesn't work: not a native CXType_Vector
typedef __attribute__ ((__vector_size__ (8))) float simdFloat2;
simdFloat2 getSimd8(float f1, float f2);
float length(simdFloat2);

#endif //SIMD_WRAPPER_SIMD_LIB_H