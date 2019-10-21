#ifndef SIMD_WRAPPER_SIMD_LIB_H
#define SIMD_WRAPPER_SIMD_LIB_H

//#include <Accelerate/Accelerate.h>
//#include <simd/geometry.h>

//int foo(__int128_t);

float getDouble(double, double);

//typedef __attribute__((__ext_vector_type__(2))) float simd_float2; // doesn't work: not a native CXType_Vector
typedef __attribute__ ((__vector_size__ (8))) float simdFloat2;
simdFloat2 getSimd8(float f1, float f2);
float length(simdFloat2);

//typedef float                   vFloat          __attribute__ ((__vector_size__ (16)));
//vFloat getVFloat(float f0, float f1, float f2, float f3);
//float my_simd_distance(vFloat v1, vFloat v2);


#endif //SIMD_WRAPPER_SIMD_LIB_H