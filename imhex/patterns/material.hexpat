#pragma once
#include "imhex/patterns/matrix.hexpat"
#include "imhex/patterns/string.hexpat"
#include "imhex/patterns/color.hexpat"

enum HX_TEXGEN : u32 {
	kTexGenNone,
	kTexGenXfm,
	kTexGenSphere,
	kTexGenProjected,
	kTexGenXfmOrigin,
	kTexGenEnviron = 5
};

enum HX_TEXWRAP : u32 {
	kTexWrapClamp,
	kTexWrapRepeat = 1
};

struct HX_MATERIAL_TEXTURE_ENTRY {
	// 2-0: Regular
	// 3-0: Idk - eyes
	// 2-2: Shiny - torsoenv
	// 3-2: Shiny - enviro, shinplates
	u32 unknown1;		// 1-4
	HX_TEXGEN texGen;	// 0,1,2,5
	HX_MATRIX matx;		// "Transform for coordinate generation" ?
	HX_TEXWRAP texWrap;	// 0-1
	HX_STRING texName;	// diffuse texture
};

enum HX_ZMODE : u32 {
	kZModeDisable,
	kZModeNormal,
	kZModeTransparent,
	kZModeForce,
	kZModeDecal = 4
};

enum HX_BLEND : u32 {
	kBlendDest, // Equal to dest rgb color
	kBlendSrc, // Equal to src rgb color
	kBlendAdd, // Alpha
	kBlendSrcAlpha,
	kBlendSrcAlphaAdd,
	kBlendSubtract,
	kBlendMultiply = 6
};

struct HX_MATERIAL {
	u32 version; // always 21

	u32 textureCount;
	HX_MATERIAL_TEXTURE_ENTRY textures[textureCount];

	u32 always3; // might be for default texture index? (used for skins?)
	HX_COLOR_4F color;

	// This part is a mess
	// These will all be 0 when material is used for a shadow?
	u8 always1;
	u16 always0;
	u32 always1;
	u16 always0;

	HX_BLEND blend; // only 0-4 observed
	u16 always0;
};
