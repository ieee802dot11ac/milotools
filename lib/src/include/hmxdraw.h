// hmxdraw.h - Harmonix Draw objects
#ifndef HMXDRAW_H
#define HMXDRAW_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "hmxprimitive.h"
#include "hmxstring.h"

typedef enum {
    kOverrideIncludeInDepthOnlyPass_None,
    kOverrideIncludeInDepthOnlyPass_Include,
    kOverrideIncludeInDepthOnlyPass_DontInclude
} OVERRIDEINCLUDEINDEPTHONLYPASS_ENUM;

typedef struct {
    u32 version; // 0 (Freq/Amp Demo/Amp), 1 (AntiGrav/GH1), 3 (GH2 4-song/GH2/GH2 360/RB1/TBRB/RB3), 4 (GDRB)
    bool showing;

    u32 drawableCount; // Drawables (mesh, env, view); <v2
    HX_STRING *drawables;

    HX_SPHERE bounding;

    f32 draw_order; // >v2

    OVERRIDEINCLUDEINDEPTHONLYPASS_ENUM depthpass; // v4+, so only green day?
} HX_DRAW;

extern HX_DRAW hmx_draw_load(FILE *file);
extern void hmx_draw_cleanup(HX_DRAW draw);
extern void hmx_draw_print(HX_DRAW draw);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
