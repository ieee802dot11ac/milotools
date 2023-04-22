// hmxmesh.h - Harmonix mesh structs and functions
#ifndef HMXMESH_H
#define HMXMESH_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#include "hmxtrans.h"
#include "hmxref.h"
#include "hmxprimitive.h"
#include "hmxenums.h"
#include "hmxvert.h"
#include "hmxtri.h"


typedef struct {
	// starting stuff
	u32 version; // should be 25
	HX_TRANS transform; // love me some 3d environments

	// bounding stuff. textures. fun times!
	HX_SPHERE bounding;
	HX_EXTERNAL_REFERENCE matName;

	// "geometry owner" (???????)
	HX_EXTERNAL_REFERENCE geometryOwner;
	MUTABLE_ENUM mutableParts;
	VOLUME_ENUM volume;
	u8 bsp; // no clue
	
	u32 vertCount;
	HX_VERT_GH* vertTable;
	u32 faceCount;
	HX_TRI_GH* faceTable;
} HX_MESH_FILE_GH;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
