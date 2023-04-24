#pragma once
#include "imhex/patterns/color.hexpat"
#include "imhex/patterns/string.hexpat"
#include "imhex/patterns/transform.hexpat"

enum HX_LIGHT_TYPE : u32 {
    kLightPoint,
    kLightDirectional,
    kLightFakeSpot,
    kLightFloorSpot,
    kLightShadowRef
};

struct HX_LIGHT {
    u32 version;
    HX_TRANSFORM transform;
    HX_COLOR_3F color;
    float intensity;
    float range;
    HX_LIGHT_TYPE type;
};
