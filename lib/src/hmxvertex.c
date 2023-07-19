#include "hmxvertex.h"
#include <stdio.h>


HX_VERTEX_GH hmx_vertex_load(FILE *file)
{
	HX_VERTEX_GH vertex;
	fread(&vertex, sizeof(HX_VERTEX_GH), 1, file);

	return vertex;
}

void hmx_vertex_print(HX_VERTEX_GH vertex)
{
	printf("HXVertex(position=(%f, %f, %f), normal=(%f, %f, %f), color=(%f, %f, %f, %f), tex=(%f, %f))",
			vertex.x, vertex.y, vertex.z,
			vertex.normX, vertex.normY, vertex.normZ,
			vertex.r, vertex.g, vertex.b, vertex.a,
			vertex.u, vertex.v);
}
