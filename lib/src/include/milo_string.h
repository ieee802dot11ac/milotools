// milo_string.h - Harmonix String (length and char pointer)
#ifndef MILO_STRING_H
#define MILO_STRING_H
#ifdef __cplusplus
extern "C" {
#endif

#include "milo_common.h"
#include <stdio.h>

typedef struct {
    u32 strLen;
    char *refName;
} MILO_STRING;

MILO_STRING milo_string_load(FILE* file);
void milo_string_print(MILO_STRING ref);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
