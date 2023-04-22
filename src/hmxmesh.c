#include "hmxmesh.h"
#include "common.h"
#include "hmxreference.h"
#include "hmxtransform.h"
#include "hmxvertex.h"
#include "iohelper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

HX_MESH_FILE_GH hmx_mesh_load(FILE *file)
{
	HX_MESH_FILE_GH mesh;
	mesh.version = iohelper_readu32(file);

	mesh.transform = hmx_transform_load(file);
	mesh.bounding = hmx_primitive_sphere_load(file);

	for (u32 i = 0; i < 9; ++i)
		mesh._unknown0[i] = iohelper_readu8(file);

	mesh.matName = hmx_reference_load(file);
	mesh.geometryOwner = hmx_reference_load(file);

	mesh.mutableParts = iohelper_readu32(file);
	mesh.volume = iohelper_readu32(file);

	mesh.bsp = iohelper_readu8(file);

	mesh.vertCount = iohelper_readu32(file);
	mesh.vertTable = malloc(sizeof(HX_VERTEX) * mesh.vertCount);
	assert (mesh.vertTable != NULL);
	for (u32 i = 0; i < mesh.vertCount; ++i)
		mesh.vertTable[i] = hmx_vertex_load(file);

	mesh.triCount = iohelper_readu32(file);
	mesh.triTable = malloc(sizeof(HX_VERTEX) * mesh.triCount);
	assert (mesh.triTable != NULL);
	for (u32 i = 0; i < mesh.triCount; ++i)
		mesh.triTable[i] = hmx_triangle_load(file);

	for (u32 i = 0; i < 16 * 4; ++i)
		mesh._unknown1[i] = iohelper_readu8(file);
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
