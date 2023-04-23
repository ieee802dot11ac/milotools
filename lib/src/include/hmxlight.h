#include <stdint.h>
#include "hmxenums.h"
#include "hmxtransform.h"
#include "hmxcolor.h"

typedef struct {
    uint32_t version; // should be 3
    HX_TRANSFORM trans;
    HX_COLOR_3F color;
    float intensity;
    float range;
    LIGHT_TYPE_ENUM type;
} HX_LIGHT;
