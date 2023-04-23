// milo_primitive.h - Milo Primitives
#ifndef MILO_PRIMITIVE_H
#define MILO_PRIMITIVE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>


typedef struct {
	float x;
	float y;
	float z;
	float r;
} MILO_SPHERE;


MILO_SPHERE milo_primitive_sphere_load(FILE *file);
void milo_primitive_sphere_print(MILO_SPHERE sphere);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
