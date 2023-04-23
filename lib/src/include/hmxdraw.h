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
