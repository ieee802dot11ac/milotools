// milo_triangle.h - Harmonix triangle struct
#ifndef MILO_TRIANGLE_H
#define MILO_TRIANGLE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "milo_common.h"


typedef struct {
	u16 vert[3];
} MILO_TRIANGLE;


MILO_TRIANGLE milo_triangle_load(FILE *file);
void milo_triangle_print(MILO_TRIANGLE triangle);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
