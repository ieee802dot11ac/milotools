// hmxstring.h - Harmonix String (length and char pointer)
#ifndef HMXSTRING_H
#define HMXSTRING_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include <stdio.h>

typedef struct {
    u32 strLen;
    char *refName;
} HX_STRING;

HX_STRING hmx_string_load(FILE* file);
void hmx_string_print(HX_STRING ref);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
