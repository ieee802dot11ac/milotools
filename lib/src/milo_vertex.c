#include "milo_vertex.h"
#include <stdio.h>


MILO_VERTEX milo_vertex_load(FILE *file)
{
	MILO_VERTEX vertex;
	fread(&vertex, 1, sizeof(MILO_VERTEX), file);

	return vertex;
}

void milo_vertex_print(MILO_VERTEX vertex)
{
	printf("MILOVertex(position=(%f, %f, %f), normal=(%f, %f, %f), color=(%f, %f, %f, %f), tex=(%f, %f))",
			vertex.x, vertex.y, vertex.z,
			vertex.normX, vertex.normY, vertex.normZ,
			vertex.r, vertex.g, vertex.b, vertex.a,
			vertex.u, vertex.v);
}
