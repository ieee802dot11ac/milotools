// hmxmesh.h - Harmonix mesh structs and functions
#ifndef HMXMESH_H
#define HMXMESH_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "hmxcommon.h"
#include "hmxgroupsec.h"
#include "hmxmatrix.h"
#include "hmxdraw.h"
#include "hmxtransform.h"
#include "hmxstring.h"
#include "hmxprimitive.h"
#include "hmxvertex.h"
#include "hmxtriangle.h"

typedef struct BSPNode{
    bool has_value;
    Vector4f vec;
    struct BSPNode* left;
    struct BSPNode* right;
} BSPNode;

typedef struct {
    u32 some_number;
    u32 short_count;
    u16* shorts;
    u32 int_count;
    u32* ints;
} GroupSectionAG;

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
	HX_MUTABLE_TYPE_AMOUNT,
} HX_MUTABLE_TYPE;

extern char const *const HX_MUTABLE_TYPE_NAME[HX_MUTABLE_TYPE_AMOUNT];

typedef struct {
	u32 version; // 10 (Freq), 13 (Amp Demo), 14 (Amp), 22 (AntiGrav), 25 (KRPAI/GH1), 28 (GH2/GH2 4-song), 29, 34 (GH2 360/RB1/RB2), 36 (TBRB), 37 (GDRB), 38 (RB3)
	HX_TRANSFORM transform;		// love me some 3d environments
	HX_DRAW draw;

	// quick jank zone: v0-14
	u32 always_zero; // "usually empty" make up your mind cisco
	i32 ampbones_count;
	HX_STRING *ampbones; // see lower freq comment
	// end jank zone

	u32 num_1; // v0-20, used for the mat z_mode, for... some reason
    u32 num_2; // v0-20, used for the mat z_mode, for... some reason

	HX_STRING some_value; // version <3 this feels like a joke

	HX_STRING matPath; // note to self: make sure to add the typecast for cstrings! freq uses null-terminated strings
	HX_STRING mat_2; // apparently v27 has the ability to have two mats. why? no clue

	HX_STRING geometryOwner;	// "geometry owner" (???????); also a cstring in freq
	HX_STRING alt_geom_owner; // freq-exclusive headache

	HX_STRING trans_parent; // in the "what thing is my transform based off of" way; usually same as geometry owner. amp and before exclusive

	HX_STRING trans_1; // pre-amp exclusive. hot shit!
	HX_STRING trans_2; // pre-amp exclusive. hot shit!

	Vector3f some_vector; // again, v<3

	HX_SPHERE sphere; // amp and before
	bool some_bool; // pre-v8

	HX_STRING some_string; // "ignored"
	f32 some_float; // "ignored"

	bool some_bool2; // replace mutableParts in v12-15

	HX_MUTABLE_TYPE mutableParts;
	HX_VOLUME_TYPE volume; // post-v17
	BSPNode *node; // if this actually has anything, die after this; post-v18

	bool some_bool3; // v7

	u32 some_number; // pre-v11

	u32 vertCount;
	bool is_ng; // v36+, denotes whether ps2/wii or ps3/360
	i32 vert_size; // only if NG!
    i32 some_type; // only if NG!
	union {
		HX_VERTEX_FREQ* vertTableFreq; // pre-v11
		HX_VERTEX_AMP* vertTableAmp; // pre-v23
		HX_VERTEX_GH* vertTableGH; // weird. don't trust it
		HX_VERTEX_GH2* vertTableGH2; // pre-v35/wii or ps2
	};

	u32 triCount;
	HX_TRIANGLE* triTable;

	u32 short_count; // pre-v24
	u16 *some_shorts; // pre-v24

	u32 group_count; // v22 or 23
	GroupSectionAG* groups; // v22 or 23

	u32 unknown; // v14-23, ends here

	u32 groupSizesCount;
	u8 *groupSizes;		// sum should == triCount

	u32 charCount;			// no bones if == 0
	i32 bone_count; // v34+ has 2^31 bones per mesh, before that is always 4 (but they don't all have to be populated)
	HX_STRING* bones;		// all NULL if charCount == 0, 4 strings if != 0
	HX_MATRIX* boneTransforms;	// all 0 if charCount == 0, 4 matrices if != 0
	bool keep_mesh_data; // v36+; always true for mutable meshes
	bool exclude_from_self_shadow; // v37; whether this mesh's Character parent uses it for shadows
	bool has_ao_calculation; // v38+; Whether or not this mesh has had ambient occlusion calculated on it.

	HX_GROUPSECTION *parts; // only if all of the 3: groupSizesCount > 0, groupSizes[0] > 0, before v25
} HX_MESH;


BSPNode *bspnode_load(FILE *file);
HX_MESH hmx_mesh_load(FILE *file);
void hmx_mesh_cleanup(HX_MESH mesh);
void hmx_mesh_print(HX_MESH mesh);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
