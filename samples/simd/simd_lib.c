#include "simd_lib.h"
#include <Accelerate/Accelerate.h>
#include <simd/geometry.h>


#include <stdio.h>

float distance(VFloat a, VFloat b) {
//	float dist = simd_distance(*(vFloat*)&a.v[0], *(vFloat*)&b.v[0]);
//    fprintf(stderr, "distance> ( (%f, %f), (%f, %f) ) = %f!\n", a.v[0], a.v[1], b.v[0], b.v[1], dist);
//
//	VFloat c = a;
//	VFloat d = b;
//	float dd = simd_distance(*(vFloat*)&c.v[0], *(vFloat*)&d.v[0]);
//    fprintf(stderr, "distance> ( (%f, %f), (%f, %f) ) = %f!\n", c.v[0], c.v[1], d.v[0], d.v[1], dd);

 	float dist = simd_distance(*(vFloat*)&a, *(vFloat*)&b);
    fprintf(stderr, "distance> ( (%f, %f), (%f, %f) ) = %f!\n", a.v[0], a.v[1], b.v[0], b.v[1], dist);
    return dist;
}

float dist_arr(xFloat a, xFloat b) {
    fprintf(stderr, "dist_arr> ( (%f, %f), (%f, %f) )\n", a[0], a[1], b[0], b[1]);

	fprintf(stderr, "dist_arr> addr = %p, %p; align = %d, %d\n", a, b, ((int)a)&15, ((int)b)&15);
 	vFloat x, y;
    fprintf(stderr, "dist_arr> addr = %p, %p; align = %d, %d\n", &x, &y, ((int)&x)&15, ((int)&y)&15);
	memcpy(&x, a, sizeof(x));
	memcpy(&y, b, sizeof(y));
    fprintf(stderr, "dist_arr> ( (%f, %f) )\n", x[0], x[1]);

// 	float dist = simd_distance(*(vFloat*)a, *(vFloat*)b);
 	float dist = simd_distance(x, y);
    fprintf(stderr, "dist_arr> ( (%f, %f), (%f, %f) ) = %f\n", a[0], a[1], b[0], b[1], dist);
    return dist;
}

float my_simd_distance(vFloat a, vFloat b) {
	float dist = simd_distance(a, b);
	fprintf(stderr, "simd_distance( (%f, %f), (%f, %f) ) = %f\n", a[0], a[1], b[0], b[1], dist);
	return dist;
}

float foo(float x[4]) {
	fprintf(stderr, "foo> (%f, %f)\n", x[0], x[1]);
	return x[0];
}

//float str(struct Str* s) {
//	return 42.42;
//}

#ifdef MAIN

void t1() {
	VFloat a = { {0, 0} };
	VFloat b = { {300, 400} };
	float d1 = simd_distance(*(vFloat*)&a, *(vFloat*)&b);
    fprintf(stderr, "simd_distance( (%f, %f), (%f, %f) ) = %f!\n", a.v[0], a.v[1], b.v[0], b.v[1], d1);

	float d2 = distance(a, b);
    fprintf(stderr, "simd_distance( (%f, %f), (%f, %f) ) = %f!\n", a.v[0], a.v[1], b.v[0], b.v[1], d2);

}

void t2() {
	xFloat a = {0, 0};
	xFloat b = {300, 400};
	float d1 = dist_arr(a, b);
    fprintf(stderr, "t2( (%f, %f), (%f, %f) ) = %f!\n", a[0], a[1], b[0], b[1], d1);
}

int main(void) {
	vFloat a;
	vFloat b = {3, 4};
	float dist = simd_distance(a, b);
    fprintf(stderr, "simd_distance( (%f, %f), (%f, %f) ) = %f!\n", a[0], a[1], b[0], b[1], dist);

	t1();
	t2();

	xFloat x = {1,2,3,4};
	foo(x);
	return 0;
}

#endif
