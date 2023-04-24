// hmxmesh.h - Harmonix mesh structs and functions
#ifndef HMXMESH_H
#define HMXMESH_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "hmxcommon.h"
#include "hmxmeshpart.h"
#include "hmxmatrix.h"
#include "hmxdraw.h"
#include "hmxtransform.h"
#include "hmxstring.h"
#include "hmxprimitive.h"
#include "hmxvertex.h"
#include "hmxtriangle.h"


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
	u32 version;			// should be 25
	HX_TRANSFORM transform;		// love me some 3d environments
	HX_DRAW draw;

	HX_STRING matName;
	HX_STRING geometryOwner;	// "geometry owner" (???????)

	MUTABLE_ENUM mutableParts;
	VOLUME_ENUM volume;
	u8 bsp;				// never observed, always 0

	u32 vertCount;
	HX_VERTEX* vertTable;

	u32 triCount;
	HX_TRIANGLE* triTable;

	u32 partCount;
	u8 *partTriCounts;		// sum should == triCount

	u32 charCount;			// no bones if == 0
	HX_STRING *bones;		// NULL if charCount == 0, 4 strings if != 0
	HX_MATRIX *boneTransforms;	// NULL if charCount == 0, 4 matrices if != 0

	HX_MESHPART *parts;
} HX_MESH;

HX_MESH hmx_mesh_load(FILE *file);
void hmx_mesh_print(HX_MESH meshData);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
