#include "hmxmesh.h"
#include "hmxcommon.h"
#include "hmxdraw.h"
#include "hmxmeshpart.h"
#include "hmxmatrix.h"
#include "hmxstring.h"
#include "hmxtransform.h"
#include "hmxtriangle.h"
#include "hmxvertex.h"
#include "iohelper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// #define MESH_VERBOSE_TRIANGLE_PARTS
// #define MESH_VERBOSE_VERTEX_PARTS

HX_MESH hmx_mesh_load(FILE *file)
{
	HX_MESH mesh;
	mesh.version = iohelper_read_u32(file);
	mesh.transform = hmx_transform_load(file);
	mesh.draw = hmx_draw_load(file);

	mesh.matPath = hmx_string_load(file);
	mesh.geometryOwner = hmx_string_load(file);

	mesh.mutableParts = iohelper_read_u32(file);
	mesh.volume = iohelper_read_u32(file);

	mesh.bsp = iohelper_read_u8(file);

	mesh.vertCount = iohelper_read_u32(file);
	mesh.vertTable = malloc(sizeof(HX_VERTEX) * mesh.vertCount);
	assert (mesh.vertTable != NULL);
	for (u32 i = 0; i < mesh.vertCount; ++i)
		mesh.vertTable[i] = hmx_vertex_load(file);

	mesh.triCount = iohelper_read_u32(file);
	mesh.triTable = malloc(sizeof(HX_VERTEX) * mesh.triCount);
	assert (mesh.triTable != NULL);
	for (u32 i = 0; i < mesh.triCount; ++i)
		mesh.triTable[i] = hmx_triangle_load(file);

	mesh.partCount = iohelper_read_u32(file);
	mesh.partTriCounts = malloc(sizeof(u8) * mesh.partCount);
	u32 shouldMatchTris = 0;
	for (u32 i = 0; i < mesh.partCount; ++i) {
		mesh.partTriCounts[i] = iohelper_read_u8(file);
		shouldMatchTris += mesh.partTriCounts[i];
	}

	if (shouldMatchTris != mesh.triCount)
		warn("Group sizes sum does not match # of triangles in mesh!");

	mesh.charCount = iohelper_read_u32(file);
	if (mesh.charCount != 0) {
		for (u32 i = 0; i < 4; ++i)
			mesh.bones[i] = hmx_string_load(file);

		for (u32 i = 0; i < 4; ++i)
			mesh.boneTransforms[i] = hmx_matrix_load(file);
	} else {
		for (u32 i = 0; i < 4; ++i) {
			mesh.bones[i] = (HX_STRING) { .value = NULL, .length = 0 };
			mesh.boneTransforms[i] = (HX_MATRIX) { 0 };
		}

	}

	mesh.parts = malloc(sizeof(HX_MESHPART) * mesh.partCount);
	for (u32 i = 0; i < mesh.partCount; ++i) {
		mesh.parts[i].faceCount = iohelper_read_u32(file);
		mesh.parts[i].vertexCount = iohelper_read_u32(file);

		mesh.parts[i].faces = malloc(sizeof(u32) * mesh.parts[i].faceCount);
		assert(mesh.parts[i].faces != NULL);
		mesh.parts[i].vertices = malloc(sizeof(u16) * mesh.parts[i].vertexCount);
		assert(mesh.parts[i].vertices != NULL);

		for (u32 si = 0; si < mesh.parts[i].faceCount; ++si)
			mesh.parts[i].faces[si] = iohelper_read_u32(file);
		for (u32 vi = 0; vi < mesh.parts[i].vertexCount; ++vi)
			mesh.parts[i].vertices[vi] = iohelper_read_u16(file);
	}

	return mesh;
}

void hmx_mesh_cleanup(HX_MESH mesh)
{
	hmx_transform_cleanup(mesh.transform);
	hmx_draw_cleanup(mesh.draw);
	hmx_string_cleanup(mesh.matPath);
	hmx_string_cleanup(mesh.geometryOwner);

	free(mesh.vertTable);
	free(mesh.triTable);
	free(mesh.partTriCounts);

	if (mesh.charCount != 0) {
		for (u32 i = 0; i < 4; ++i)
			hmx_string_cleanup(mesh.bones[i]);
	}

	for (u32 i = 0; i < mesh.partCount; ++i) {
		free(mesh.parts[i].faces);
		free(mesh.parts[i].vertices);
	}
	free(mesh.parts);
}

void hmx_mesh_print(HX_MESH mesh)
{
	printf("VERSION: %u\n", mesh.version);

	puts("TRANSFORM: {");
	hmx_transform_print(mesh.transform);
	puts("}");

	fputs("DRAW: ", stdout);
	hmx_draw_print(mesh.draw);

	fputs("MATERIAL: ", stdout);
	hmx_string_print(mesh.matPath);
	putchar('\n');

	fputs("GEOMETRY_OWNER: ", stdout);
	hmx_string_print(mesh.geometryOwner);
	putchar('\n');

	printf("MUTABLE_PARTS: %s\n", HX_MUTABLE_TYPE_NAME[mesh.mutableParts]);
	printf("VOLUME: %s\n", HX_VOLUME_TYPE_NAME[mesh.volume]);

	printf("BSP: %u\n", mesh.bsp);

	fputs("VERTICES: [", stdout);
	for (u32 i = 0; i < mesh.vertCount; ++i) {
		hmx_vertex_print(mesh.vertTable[i]);
		if (i != mesh.vertCount - 1)
			fputs(", ", stdout);
	}
	puts("]");

	fputs("TRIANGLES: [", stdout);
	for (u32 i = 0; i < mesh.triCount; ++i) {
		hmx_triangle_print(mesh.triTable[i]);
		if (i != mesh.triCount - 1)
			fputs(", ", stdout);
	}
	puts("]");

	// Just guessing how this is structured
	puts("MESH_PARTS: [");
	HX_TRIANGLE *triStart = mesh.triTable;
	for (u32 i = 0; i < mesh.partCount; ++i) {
		HX_TRIANGLE *triEnd = triStart + mesh.partTriCounts[i];
		fputs("\tMeshPart(triangles=[", stdout);
		for (; triStart < triEnd; ++triStart) {
			assert (triStart < mesh.triTable + mesh.triCount);

#ifndef MESH_VERBOSE_TRIANGLE_PARTS
			printf("%lu", (triStart - mesh.triTable));
#else
			HX_TRIANGLE tri = *triStart;
			hmx_triangle_print(tri);
#endif
			if (triStart != triEnd - 1)
				fputs(", ", stdout);
		}
		fputs("], faces=[", stdout);
		HX_MESHPART group = mesh.parts[i];
		u16 *vertStart = group.vertices;
		u32 prevfaces = 0;
		for (u32 si = 0; si < group.faceCount; ++si) {
			u16 *vertEnd = vertStart + group.faces[si] - prevfaces;
			prevfaces = group.faces[si];
			fputs("Section([", stdout);
			for (; vertStart < vertEnd; ++vertStart) {
				u16 vertId = *vertStart;
				assert (vertId < mesh.vertCount);

#ifndef MESH_VERBOSE_VERTEX_PARTS
				printf("%u", vertId);
#else
				HX_VERTEX vert = mesh.vertTable[vertId];
				hmx_vertex_print(vert);
#endif
				if (vertStart != vertEnd - 1)
					fputs(", ", stdout);
			}
			fputs("])", stdout);
			if (si != group.faceCount - 1)
				fputs(", ", stdout);
		}
		fputs("])", stdout);
		if (i != mesh.partCount - 1)
			fputs(", ", stdout);
		putchar('\n');
	}
	puts("]");
	if (mesh.charCount == 0) {
		puts("BONES: NONE");
	} else {
		fputs("BONES: [", stdout);
		for (u32 i = 0; i < 4; ++i) {
			fputs("Bone(refId=", stdout);
			hmx_string_print(mesh.bones[i]);
			fputs(", transform=", stdout);
			hmx_matrix_print(mesh.boneTransforms[i]);
			putchar(')');
			if (i != 3)
				fputs(", ", stdout);
		}
		puts("]");
	}
}

char const *const HX_VOLUME_TYPE_NAME[HX_VOLUME_TYPE_AMOUNT] = {
	"VolumeEmpty",
	"VolumeTriangles",
	"VolumeBSP",
	"VolumeBox",
};

char const *const HX_MUTABLE_TYPE_NAME[HX_MUTABLE_TYPE_AMOUNT] = {
	"kMutableNone",
	[31]="kMutableVerts",
	"kMutableFaces",
	[63]="kMutableAll",
};
