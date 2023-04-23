// hmxdraw.h - Harmonix Draw objects
#ifndef HMXDRAW_H
#define HMXDRAW_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "hmxprimitive.h"
#include "hmxreference.h"

typedef struct {
    uint32_t version; // should be 1
    bool showing;

    uint32_t draw_count; // Drawables (mesh, env, view)
    HX_REFERENCE* draw_objects;
    HX_SPHERE bounding;
} HX_DRAW;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
