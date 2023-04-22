#pragma once
#ifndef HMXSTUFF_H
#define HMXSTUFF_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

struct HX_EXTERNAL_REFERENCE {
	uint32_t strLen;
	char* refName;
};

typedef struct HX_EXTERNAL_REFERENCE HX_EXTERNAL_REFERENCE;

HX_EXTERNAL_REFERENCE getRefFromFile(FILE* file) {
	uint32_t len;
	HX_EXTERNAL_REFERENCE ret;
	fread(&len, 4, 1, file);
	ret.strLen = len;
	if (len == 0) {
		ret.refName = (char*)"\0";
	} else {
		for (int i = 0; i < len; i++) {ret.refName[i] = fgetc(file);}
	}
	return ret;
}


struct HX_SPHERE {
	float x;
	float y;
	float z;
	float r;
};

typedef struct HX_SPHERE HX_SPHERE;

typedef enum
{
	kConstraintNone,
	kConstraintLocalRotate,
	kConstraintParentWorld,
	kConstraintLookAtTarget,
	kConstraintShadowTarget,
	kConstraintBillboardZ,
	kConstraintBillboardXZ,
	kConstraintBillboardXYZ,
	kConstraintFastBillboardXYZ
} CONSTRAINT_ENUM; // i'm just stealing shit at this point, sorry cisco

typedef enum
{
	kVolumeEmpty,
	kVolumeTriangles,
	kVolumeBSP,
	kVolumeBox
} VOLUME_ENUM;

typedef enum
{
	kMutableNone = 0,
	kMutableVerts = 31,
	kMutableFaces = 32,
	kMutableAll = 63
} MUTABLE_ENUM;

struct HX_TRANS {
	uint32_t version; // should be 8
	float localTransMtx[12]; // local transformation matrix
	float worldTransMtx[12]; // world transformation matrix
	
	// i don't even know but trans so based
	uint32_t trans_count;
	HX_EXTERNAL_REFERENCE* trans_objects; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	CONSTRAINT_ENUM constraint;
	HX_EXTERNAL_REFERENCE target;
	bool preserve_scale; // 1 byte wide
	HX_EXTERNAL_REFERENCE parent;
};

typedef struct HX_TRANS HX_TRANS;

struct HX_VERT_GH {
	float X; // standard coord system
	float Y; // standard coord system
	float Z; // standard coord system
	float NormX; // normal map coords
	float NormY; // normal map coords
	float NormZ; // normal map coords
	float R; // 0-1
	float G; // 0-1
	float B; // 0-1
	float A; // 0-1, usually like half cause hmx
	float U; // texture space stuff
	float V; // texture space stuff
};

typedef struct HX_VERT_GH HX_VERT_GH;

struct HX_TRI_GH {
	uint16_t index0;
	uint16_t index1;
	uint16_t index2;
};

typedef struct HX_TRI_GH HX_TRI_GH;

struct HX_BMP_HEADER_GH {
	uint8_t magic;
	uint8_t bpp;
	uint32_t imgfmt;
	uint8_t padding1;
	uint16_t width;
	uint16_t height;
	uint16_t bytesperline;
	uint8_t padding2[19];
};

struct HX_MESH_FILE_GH {
	// starting stuff
	uint32_t version; // should be 25
	HX_TRANS transform; // love me some 3d environments

	// bounding stuff. textures. fun times!
	HX_SPHERE bounding;
	HX_EXTERNAL_REFERENCE matName;

	// "geometry owner" (???????)
	HX_EXTERNAL_REFERENCE geometryowner;
	MUTABLE_ENUM mutable;
	VOLUME_ENUM volume;
	uint8_t bsp; // no clue
	
	uint32_t vertCount;
	HX_VERT_GH* vertTable;
	uint32_t faceCount;
	HX_TRI_GH* faceTable;
};

typedef struct HX_MESH_FILE_GH HX_MESH_FILE_GH;

#endif