// hmxmaterial.h - Harmonix material struct
#ifndef HMXMATERIAL_H
#define HMXMATERIAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "hmxcommon.h"
#include "hmxmatrix.h"
#include "hmxstring.h"
#include "hmxcolor.h"

typedef enum {
	kTexGenNone,
	kTexGenXfm,
	kTexGenSphere,
	kTexGenProjected,
	kTexGenXfmOrigin,
	kTexGenEnviron,
	HX_TEXGEN_COUNT
} HX_TEXGEN;

extern char const *const HX_TEXGEN_NAME[HX_TEXGEN_COUNT];

typedef enum {
	kTexWrapClamp,
	kTexWrapRepeat,
	HX_TEXWRAP_COUNT
} HX_TEXWRAP;

extern char const *const HX_TEXWRAP_NAME[HX_TEXWRAP_COUNT];

typedef enum {
	kZModeDisable,
	kZModeNormal,
	kZModeTransparent,
	kZModeForce,
	kZModeDecal,
	HX_ZMODE_COUNT
} HX_ZMODE;

extern char const *const HX_ZMODE_NAME[HX_ZMODE_COUNT];

typedef enum {
	kBlendDest, // Equal to dest rgb color
	kBlendSrc, // Equal to src rgb color
	kBlendAdd, // Alpha
	kBlendSrcAlpha,
	kBlendSrcAlphaAdd,
	kBlendSubtract,
	kBlendMultiply,
	HX_BLEND_COUNT
} HX_BLEND;

extern char const *const HX_BLEND_NAME[HX_BLEND_COUNT];

typedef struct {
	// 2-0: Regular
	// 3-0: Idk - eyes
	// 2-2: Shiny - torsoenv
	// 3-2: Shiny - enviro, shinplates
	u32 unknown1;		// 1-4
	HX_TEXGEN texGen;	// 0,1,2,5
	HX_MATRIX matx;		// "Transform for coordinate generation" ?
	HX_TEXWRAP texWrap;	// 0-1
	HX_STRING texName;	// diffuse texture
} HX_MATERIAL_TEXTURE_ENTRY;

typedef struct {
	u32 version; // always 21

	u32 textureCount;
	HX_MATERIAL_TEXTURE_ENTRY *textures;

	u32 always3; // might be for default texture index? (used for skins?)
	HX_COLOR_4F color;

	// This part is a mess
	// These will all be 0 when material is used for a shadow?
	u8 always1_1;
	u16 always0_1;
	u32 always1_2;
	u16 always0_2;

	HX_BLEND blend; // only 0-4 observed
	u16 always0_3;
} HX_MATERIAL;

HX_MATERIAL hmx_material_load(FILE *file);
void hmx_material_cleanup(HX_MATERIAL mat);
void hmx_material_print(HX_MATERIAL mat);

HX_MATERIAL_TEXTURE_ENTRY hmx_material_texture_entry_load(FILE *file);
void hmx_material_texture_entry_cleanup(HX_MATERIAL_TEXTURE_ENTRY texEnt);
void hmx_material_texture_entry_print(HX_MATERIAL_TEXTURE_ENTRY texEnt);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
