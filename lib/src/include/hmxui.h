// hmxui.h - Harmonix UI stuff (the actually modern way)
#ifndef HMXUI_H
#define HMXUI_H
#include "hmx.h"
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
    i32 version;
    HX_COLOR_4F color;
} HX_UI_COLOR; // why tho

typedef struct {
    u32 version;
    HX_UI_COMPONENT ui_component;
    float min_display;
    float max_display;
    float unknown1;
    float unknown2;
} HX_UI_LIST;

typedef struct {
    i32 version;
    HX_UI_COMPONENT ui_component;
    bool localize;
    HX_STRING text_token; // the token for the locale
} HX_UI_LABEL;

typedef struct {
    i32 version;
    HX_UI_LABEL ui_label;
} HX_UI_BUTTON; // why 2: the confusioning
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
