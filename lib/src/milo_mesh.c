#include "milo_mesh.h"
#include "milo_common.h"
#include "milo_string.h"
#include "milo_transform.h"
#include "milo_vertex.h"
#include "iohelper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

MILO_MESH_FILE_GH milo_mesh_load(FILE *file)
{
	MILO_MESH_FILE_GH mesh;
	mesh.version = iohelper_readu32(file);

	mesh.transform = milo_transform_load(file);
	mesh.bounding = milo_primitive_sphere_load(file);

	for (u32 i = 0; i < 9; ++i)
		mesh._unknown0[i] = iohelper_readu8(file);

	mesh.matName = milo_string_load(file);
	mesh.geometryOwner = milo_string_load(file);

	mesh.mutableParts = iohelper_readu32(file);
	mesh.volume = iohelper_readu32(file);

	mesh.bsp = iohelper_readu8(file);

	mesh.vertCount = iohelper_readu32(file);
	mesh.vertTable = malloc(sizeof(MILO_VERTEX) * mesh.vertCount);
	assert (mesh.vertTable != NULL);
	for (u32 i = 0; i < mesh.vertCount; ++i)
		mesh.vertTable[i] = milo_vertex_load(file);

	mesh.triCount = iohelper_readu32(file);
	mesh.triTable = malloc(sizeof(MILO_VERTEX) * mesh.triCount);
	assert (mesh.triTable != NULL);
	for (u32 i = 0; i < mesh.triCount; ++i)
		mesh.triTable[i] = milo_triangle_load(file);

	for (u32 i = 0; i < 16 * 4; ++i)
		mesh._unknown1[i] = iohelper_readu8(file);
	return mesh;
}

void milo_mesh_print(MILO_MESH_FILE_GH mesh)
{
	printf("VERSION: %u\n", mesh.version);

	puts("TRANSFORM: {");
	milo_transform_print(mesh.transform);
	puts("}");

	fputs("BOUNDING: ", stdout);
	milo_primitive_sphere_print(mesh.bounding);

	fputs("_unknown0: [", stdout);
	for (u32 i = 0; i < 9; ++i) {
		printf("%u", mesh._unknown0[i]);
		if (i != 8)
			fputs(", ", stdout);
	}
	puts("]");

	fputs("MATERIAL: ", stdout);
	milo_string_print(mesh.matName);
	putchar('\n');

	fputs("GEOMETRY_OWNER: ", stdout);
	milo_string_print(mesh.geometryOwner);
	putchar('\n');

	printf("MUTABLE_PARTS: %s\n", MUTABLE_ENUM_name(mesh.mutableParts));
	printf("VOLUME: %s\n", VOLUME_ENUM_NAME[mesh.volume]);

	printf("BSP: %u\n", mesh.bsp);

	fputs("VERTICES: [", stdout);
	for (u32 i = 0; i < mesh.vertCount; ++i) {
		milo_vertex_print(mesh.vertTable[i]);
		if (i != mesh.vertCount - 1)
			fputs(", ", stdout);
	}
	puts("]");

	fputs("TRIANGLES: [", stdout);
	for (u32 i = 0; i < mesh.triCount; ++i) {
		milo_triangle_print(mesh.triTable[i]);
		if (i != mesh.triCount - 1)
			fputs(", ", stdout);
	}
	puts("]");

	fputs("_unknown1: [", stdout);
	for (u32 i = 0; i < 16*4; ++i) {
		printf("%u", mesh._unknown1[i]);
		if (i != 16*4-1)
			fputs(", ", stdout);
	}
	puts("]");
}

char const *const VOLUME_ENUM_NAME[VOLUME_ENUM_AMOUNT] = {
	"VolumeEmpty",
	"VolumeTriangles",
	"VolumeBSP",
	"VolumeBox",
};
