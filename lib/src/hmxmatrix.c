#include "hmxmatrix.h"
#include "iohelper.h"
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

bool hmx_matrix_write(FILE *file, HX_MATRIX mtx)
{
	iohelper_write_f32(file, mtx.v11); iohelper_write_f32(file, mtx.v12); iohelper_write_f32(file, mtx.v13);
	iohelper_write_f32(file, mtx.v21); iohelper_write_f32(file, mtx.v22); iohelper_write_f32(file, mtx.v23);
	iohelper_write_f32(file, mtx.v31); iohelper_write_f32(file, mtx.v32); iohelper_write_f32(file, mtx.v33);
	iohelper_write_f32(file, mtx.v41); iohelper_write_f32(file, mtx.v42); iohelper_write_f32(file, mtx.v43);
	return true;
}
