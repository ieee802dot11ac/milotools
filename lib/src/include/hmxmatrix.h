// hmxmatrix.h - Harmonix transform matrix
#ifndef HMXMATRIX_H
#define HMXMATRIX_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef struct {
	float v11, v12, v13;
	float v21, v22, v23;
	float v31, v32, v33;
	float v41, v42, v43;
} HX_MATRIX;

HX_MATRIX hmx_matrix_load(FILE *file);
void hmx_matrix_print(HX_MATRIX matx);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
