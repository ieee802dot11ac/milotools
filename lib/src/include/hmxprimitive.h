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

typedef struct {
	float x;
	float y;
	float w;
	float h;
} HX_RECT;


HX_SPHERE hmx_primitive_sphere_load(FILE *file);
void hmx_primitive_sphere_print(HX_SPHERE sphere);

HX_RECT hmx_primitive_rect_load(FILE *file);
void hmx_primitive_rect_print(HX_RECT rect);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
