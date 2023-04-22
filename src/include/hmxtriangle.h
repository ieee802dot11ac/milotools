// hmxtriangle.h - Harmonix triangle struct
#ifndef HMXTRIANGLE_H
#define HMXTRIANGLE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"


typedef struct {
	u16 vert[3];
} HX_TRIANGLE;


HX_TRIANGLE hmx_triangle_load(FILE *file);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
