// hmxprimitive.h - Harmonix Primitives
#ifndef HMXPRIMITIVE_H
#define HMXPRIMITIVE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>


typedef struct {
	float x;
	float y;
	float z;
	float r;
} HX_SPHERE;


HX_SPHERE hmx_primitive_sphere_load(FILE *file);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
