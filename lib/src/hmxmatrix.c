#include "hmxmatrix.h"
#include "iohelper.h"
#include <stdio.h>

HX_MATRIX hmx_matrix_load(FILE *file, bool isBigEndian)
{
	HX_MATRIX mtx;
	// i'm sorry the code duplication was bothering me, especially with isBigEndian too
#define _MATREAD(x) mtx.v##x = iohelper_read_f32_ve(file, isBigEndian)
	_MATREAD(11); _MATREAD(12); _MATREAD(13);
	_MATREAD(21); _MATREAD(22); _MATREAD(23);
	_MATREAD(31); _MATREAD(32); _MATREAD(33);
	_MATREAD(41); _MATREAD(42); _MATREAD(43);
#undef _MATREAD
	return mtx;
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

bool hmx_matrix_write(FILE *file, HX_MATRIX mtx, bool isBigEndian)
{
	// i'm sorry the code duplication was bothering me, especially with isBigEndian too
#define _MATWRITE(x) iohelper_write_f32_ve(file, mtx.v##x, isBigEndian)
	_MATWRITE(11); _MATWRITE(12); _MATWRITE(13);
	_MATWRITE(21); _MATWRITE(22); _MATWRITE(23);
	_MATWRITE(31); _MATWRITE(32); _MATWRITE(33);
	_MATWRITE(41); _MATWRITE(42); _MATWRITE(43);
#undef _MATWRITE
	return true;
}
