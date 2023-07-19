#include "hmxmatrix.h"
#include <stdio.h>

HX_MATRIX hmx_matrix_load(FILE *file)
{
	HX_MATRIX matx;
	fread(&matx, sizeof(float), 12, file);
	return matx;
}

void hmx_matrix_print(HX_MATRIX mtx)
{
	// Matrix indexing notation in math is typically A_yx, A being your
	// matrix, y and x being positions in the matrix starting at the top
	// left.
	printf("[%f %f %f][%f %f %f][%f %f %f][%f %f %f]",
		mtx.v11, mtx.v12, mtx.v13,
		mtx.v21, mtx.v22, mtx.v23,
		mtx.v31, mtx.v32, mtx.v33,
		mtx.v41, mtx.v42, mtx.v43);
}
