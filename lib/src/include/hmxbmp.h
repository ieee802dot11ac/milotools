// hmxbmp.h - Harmonix bitmap structs and functions
#ifndef HMXBMP_H
#define HMXBMP_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"


typedef struct {
    u8 magic;
    u8 bpp;
    u32 imgfmt;
    u8 padding1;
    u16 width;
    u16 height;
    u16 bytesperline;
    u8 padding2[19];
} HX_BMP_HEADER_GH;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif

