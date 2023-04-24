#include "hmxmatrix.h"
#include <stdio.h>

HX_MATRIX hmx_matrix_load(FILE *file)
{
	HX_MATRIX matx;
	fread(&matx, sizeof(float), 12, file);
	return matx;
}

void hmx_matrix_print(HX_MATRIX matx)
{
	// Matrix indexing notation in math is typically A_yx, A being your
	// matrix, y and x being positions in the matrix starting at the top
	// left.
	printf("[%f %f %f][%f %f %f][%f %f %f][%f %f %f]",
		matx.v11, matx.v12, matx.v13,
		matx.v21, matx.v22, matx.v23,
		matx.v31, matx.v32, matx.v33,
		matx.v41, matx.v42, matx.v43);
}
