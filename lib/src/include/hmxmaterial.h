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
    kTexBorderBlack,
    kTexBorderWhite,
    kTexWrapMirror,
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

// Starting w/ v56
typedef enum {
    kPerPixelOff,
    kPerPixelXbox360Only,
    kPerPixelPs3Only,
    kPerPixelAllNgPlatforms,
	HX_PERPIXEL_COUNT
} HX_PERPIXEL;

extern char const *const HX_PERPIXEL_NAME[HX_PERPIXEL_COUNT];

typedef enum
{
    kStencilIgnore,
    kStencilWrite,
    kStencilTest
} STENCILMODE_ENUM; // too lazy rn to change these

typedef enum
{
    kShaderVariationNone,
    kShaderVariationSkin,
    kShaderVariationHair
} SHADERVARIATION_ENUM;

typedef enum {
    kDiffuse,
    kEnviron = 2,
} TEXMAP_ENUM;

typedef struct
{
    // 2 - Emissive?
    // 3 - Transparent (i.e. glass)?
    // 4 - Diffuse
    // 5 - Environ
    // 6 - ???
    i32 map_type; // Might actually be used for pass order

    HX_MATRIX tex_xfm;

    u8 data[13];
    HX_STRING name; // Diffuse texture
} HX_MATERIAL_TEX_ENTRY_AMP;

typedef struct {
	// 2-0: Regular
	// 3-0: Idk - eyes
	// 2-2: Shiny - torsoenv
	// 3-2: Shiny - enviro, shinplates
	u32 unknown1;		// 1-4
	// HX_TEXGEN texGen;	// 0,1,2,5
	TEXMAP_ENUM map_type;

	HX_MATRIX matx;		// "Transform for coordinate generation" ?
	HX_TEXWRAP texWrap;	// 0-1
	HX_STRING texName;	// diffuse texture
} HX_MATERIAL_TEXTURE_ENTRY;

typedef struct {
	u32 version; // 8 (Amp Demo), 9 (Amp), 15 (AntiGrav), 21 (KRPAI/GH1), 25 (GH2 4-song) 27 (GH2), 28 (GH2 360), 41 (RB1), 47 (RB2), 55 (TBRB), 56 (GDRB), 68 (RB3)
	// bitch got improved basically every game lmao
	u32 ampTexCount;
	HX_MATERIAL_TEX_ENTRY_AMP *ampTextures; // only for amp and its demos

	u32 textureCount;
	HX_MATERIAL_TEXTURE_ENTRY *textures; // for everything after amp to gh1, afterwards i think they went monogamous

	HX_BLEND blend; // might be for default texture index? (used for skins?)
	HX_COLOR_4F color;
	// amp demo to antigrav club
	HX_COLOR_4F color_2;

	f32 some_floats[4]; // according to cisco it's 4 separate floats, but afaict they don't. do anything. so they're getting abandoned here lmao
	bool some_bool;
	u8 padding[14];
	// end amp and demo club
	u32 unknown_num;
	// post-antigrav to gh1 club
	// This part is a mess
	// These will all be 0 when material is used for a shadow?
	u8 always1_1;
	u16 always0_1;
	u32 always1_2;
	u16 always0_2;

	HX_BLEND blend2; // only 0-4 observed
	u16 always0_3;
	
	// PAST THIS POINT: GH2 AND ONWARDS

	bool prelit;      // Use vertex color and alpha for base or ambient - Usually true
    bool use_environ; // Modulate with environment ambient and lights - Usually false

    HX_ZMODE z_mode;   // How to read and write z-buffer
    bool alpha_cut;      // Cut zero alpha pixels from z-buffer
	i32 alpha_threshold; // Alpha level below which gets cut (0-255), only for version > 37 (track packs? phase?)
	bool alpha_write;    // Write pixel alpha to screen
    
    HX_TEXGEN tex_gen;   // How to generate texture coordinates
    HX_TEXWRAP tex_wrap; // Texture mapping mode

    HX_MATRIX tex_xfm;        // Transform for coordinate generation
    HX_STRING diffuse_tex; // Base texture map, modulated with color and alpha

    HX_STRING next_pass; // Next material for object (Mat)
    bool intensify;      // Double the intensity of base map - Always false
    bool cull;           // Cull backface polygons - Always true

    f32 emissive_multiplier; // Multiplier to apply to emission
    HX_COLOR_3F specular_rgb;// Color to use; multiplied by specular texture RGB if present
    f32 specular_power;      // Power to use; multiplied by specular texture Alpha if present - 10.0-50.0 not uncommon

    HX_STRING normal_map;   // Texture map to define lighting normals. Requires per-pixel lighting
    HX_STRING emissive_map; // Map for self illumination
    HX_STRING specular_map; // Texture map for specular color and power. Requires per-pixel lighting

	// Do something w/ RndTex?
    // Seems to match diffuse_tex
	HX_STRING some_string; // pre-v51 (lego?)

	HX_STRING environ_map;  // CubeTex - Cube texture for reflections
	// v25 (GH2 4-song) doesn't have per-pixel lighting
	bool per_pixel_lit;
	HX_PERPIXEL per_pixel_lit_gdrb; // Per-pixel lighting mode for this material

	bool ignored_bool; // v27-v49, seemingly pointless/padding

	STENCILMODE_ENUM stencil_mode;   // How to read and write the stencil buffer; v28 onwards (sorry, ps2)

	HX_STRING ignore_string; // v29-v40, also pointless/padding

	/*
	pre-v33
	if (version > 29) {
        // Load fur from "{mat_base_name}.fur" file
        // Call RndFur::LoadOld if found
    }
	*/

	HX_STRING fur;    // Use fur shader; v33 onwards

	bool ignored_bool_2; // these 3 are 34-48
	HX_COLOR_3F ignored_color;
    f32 ignored_alpha;

	HX_STRING some_string_2; // Do something w/ RndTex? v35-48

	// v35+
	f32 de_normal;  // Amount to diminish normal map bumpiness, 0 is neutral, 1 is no bumps, -1 exaggerates (range: -3 to -1)
    f32 anisotropy; // Specular power in downward (strand) direction, 0 to disable (range: 0.0 to 100.0)
	// v38+
	bool ignored_bool_3; // only to v41

	f32 norm_detail_tiling;   // Texture tiling scale for the detail map
    f32 norm_detail_strength; // Strength of the detail map bumpiness

	f32 ignored_floats[5]; // only to v41

	HX_STRING norm_detail_map; // Detail map texture

	HX_STRING some_string_3; // only to v41

	// v43+

	// Seems to be more work to calculate
    // Probably 2nd bit?
    // point_lights = (b ^ 1 >> 1) - ((b ^ 1) & b) >> 0x1f
    u32 some_bitfield; // *immediately* v43 and v44
	bool point_lights; // v45+, the opposite side of the coin of the bitfield

	bool proj_lights;  // Is the Mat lit with projected lights?
    bool fog;          // Is the Mat affected by fog?
    bool fade_out;     // Is the Mat affected its Environment's fade_out?

	bool ignored_bool_4; // ghidra shat the bed on this one, the requirement is version < 46
	bool color_adjust; // Is the Mat affected its Environment's color adjust? >v46
	// v47+
	HX_COLOR_3F rim_rgb;	// Rim lighting color; multiplied by the rim texture RGB if present
    f32 rim_power;			// Rim lighting power; multiplied by the rim texture Alpha if present (range: 0.0 to 64.0)
    HX_STRING rim_map;		// Texture map that defines the rim lighting color (in the RGB channels) and power (in the Alpha channel). Requires per-pixel lighting.
    bool rim_always_show;	// When enabled, this causes the rim effect to be visible regardless of the lighting direction. This is useful when simulating materials such as cloth
    
	bool screen_aligned; // Projected material from camera's POV; v49+

	// if val != 0, set shader_variation to kShaderVariationSkin (1)
    u8 legacy_shader_variation; // only for v50

	// v51+
	SHADERVARIATION_ENUM shader_variation; // Select a variation on the shader to enable a new range of rendering features
	HX_COLOR_3F specular2_rgb;	// Secondary specular color. Only valid for certain shader variations
    f32 specular2_power;		// Secondary specular power. Only valid for certain shader variations

	bool ignored_bool_5; // v52 exclusive! get in quick

	// Not mapped to SyncProperty()
    // Value is usually 0.0 or 1.0
    // Default: 1.0
    float val_0x160; // v53+

	// Not mapped to SyncProperty()
    // Values are usually 0.0 or 1.0
    // Default: (1.0, 1.0, 1.0, 0.0)
    float val_0x170; // v55+
    float val_0x174;
    float val_0x178;
    float val_0x17c;

	HX_STRING alpha_mask; // Alpha mask coordinates (in widescreen) and texture (ScreenMask); v54+
    // RndMat::AlphaMaskPostSync()

	bool ps3_force_trilinear; // Force trilinear filtering of diffuse map (PS3 only); v55+

} HX_MATERIAL;

HX_MATERIAL hmx_material_load(FILE *file, bool isBigEndian);
void hmx_material_cleanup(HX_MATERIAL mat);
void hmx_material_print(HX_MATERIAL mat);

HX_MATERIAL_TEXTURE_ENTRY hmx_material_texture_entry_load(FILE *file, bool isBigEndian);
void hmx_material_texture_entry_cleanup(HX_MATERIAL_TEXTURE_ENTRY texEnt);
void hmx_material_texture_entry_print(HX_MATERIAL_TEXTURE_ENTRY texEnt);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
