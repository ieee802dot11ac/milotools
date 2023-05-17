// hmxlabelex.h - Harmonix UI Labels (only really seen in GH1 and KRP (maybe amp, haven't checked))
#ifndef HMXLABELEX_H
#define HMXLABELEX_H
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
    i32 version; // gh1 is 6

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

extern HX_LABEL_EX *hmx_labelex_load(FILE *file);
extern void hmx_labelex_cleanup(HX_LABEL_EX *label);
extern void hmx_labelex_print(HX_LABEL_EX *label, char* str);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
