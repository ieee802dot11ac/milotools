// hmxreference.h - Harmonix External Reference structure and associated functions
#ifndef HMXREFERENCE_H
#define HMXREFERENCE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include <stdio.h>

typedef struct {
    u32 strLen;
    char *refName;
} HX_REFERENCE;

HX_REFERENCE hmx_reference_load(FILE* file);
void hmx_reference_print(HX_REFERENCE ref);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
