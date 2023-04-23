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
} LIGHT_TYPE_ENUM;

typedef struct {
	uint32_t version; // should be 3
	HX_TRANSFORM trans;
	HX_COLOR_3F color;
	float intensity;
	float range;
	LIGHT_TYPE_ENUM type;
} HX_LIGHT;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
