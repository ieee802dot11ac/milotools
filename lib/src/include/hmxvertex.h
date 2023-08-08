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

typedef struct { // both W coordinates are v34 exclusive
	f32 x; 
	f32 y;
	f32 z;
	f32 w; 
	// Normals
	f32 nx;
	f32 ny;
	f32 nz;
	f32 nw;
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
} HX_VERTEX_NU; // also applies up to rb2, apparently


HX_VERTEX_FREQ hmx_freqvertex_load(FILE *file);
void hmx_freqvertex_write(FILE *file, HX_VERTEX_FREQ vertex);
void hmx_freqvertex_print(HX_VERTEX_FREQ vertex);

HX_VERTEX_AMP hmx_ampvertex_load(FILE *file);
void hmx_ampvertex_write(FILE *file, HX_VERTEX_AMP vertex);
void hmx_ampvertex_print(HX_VERTEX_AMP vertex);

HX_VERTEX_NU hmx_nu_vertex_load(FILE *file, int version);
void hmx_nu_vertex_write(FILE *file, HX_VERTEX_NU vertex, int version);
void hmx_nu_vertex_print(HX_VERTEX_NU vertex);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
