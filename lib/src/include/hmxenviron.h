// hmxenviron.h - Harmonix environments
#ifndef HMXENVIRON_H
#define HMXENVIRON_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxdraw.h"
#include "hmxcolor.h"

typedef struct {
	float fogStart;
	float fogEnd;
	HX_COLOR_4F fogColor; // Guessing alpha is last float?
} HX_FOG;

typedef struct {
    u32 version; // should be 1
    HX_DRAW draw;

    u32 lightsCount;
	HX_STRING* lights;

    HX_COLOR_4F ambient_color;

	HX_FOG fog;

    u8 fogEnable;
} HX_ENVIRON;

extern HX_FOG hmx_fog_load(FILE *file);
extern void hmx_fog_print(HX_FOG fog);

extern HX_ENVIRON hmx_environ_load(FILE *file);
extern void hmx_environ_cleanup(HX_ENVIRON environ);
extern void hmx_environ_print(HX_ENVIRON environ);

#ifdef __cplusplus
}
#endif
#endif
