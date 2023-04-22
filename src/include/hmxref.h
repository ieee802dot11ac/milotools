// hmxref.h - HMX External Reference structure and associated functions
#ifndef HMXREF_H
#define HMXREF_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t strLen;
    char *refName;
} HX_EXTERNAL_REFERENCE;

HX_EXTERNAL_REFERENCE extref_from_file(FILE* file);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
