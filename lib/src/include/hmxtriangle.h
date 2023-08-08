// hmxtriangle.h - Harmonix triangle struct
#ifndef HMXTRIANGLE_H
#define HMXTRIANGLE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"


typedef struct {
	u16 idx[3];
} HX_TRIANGLE;


HX_TRIANGLE hmx_triangle_load(FILE *file);
void hmx_triangle_print(HX_TRIANGLE triangle);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
