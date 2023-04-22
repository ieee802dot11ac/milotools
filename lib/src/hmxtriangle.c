#include "hmxtriangle.h"
#include <stdio.h>



HX_TRIANGLE hmx_triangle_load(FILE *file)
{
	HX_TRIANGLE triangle;
	fread(&triangle, 1, sizeof(HX_TRIANGLE), file);

	return triangle;
}

void hmx_triangle_print(HX_TRIANGLE triangle)
{
	printf("HXTriangle(%u, %u, %u)", triangle.vert[0],
					 triangle.vert[1],
					 triangle.vert[2]);
}
