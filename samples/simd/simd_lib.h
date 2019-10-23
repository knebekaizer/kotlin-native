#ifndef SIMD_WRAPPER_SIMD_LIB_H
#define SIMD_WRAPPER_SIMD_LIB_H

//#include <Accelerate/Accelerate.h>
//#include <simd/geometry.h>

//int foo(__int128_t);

#include <inttypes.h>

typedef double d16_t;
void setDouble(d16_t);

//typedef __attribute__ ((__vector_size__ (8))) float simdFloat2;
//simdFloat2 getSimd8(float f1, float f2);
//float length(simdFloat2);

typedef float                   vFloat          __attribute__ ((__vector_size__ (16)));

void Kotlin_Vector_set(vFloat* thiz, uint32_t index, float value);

void printVFloat(vFloat v);
vFloat getVFloat(float f0, float f1, float f2, float f3);
float my_simd_distance(vFloat v1, vFloat v2);


#endif //SIMD_WRAPPER_SIMD_LIB_H