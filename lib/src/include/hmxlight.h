// hmxlight.h - Harmonix lights
#ifndef HMXLIGHT_H
#define HMXLIGHT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
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
	u32 version; // should be 3
	HX_TRANSFORM transform;
	HX_COLOR_3F color;
	float intensity;
	float range;
	HX_LIGHT_TYPE type;
} HX_LIGHT;


extern HX_LIGHT hmx_light_load(FILE *file);
extern void hmx_light_cleanup(HX_LIGHT light);
extern void hmx_light_print(HX_LIGHT light);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
