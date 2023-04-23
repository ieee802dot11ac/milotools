#include "milo_triangle.h"
#include <stdio.h>



MILO_TRIANGLE milo_triangle_load(FILE *file)
{
	MILO_TRIANGLE triangle;
	fread(&triangle, 1, sizeof(MILO_TRIANGLE), file);

	return triangle;
}

void milo_triangle_print(MILO_TRIANGLE triangle)
{
	printf("MILOTriangle(%u, %u, %u)", triangle.vert[0],
					   triangle.vert[1],
					   triangle.vert[2]);
}
