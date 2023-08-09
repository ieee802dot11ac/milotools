// hmxlight.h - Harmonix lights
#ifndef HMXLIGHT_H
#define HMXLIGHT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hmxmetadata.h"
#include "hmxtransform.h"
#include "hmxcolor.h"

typedef enum {
	kLightPoint,
	kLightDirectional,
	kLightFakeSpot,
	kLightFloorSpot,
	kLightShadowRef
} HX_LIGHT_TYPE;

typedef struct {
	u32 version; // 3 (GH1), 6 (GH2), 9 (GH2 360), 14 (TBRB)
	HX_METADATA *meta;
	HX_TRANSFORM transform;
	HX_COLOR_3F color;
	f32 intensity;
	f32 ignore_data_1[8]; // <v2
	f32 ignore_data_2[2]; // <v3
	f32 range;
	f32 ignore_data_3[3]; // <v3
	HX_LIGHT_TYPE type; // >v0
	f32 falloff_start; // >v11

	// Animation authority for LightPreset
    bool animate_color_from_preset;
    bool animate_position_from_preset; // both >v5

	// these four are >v6
	f32 topradius;    // Fake cone small radius at the source
    f32 botradius;    // Fake cone big radius at the far end
    f32 softness;     // Fake cone softness with 0 hard edge and 1 total mushy
    f32 displacement; // Amount along dir to adjust the fake spot position
	// past this point: v7 onwards
	HX_STRING texture; // fun with virtual gobos
	u32 string_count; // no clue. v8 and v9
	HX_STRING *strings; // no clue. v8 and v9

	HX_STRING color_owner; // >v10
	HX_MATRIX texture_xfm; // >v12
	bool only_projection; // >v13
} HX_LIGHT;


extern HX_LIGHT hmx_light_load(FILE *file, bool isBigEndian);
extern void hmx_light_cleanup(HX_LIGHT light);
extern void hmx_light_print(HX_LIGHT light);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
