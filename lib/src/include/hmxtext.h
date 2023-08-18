// hmxtext.h - 3d text? weird. anyways note: all milos with text also have fonts
#ifndef HMXTEXT_H
#define HMXTEXT_H
#ifdef __cplusplus
extern "C" {
#endif
#include "hmxmetadata.h"
#include "hmxdraw.h"
#include "hmxtransform.h"
#include "hmxcolor.h"

typedef enum {
    kCapsModeNone,
    kForceLower,
    kForceUpper
} CAPS_MODE_ENUM;

typedef enum { // fun with bitfields
    kTopLeft = 17,      // 0b00010001
    kTopCenter = 18,    // 0b00010010
    kTopRight = 20,     // 0b00010100
    kMiddleLeft = 33,   // 0b00100001
    kMiddleCenter = 34, // 0b00100010
    kMiddleRight = 36,  // 0b00100100
    kBottomLeft = 65,   // 0b01000001
    kBottomCenter = 66, // 0b01000010
    kBottomRight = 68,  // 0b01000100
} ALIGNMENT_ENUM;

typedef struct {
    u32 version; // 17 (GH2/GH2 360)
    HX_METADATA *meta;

    HX_DRAW draw;
    HX_TRANSFORM transform;

    HX_STRING font; // RndFont
    ALIGNMENT_ENUM align;
    HX_STRING text;
    HX_COLOR_4F color; // includes alpha

    f32 wrap_width;
    f32 leading;
    u32 fixed_length;

    f32 italics; // variable italicization. neat!
    f32 size;
    bool markup;
    CAPS_MODE_ENUM caps_mode;

    /*if (version < 21)
    {
        Bool unknown_bool;
        float unknown_floats[3];
    }*/
} HX_TEXT;

HX_TEXT *hmx_text_load(FILE *file, bool isBigEndian);
void hmx_text_write(FILE *file, HX_TEXT *text, bool isBigEndian);
void hmx_text_cleanup(HX_TEXT *text);
void hmx_text_print(HX_TEXT *text);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
