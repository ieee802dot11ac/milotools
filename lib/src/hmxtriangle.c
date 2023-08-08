#include "hmxtriangle.h"
#include "iohelper.h"
#include <stdio.h>



HX_TRIANGLE hmx_triangle_load(FILE *file, bool isBigEndian)
{
	HX_TRIANGLE triangle;

	triangle.idx[0] = iohelper_read_u16_ve(file, isBigEndian);
	triangle.idx[1] = iohelper_read_u16_ve(file, isBigEndian);
	triangle.idx[2] = iohelper_read_u16_ve(file, isBigEndian);

	return triangle;
}

void hmx_triangle_print(HX_TRIANGLE triangle)
{
	printf("HXTriangle(%u, %u, %u)", triangle.idx[0],
					 triangle.idx[1],
					 triangle.idx[2]);
}
