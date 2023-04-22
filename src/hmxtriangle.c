#include "hmxtriangle.h"
#include <stdio.h>



HX_TRIANGLE hmx_triangle_load(FILE *file)
{
	HX_TRIANGLE triangle;
	fread(&triangle, 1, sizeof(HX_TRIANGLE), file);

	return triangle;
}
