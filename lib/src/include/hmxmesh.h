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
	HX_VOLUME_TYPE_AMOUNT
} HX_VOLUME_TYPE;

extern char const *const HX_VOLUME_TYPE_NAME[HX_VOLUME_TYPE_AMOUNT];

typedef enum {
	kMutableNone = 0,
	kMutableVerts = 31,
	kMutableFaces = 32,
	kMutableAll = kMutableVerts | kMutableFaces,
	HX_MUTABLE_TYPE_AMOUNT = 4
} HX_MUTABLE_TYPE;

extern char const *const HX_MUTABLE_TYPE_NAME[HX_MUTABLE_TYPE_AMOUNT];




typedef struct {
	u32 version;			// Amplitude (2003) is 14, Guitar Hero is 25
	HX_TRANSFORM transform;		// love me some 3d environments
	HX_DRAW draw;

	HX_STRING matPath;
	HX_STRING geometryOwner;	// "geometry owner" (???????)

	HX_MUTABLE_TYPE mutableParts;
	HX_VOLUME_TYPE volume;
	u8 bsp;				// never observed, always 0

	u32 vertCount;
	HX_VERTEX* vertTable;

	u32 triCount;
	HX_TRIANGLE* triTable;

	u32 partCount;
	u8 *partTriCounts;		// sum should == triCount

	u32 charCount;			// no bones if == 0
	HX_STRING bones[4];		// all NULL if charCount == 0, 4 strings if != 0
	HX_MATRIX boneTransforms[4];	// all 0 if charCount == 0, 4 matrices if != 0

	HX_MESHPART *parts;
} HX_MESH;

HX_MESH hmx_mesh_load(FILE *file);
void hmx_mesh_cleanup(HX_MESH mesh);
void hmx_mesh_print(HX_MESH mesh);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
