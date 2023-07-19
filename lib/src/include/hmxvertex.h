// hmxvertex.h - Harmonix vertex struct
#ifndef HMXVERTEX_H
#define HMXVERTEX_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "hmxcommon.h"

typedef struct {
	// Coordinates
	f32 x;
	f32 y;
	f32 z;
	// Normals
	f32 nx;
	f32 ny;
	f32 nz;
	// UVs
	f32 u;
	f32 v;
	// Weights
	f32 weight_0;
	f32 weight_1;
	f32 weight_2;
	f32 weight_3;
	// Bone indices
	u16 bone_0;
	u16 bone_1;
	u16 bone_2;
	u16 bone_3;
} HX_VERTEX_FREQ;

typedef struct {
	f32 x;
	f32 y;
	f32 z;
	// Bone indices
	u16 bone_0;
	u16 bone_1;
	u16 bone_2;
	u16 bone_3;
	// Normals
	f32 nx;
	f32 ny;
	f32 nz;
	// Weights
	f32 weight_0;
	f32 weight_1;
	f32 weight_2;
	f32 weight_3;
	// UVs
	f32 u;
	f32 v;
} HX_VERTEX_AMP; // also antigrav

typedef struct {
	f32 x; // standard coord system
	f32 y; // standard coord system
	f32 z; // standard coord system
	f32 normX; // normal map coords
	f32 normY; // normal map coords
	f32 normZ; // normal map coords
	f32 r; // 0-1
	f32 g; // 0-1
	f32 b; // 0-1
	f32 a; // 0-1, usually like half cause hmx
	f32 u; // texture space stuff
	f32 v; // texture space stuff
} HX_VERTEX_GH; // this is a now-defunct labeling from cisco's notes. i will only be keeping this cause i'm too lazy to redo it and i'm rushing gh2 meshes lmao

typedef struct {
	f32 x;
	f32 y;
	f32 z;
	// Normals
	f32 nx;
	f32 ny;
	f32 nz;
	f32 nw; // gh2 360 to rb2 exclusive (apparently also appears in NG beatles?)
	// Weights
	f32 weight_0;
	f32 weight_1;
	f32 weight_2;
	f32 weight_3;
	// UVs
	f32 u;
	f32 v;
	// Bone indices
	u16 bone_0;
	u16 bone_1;
	u16 bone_2;
	u16 bone_3;
	// Tangent? (range: -1 to 1)
	f32 tangent_0;
	f32 tangent_1;
	f32 tangent_2;
	f32 tangent_3;
} HX_VERTEX_GH2; // also applies up to rb2, apparently


HX_VERTEX_GH hmx_vertex_load(FILE *file);
void hmx_vertex_print(HX_VERTEX_GH vertex);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
