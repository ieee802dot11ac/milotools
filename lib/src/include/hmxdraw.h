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

typedef struct {
    u32 version; // should be 1
    bool showing;

    u32 drawableCount; // Drawables (mesh, env, view)
    HX_STRING *drawables;
    HX_SPHERE bounding;
} HX_DRAW;

extern HX_DRAW hmx_draw_load(FILE *file);
extern void hmx_draw_cleanup(HX_DRAW draw);
extern void hmx_draw_print(HX_DRAW draw);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
