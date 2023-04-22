#include "hmxmesh.h"
#include "iohelper.h"
#include <stdio.h>

HX_MESH_FILE_GH hmx_mesh_load(FILE *file)
{
	HX_MESH_FILE_GH mesh;
	mesh.version = iohelper_readu32(file);
	mesh.transform = hmx_transform_load(file);
	return mesh;
}

void hmx_mesh_print(HX_MESH_FILE_GH meshData)
{
	printf("VERSION: %u\n", meshData.version);
	puts("TRANSFORM:{");
	hmx_transform_print(meshData.transform);
	puts("}");
	//puts("BOUNDING:");
}
