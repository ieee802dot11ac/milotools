#include "hmxvertex.h"
#include <stdio.h>


HX_VERTEX hmx_vertex_load(FILE *file)
{
	HX_VERTEX vertex;
	fread(&vertex, 1, sizeof(HX_VERTEX), file);

	return vertex;
}
