// hmxdraw.h - Harmonix Draw objects
#ifndef HMXDRAW_H
#define HMXDRAW_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "hmxprimitive.h"
#include "hmxstring.h"

typedef struct {
    u32 version; // should be 1
    bool showing;

    u32 draw_count; // Drawables (mesh, env, view)
    HX_STRING *draw_objects;
    HX_SPHERE bounding;
} HX_DRAW;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
