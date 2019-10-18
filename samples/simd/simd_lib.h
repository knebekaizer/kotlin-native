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
//
typedef float Float;
void foo(Float f);

//typedef float xFloat[4];
//void bar(xFloat x);
//void bar(float x[4]) {
//	foo(x);
//}
//
//float dist_arr(xFloat a, xFloat b);

typedef float vFloat __attribute__ ((__vector_size__ (16)));
float my_simd_distance(vFloat f1, vFloat f2);


#endif //SIMD_WRAPPER_SIMD_LIB_H