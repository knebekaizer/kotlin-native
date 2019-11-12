#ifndef SIMD_WRAPPER_SIMD_LIB_H
#define SIMD_WRAPPER_SIMD_LIB_H

#include <Accelerate/Accelerate.h>
#include <simd/geometry.h>


#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif

extern simd_int4 myVar4i32;

simd_quatf fun_simd_quatf();

float length(simd_float4 f);
simd_float4 vfadd(simd_float4 v1, simd_float4 v2);
simd_float4 vfsub(simd_float4 v1, simd_float4 v2);

float my_simd_distance(vFloat v1, vFloat v2);

#ifdef __cplusplus
}; // extern C {
#endif


#endif //SIMD_WRAPPER_SIMD_LIB_H