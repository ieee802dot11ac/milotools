// hmxex.h - Harmonix UI stuff (only really seen in GH1)
#ifndef HMXEX_H
#define HMXEX_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "hmxtransform.h"
#include "hmxdraw.h"
#include "hmxstring.h"
#include "hmxprimitive.h"
#include "hmxobj.h"

typedef struct {
    i32 version;

    HX_TRANSFORM trans;
    HX_DRAW draw;

    u32 unknown;
    Vector3f always0;

    HX_STRING textType;

    bool showing;
    bool enabled;
    
    float hundredSomething;
    float tenSomething;
    HX_STRING buttonText;
} HX_BUTTON_EX;

typedef struct {
    i32 version; // krp is 4, gh1 is 6

    HX_TRANSFORM trans;
    HX_DRAW draw;

    bool showing; // complete guess
    Vector3f position;

    i32 size;
    HX_SPHERE bounding;

    HX_STRING fontType;
    bool always0;
    HX_STRING text;
    float fSize;
} HX_LABEL_EX;

typedef struct {
    i32 version;
    HX_TRANSFORM trans;
    HX_DRAW draw;
    HX_STRING path;
} HX_PICTURE_EX;

extern HX_BUTTON_EX *hmx_buttonex_load(FILE *file);
extern void hmx_buttonex_cleanup(HX_BUTTON_EX *button);
extern void hmx_buttonex_print(HX_BUTTON_EX *button);

extern HX_LABEL_EX *hmx_labelex_load(FILE *file);
extern void hmx_labelex_cleanup(HX_LABEL_EX *label);
extern void hmx_labelex_print(HX_LABEL_EX *label);

extern HX_PICTURE_EX *hmx_pictureex_load(FILE *file);
extern void hmx_pictureex_cleanup(HX_PICTURE_EX *pic);
extern void hmx_pictureex_print(HX_PICTURE_EX *pic);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
