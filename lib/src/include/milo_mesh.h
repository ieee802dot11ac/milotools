// milo_mesh.h - Harmonix mesh structs and functions
#ifndef MILO_MESH_H
#define MILO_MESH_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "milo_common.h"

#include "milo_transform.h"
#include "milo_string.h"
#include "milo_primitive.h"
#include "milo_vertex.h"
#include "milo_triangle.h"


typedef enum {
	kVolumeEmpty,
	kVolumeTriangles,
	kVolumeBSP,
	kVolumeBox,
	VOLUME_ENUM_AMOUNT
} VOLUME_ENUM;

extern char const *const VOLUME_ENUM_NAME[VOLUME_ENUM_AMOUNT];

typedef enum {
	kMutableNone = 0,
	kMutableVerts = 31,
	kMutableFaces = 32,
	kMutableAll = 63,
} MUTABLE_ENUM;

INLINE char *MUTABLE_ENUM_name(MUTABLE_ENUM mut)
{
	switch (mut) {
	case kMutableNone:
		return "MutableNone";
	case kMutableVerts:
		return "MutableVerts";
	case kMutableFaces:
		return "MutableFaces";
	case kMutableAll:
		return "MutableAll";
	}
	return "UNKNOWN";
}



typedef struct {
	// starting stuff
	u32 version; // should be 25
	MILO_TRANSFORM transform; // love me some 3d environments

	// bounding stuff. textures. fun times!
	MILO_SPHERE bounding;

	u8 _unknown0[9];

	MILO_STRING matName;

	// "geometry owner" (???????)
	MILO_STRING geometryOwner;
	MUTABLE_ENUM mutableParts;
	VOLUME_ENUM volume;
	u8 bsp; // no clue
	
	u32 vertCount;
	MILO_VERTEX* vertTable;
	u32 triCount;
	MILO_TRIANGLE* triTable;

	u8 _unknown1[16*4];
} MILO_MESH_FILE_GH;

MILO_MESH_FILE_GH milo_mesh_load(FILE *file);
void milo_mesh_print(MILO_MESH_FILE_GH meshData);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
