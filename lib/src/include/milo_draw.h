// milo_draw.h - Milo Draw objects
#ifndef MILO_DRAW_H
#define MILO_DRAW_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "milo_primitive.h"
#include "milo_string.h"

typedef struct {
    u32 version; // should be 1
    bool showing;

    u32 draw_count; // Drawables (mesh, env, view)
    MILO_STRING *draw_objects;
    MILO_SPHERE bounding;
} MILO_DRAW;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
