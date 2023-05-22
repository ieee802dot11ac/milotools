// hmxui.h - Harmonix UI stuff (the actually modern way)
#ifndef HMXUI_H
#define HMXUI_H
#include "hmxcommon.h"
#include "hmx.h"
#include "hmxstring.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    u32 version;
    HX_TRANSFORM trans;
    HX_DRAW draw;
    HX_STRING object_dir1;
    HX_STRING object_dir2;
} HX_UI_COMPONENT;

typedef struct {
    u32 version;
    HX_UI_COMPONENT ui_component;
    float min_display;
    float max_display;
    float unknown1;
    float unknown2;
} HX_UI_LIST;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
