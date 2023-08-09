#include "hmxmesh.h"
#include "hmxcommon.h"
#include "hmxdraw.h"
#include "hmxgroupsec.h"
#include "hmxmatrix.h"
#include "hmxmetadata.h"
#include "hmxprimitive.h"
#include "hmxstring.h"
#include "hmxtransform.h"
#include "hmxtriangle.h"
#include "hmxvector.h"
#include "hmxvertex.h"
#include "iohelper.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// #define MESH_VERBOSE_TRIANGLE_PARTS
// #define MESH_VERBOSE_VERTEX_PARTS

BSPNode *bspnode_load(FILE *file, bool isBigEndian) {
	BSPNode *node = malloc(sizeof(BSPNode));
	node->has_value = iohelper_read_u8(file);
	if (node->has_value) {
		node->vec = hmx_vec4f_load(file, isBigEndian);
		node->left = bspnode_load(file, isBigEndian);
		node->right = bspnode_load(file, isBigEndian);
	} else {
		node->vec = (Vector4f){{0.0f},{0.0f},{0.0f},{0.0f}};
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

HX_MESH *hmx_mesh_load(FILE *file, bool isBigEndian)
{
	HX_MESH *mesh = malloc(sizeof(HX_MESH));
	bool FREQMESH = false;
	mesh->version = iohelper_read_u32_ve(file, isBigEndian);
	if (mesh->version <= 10) FREQMESH = true;
	if (mesh->version > 27) mesh->meta = hmx_metadata_load(file, isBigEndian);
	mesh->transform = hmx_transform_load(file, isBigEndian);
	mesh->draw = hmx_draw_load(file, isBigEndian);

	if (mesh->version < 15) {
		mesh->always_zero = iohelper_read_u32_ve(file, isBigEndian);
		mesh->ampbones_count = iohelper_read_u32_ve(file, isBigEndian);
		if (FREQMESH) {
			for (i32 i = 0; i < mesh->ampbones_count; i++) 
				mesh->ampbones[i] = iohelper_read_cstring_to_hxstring(file);
		} else {
			for (i32 i = 0; i < mesh->ampbones_count; i++) 
				mesh->ampbones[i] = hmx_string_load(file, isBigEndian);
		}
	}

	if (mesh->version < 20) {
		mesh->num_1 = iohelper_read_u32_ve(file, isBigEndian);
		mesh->num_2 = iohelper_read_u32_ve(file, isBigEndian);
	}

	if (mesh->version < 3) {
		mesh->some_value = hmx_string_load(file, isBigEndian);
	}

	if (FREQMESH) mesh->matPath = iohelper_read_cstring_to_hxstring(file);
	else mesh->matPath = hmx_string_load(file, isBigEndian);
	if (mesh->version == 27) mesh->mat_2 = hmx_string_load(file, isBigEndian);
	if (FREQMESH) mesh->geometryOwner = iohelper_read_cstring_to_hxstring(file);
	else mesh->geometryOwner = hmx_string_load(file, isBigEndian);

	if (mesh->version < 13) {	
		if (FREQMESH) mesh->alt_geom_owner = iohelper_read_cstring_to_hxstring(file);
		else mesh->alt_geom_owner = hmx_string_load(file, isBigEndian);
	}

	if (mesh->version < 15) {	
		if (FREQMESH) mesh->trans_parent = iohelper_read_cstring_to_hxstring(file);
		else mesh->trans_parent = hmx_string_load(file, isBigEndian);
	}

	if (mesh->version < 14) {	
		if (FREQMESH) mesh->trans_1 = iohelper_read_cstring_to_hxstring(file);
		else mesh->trans_1 = hmx_string_load(file, isBigEndian);
		if (FREQMESH) mesh->trans_2 = iohelper_read_cstring_to_hxstring(file);
		else mesh->trans_2 = hmx_string_load(file, isBigEndian);
	}

	if (mesh->version < 3) {
		mesh->some_vector = hmx_vec3f_load(file, isBigEndian);
	}

	if (mesh->version < 15) {
		mesh->sphere = hmx_primitive_sphere_load(file, isBigEndian);
	}

	if (mesh->version < 8) {
		mesh->some_bool = iohelper_read_u8(file);
	}

	if (mesh->version < 15) {	
		if (FREQMESH) mesh->some_string = iohelper_read_cstring_to_hxstring(file);
		else mesh->some_string = hmx_string_load(file, isBigEndian);
		mesh->some_float = iohelper_read_f32_ve(file, isBigEndian);
	}


	if (mesh->version < 16) {
		if (mesh->version > 11) mesh->some_bool2 = iohelper_read_u8(file);
	} else mesh->mutableParts = iohelper_read_u32_ve(file, isBigEndian);
	if (mesh->version > 17) mesh->volume = iohelper_read_u32_ve(file, isBigEndian);

	if (mesh->version > 18) mesh->node = bspnode_load(file, isBigEndian);
	if (mesh->node->has_value) return mesh;

	if (mesh->version == 7) mesh->some_bool3 = iohelper_read_u8(file);
	if (mesh->version < 11) mesh->some_number = iohelper_read_u32_ve(file, isBigEndian);

	mesh->vertCount = iohelper_read_u32_ve(file, isBigEndian);

	if (mesh->version >= 36) {
		mesh->is_ng = iohelper_read_u8(file);
		if (mesh->is_ng) {
			mesh->vert_size = iohelper_read_u32_ve(file, isBigEndian);
			mesh->some_type = iohelper_read_u32_ve(file, isBigEndian);
		}
	}
	/*
	mesh.vertTableGH = malloc(sizeof(HX_VERTEX_GH) * mesh.vertCount);
	assert (mesh.vertTableGH != NULL);
	for (u32 i = 0; i < mesh.vertCount; ++i)
		mesh.vertTableGH[i] = hmx_vertex_load(file);
	*/

	if (mesh->version <= 10) {
		mesh->vertTableFreq = malloc(sizeof(HX_VERTEX_FREQ) * mesh->vertCount);
		assert (mesh->vertTableFreq != NULL);
		for (u32 i = 0; i < mesh->vertCount; ++i) mesh->vertTableFreq[i] = hmx_freqvertex_load(file);
	} else if (mesh->version <= 22) {
		mesh->vertTableAmp = malloc(sizeof(HX_VERTEX_AMP) * mesh->vertCount);
		assert (mesh->vertTableAmp != NULL);
		for (u32 i = 0; i < mesh->vertCount; ++i) mesh->vertTableAmp[i] = hmx_ampvertex_load(file, isBigEndian);
	} else if (mesh->version < 35 || mesh->is_ng == false) {
		mesh->vertTableNu = malloc(sizeof(HX_VERTEX_NU) * mesh->vertCount);
		assert (mesh->vertTableNu != NULL);
		for (u32 i = 0; i < mesh->vertCount; ++i) mesh->vertTableNu[i] = hmx_nu_vertex_load(file, mesh->version > 28, isBigEndian);
	}

	mesh->triCount = iohelper_read_u32_ve(file, isBigEndian);
	mesh->triTable = malloc(sizeof(u16) * 3 * mesh->triCount); // why the fuck was it allocating the size of a vert
	assert (mesh->triTable != NULL);
	for (u32 i = 0; i < mesh->triCount; ++i)
		mesh->triTable[i] = hmx_triangle_load(file, isBigEndian);

	if (mesh->version < 24) {
		mesh->short_count = iohelper_read_u32_ve(file, isBigEndian);
		for (u32 i = 0; i < mesh->short_count; i++) {
			mesh->some_shorts[i] = iohelper_read_u16_ve(file, isBigEndian);
		}
	}

	if (mesh->version < 24 && mesh->version > 21) {
		mesh->group_count = iohelper_read_u32_ve(file, isBigEndian);
		for (u32 i = 0; i < mesh->group_count; i++) {
			mesh->groups[i].some_number = iohelper_read_u32_ve(file, isBigEndian);
			mesh->groups[i].short_count = iohelper_read_u32_ve(file, isBigEndian);
			for (u32 j = 0; j < mesh->groups[i].short_count; j++) {
				mesh->groups[i].shorts[j] = iohelper_read_u16_ve(file, isBigEndian);
			}
			mesh->groups[i].int_count = iohelper_read_u32_ve(file, isBigEndian);
			for (u32 j = 0; j < mesh->groups[i].int_count; j++) {
				mesh->groups[i].ints[j] = iohelper_read_u32_ve(file, isBigEndian);
			}
		}
	}

	if (mesh->version > 13 && mesh->version < 24) {
		mesh->unknown = iohelper_read_u32_ve(file, isBigEndian);
		return mesh;
	}

	mesh->groupSizesCount = iohelper_read_u32_ve(file, isBigEndian);
	mesh->groupSizes = malloc(sizeof(u8) * mesh->groupSizesCount);
	u32 shouldMatchTris = 0;
	for (u32 i = 0; i < mesh->groupSizesCount; ++i) {
		mesh->groupSizes[i] = iohelper_read_u8(file);
		shouldMatchTris += mesh->groupSizes[i];
	}

	if (shouldMatchTris != mesh->triCount)
		warn("Group sizes sum does not match # of triangles in mesh!");

	mesh->charCount = iohelper_read_u32_ve(file, isBigEndian);
	if (mesh->version < 34) {
		mesh->bones = malloc(sizeof(HX_STRING) * 4);
		mesh->boneTransforms = malloc(sizeof(HX_MATRIX) * 4);
	}
	if (mesh->charCount != 0) {
		for (u32 i = 0; i < 4; ++i)
			mesh->bones[i] = hmx_string_load(file, isBigEndian);

		for (u32 i = 0; i < 4; ++i)
			mesh->boneTransforms[i] = hmx_matrix_load(file, isBigEndian);
	} else {
		for (u32 i = 0; i < 4; ++i) {
			mesh->bones[i] = HX_STRING_EMPTY;
			mesh->boneTransforms[i] = (HX_MATRIX) { 0 };
		}

	}

	mesh->parts = malloc(sizeof(HX_GROUPSECTION) * mesh->groupSizesCount);
	for (u32 i = 0; i < mesh->groupSizesCount; ++i) {
		mesh->parts[i].faceCount = iohelper_read_u32_ve(file, isBigEndian);
		mesh->parts[i].vertexCount = iohelper_read_u32_ve(file, isBigEndian);

		mesh->parts[i].faces = malloc(sizeof(u32) * mesh->parts[i].faceCount);
		assert(mesh->parts[i].faces != NULL);
		mesh->parts[i].vertices = malloc(sizeof(u16) * mesh->parts[i].vertexCount);
		assert(mesh->parts[i].vertices != NULL);

		for (u32 si = 0; si < mesh->parts[i].faceCount; ++si)
			mesh->parts[i].faces[si] = iohelper_read_u32_ve(file, isBigEndian);
		for (u32 vi = 0; vi < mesh->parts[i].vertexCount; ++vi)
			mesh->parts[i].vertices[vi] = iohelper_read_u16_ve(file, isBigEndian);
	}

	return mesh;
}

void hmx_mesh_write(FILE *file, HX_MESH *mesh, bool isBigEndian) { //FIXME assumes little endian, need to stop doing that 
	bool FREQMESH = false;
	iohelper_write_u32_ve(file, mesh->version, isBigEndian);
	if (mesh->version <= 10) FREQMESH = true;
	if (mesh->version > 27) hmx_metadata_write(file, mesh->meta, isBigEndian);
	hmx_transform_write(file, mesh->transform, isBigEndian);
	hmx_draw_write(file, mesh->draw, isBigEndian);

	if (mesh->version < 15) {
		iohelper_write_u32_ve(file, mesh->always_zero, isBigEndian);
		iohelper_write_u32_ve(file, mesh->ampbones_count, isBigEndian);
		if (FREQMESH) {
			for (i32 i = 0; i < mesh->ampbones_count; i++) 
				fputs(hmx_string_cstring(mesh->ampbones[i]), file);	
		} else {
			for (i32 i = 0; i < mesh->ampbones_count; i++) 
				hmx_string_write(file, mesh->ampbones[i], isBigEndian);
		}
	}

	if (mesh->version < 20) {
		iohelper_write_u32_ve(file, mesh->num_1, isBigEndian);
		iohelper_write_u32_ve(file, mesh->num_2, isBigEndian);
	}

	if (mesh->version < 3) {
		hmx_string_write(file, mesh->some_value, isBigEndian);
	}

	if (FREQMESH) fputs(hmx_string_cstring(mesh->matPath), file);	
	else hmx_string_write(file, mesh->matPath, isBigEndian);
	if (mesh->version == 27) mesh->mat_2 = hmx_string_load(file, isBigEndian);
	if (FREQMESH) fputs(hmx_string_cstring(mesh->geometryOwner), file);	
	else hmx_string_write(file, mesh->geometryOwner, isBigEndian);

	if (mesh->version < 13) {	
		if (FREQMESH) fputs(hmx_string_cstring(mesh->alt_geom_owner), file);
		else hmx_string_write(file, mesh->alt_geom_owner, isBigEndian);
	}

	if (mesh->version < 15) {	
		if (FREQMESH) fputs(hmx_string_cstring(mesh->trans_parent), file);
		else hmx_string_write(file, mesh->trans_parent, isBigEndian);
	}

	if (mesh->version < 14) {
		if (FREQMESH) fputs(hmx_string_cstring(mesh->trans_1), file);
		else hmx_string_write(file, mesh->trans_1, isBigEndian);
		if (FREQMESH) fputs(hmx_string_cstring(mesh->trans_2), file);
		else hmx_string_write(file, mesh->trans_2, isBigEndian);
	}

	if (mesh->version < 3) {
		hmx_vec3f_write(file, mesh->some_vector, isBigEndian);
	}

	if (mesh->version < 15) {
		hmx_primitive_sphere_write(file, mesh->sphere, isBigEndian);
	}

	if (mesh->version < 8) {
		iohelper_write_u8(file, mesh->some_bool);
	}

	if (mesh->version < 15) {	
		if (FREQMESH) fputs(hmx_string_cstring(mesh->some_string), file);
		else hmx_string_write(file, mesh->some_string, isBigEndian);
		iohelper_write_f32_ve(file, mesh->some_float, isBigEndian);
	}

	if (mesh->version < 16) {
		if (mesh->version > 11) iohelper_write_u8(file, mesh->some_bool2);
	} else iohelper_write_u32_ve(file, mesh->mutableParts, isBigEndian);
	if (mesh->version > 17) iohelper_write_u32_ve(file, mesh->volume, isBigEndian);

	// if (mesh->version > 18) mesh->node = bspnode_write(file); // no bsps, mostly cause ????
	// if (mesh->node->has_value) return;

	if (mesh->version == 7) iohelper_write_u8(file, mesh->some_bool3);
	if (mesh->version < 11) iohelper_write_u32_ve(file, mesh->some_number, isBigEndian);

	iohelper_write_u32_ve(file, mesh->vertCount, isBigEndian);

	if (mesh->version >= 36) {
		iohelper_write_u8(file, mesh->is_ng);
		if (mesh->is_ng) {
			iohelper_write_u32_ve(file, mesh->vert_size, isBigEndian);
			iohelper_write_u32_ve(file, mesh->some_type, isBigEndian);
		}
	}

	if (mesh->version <= 10) { // TODO write the freq and amp vert write funcs
		//for (u32 i = 0; i < mesh->vertCount; ++i) hmx_freqvertex_write(file, mesh->vertTableFreq[i], isBigEndian);
	} else if (mesh->version <= 22) {
		//for (u32 i = 0; i < mesh->vertCount; ++i) hmx_ampvertex_write(file, mesh->vertTableAmp[i], isBigEndian);
	} else if (mesh->version < 35 || mesh->is_ng == false) {
		for (u32 i = 0; i < mesh->vertCount; ++i) hmx_nu_vertex_write(file, mesh->vertTableNu[i], mesh->version, isBigEndian);
	}
}

void hmx_mesh_cleanup(HX_MESH mesh)
{
	hmx_transform_cleanup(mesh.transform);
	hmx_draw_cleanup(mesh.draw);
	hmx_string_cleanup(mesh.matPath);
	hmx_string_cleanup(mesh.geometryOwner);

	free(mesh.vertTableNu);
	free(mesh.triTable);
	free(mesh.groupSizes);

	if (mesh.charCount != 0) {
		for (u32 i = 0; i < 4; ++i)
			hmx_string_cleanup(mesh.bones[i]);
	}

	for (u32 i = 0; i < mesh.groupSizesCount; ++i) {
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

	// printf("BSP: %u\n", mesh.bsp);

	fputs("VERTICES: [", stdout);
	for (u32 i = 0; i < mesh.vertCount; ++i) {
		hmx_nu_vertex_print(mesh.vertTableNu[i]);
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
	for (u32 i = 0; i < mesh.groupSizesCount; ++i) {
		HX_TRIANGLE *triEnd = triStart + mesh.groupSizes[i];
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
		HX_GROUPSECTION group = mesh.parts[i];
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
				hmx_ghvertex_print(vert);
#endif
				if (vertStart != vertEnd - 1)
					fputs(", ", stdout);
			}
			fputs("])", stdout);
			if (si != group.faceCount - 1)
				fputs(", ", stdout);
		}
		fputs("])", stdout);
		if (i != mesh.groupSizesCount - 1)
			fputs(", ", stdout);
		putchar('\n');
	}
	puts("]");
	if (mesh.charCount == 0) {
		puts("BONES: NONE");
	} else {
		fputs("BONES: [", stdout);
		u32 max = 0;
		if (mesh.version < 34) max = 4;
		else max = mesh.bone_count;
		for (u32 i = 0; i < max; ++i) {
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
