#pragma once
#include "imhex/patterns/facelist.hexpat"
#include "imhex/patterns/string.hexpat"
#include "imhex/patterns/transform.hexpat"
#include "imhex/patterns/vertex.hexpat"
#include "imhex/patterns/triangle.hexpat"
#include "imhex/patterns/primitives.hexpat"
#include "imhex/patterns/draw.hexpat"

enum VOLUME_ENUM : u32 {
	kVolumeEmpty,
	kVolumeTriangles,
	kVolumeBSP,
	kVolumeBox
};

enum MUTABLE_ENUM : u32 {
	kMutableNone = 0,
	kMutableVerts = 31,
	kMutableFaces = 32,
	kMutableAll = 63
};

struct HX_MESH {
	u32 version; // should be 25
	HX_TRANSFORM transform; // love me some 3d environments
	HX_DRAW draw;

	HX_STRING matName;
	HX_STRING geometryOwnerName;

	MUTABLE_ENUM mutableParts;
	VOLUME_ENUM volume;
	u8 bsp; // never observed, always 0

	u32 vertCount;
	HX_VERTEX vertTable[vertCount];

	u32 triCount;
	HX_TRIANGLE triTable[triCount];

	u32 partCount;
	u8 partTriCounts[partCount]; // sum should == total number of triangles(triCount)

	u32 charCount; // no bones if == 0
	if (charCount > 0) {
		HX_STRING bones[4];
		HX_MATRIX boneTransforms[4];
	}

	HX_FACE_LIST parts[partCount];
};
