// hmxstring.h - Harmonix String (length and char pointer)
#ifndef HMXSTRING_H
#define HMXSTRING_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include <stdio.h>

typedef struct {
    u32 length;
    char *value;
} HX_STRING;

#define HX_STRING_EMPTY ((HX_STRING) { .length = 0, .value = NULL })

HX_STRING hmx_string_load(FILE* file, bool isBigEndian);
bool hmx_string_write(FILE* file, HX_STRING string, bool isBigEndian);
char *hmx_string_cstring(HX_STRING string);
void hmx_string_cleanup(HX_STRING string);
void hmx_string_print(HX_STRING string);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
