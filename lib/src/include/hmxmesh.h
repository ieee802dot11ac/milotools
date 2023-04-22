// hmxmesh.h - Harmonix mesh structs and functions
#ifndef HMXMESH_H
#define HMXMESH_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "common.h"

#include "hmxtransform.h"
#include "hmxreference.h"
#include "hmxprimitive.h"
#include "hmxenums.h"
#include "hmxvertex.h"
#include "hmxtriangle.h"


typedef struct {
	// starting stuff
	u32 version; // should be 25
	HX_TRANSFORM transform; // love me some 3d environments

	// bounding stuff. textures. fun times!
	HX_SPHERE bounding;

	u8 _unknown0[9];

	HX_REFERENCE matName;

	// "geometry owner" (???????)
	HX_REFERENCE geometryOwner;
	MUTABLE_ENUM mutableParts;
	VOLUME_ENUM volume;
	u8 bsp; // no clue
	
	u32 vertCount;
	HX_VERTEX* vertTable;
	u32 triCount;
	HX_TRIANGLE* triTable;

	u8 _unknown1[16*4];
} HX_MESH_FILE_GH;

HX_MESH_FILE_GH hmx_mesh_load(FILE *file);
void hmx_mesh_print(HX_MESH_FILE_GH meshData);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
