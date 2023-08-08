// hmxxbv.h - Harmonix Xbox videos
#ifndef HMXXBV_H
#define HMXXBV_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmx.h"

typedef struct {
    u8* data;
} XBV_FRAME;

typedef struct {
    u32 width;
    u32 height;
    u32 frame_count;
    u32 bytes_per_frame; // seems to be packed as 4bpp
    // 16 bytes of padding...
    XBV_FRAME* frames;
} HX_XBV;

extern HX_XBV *hmx_xboxvideo_load(FILE *file);
extern void hmx_xboxvideo_cleanup(HX_XBV *xbv);
extern void hmx_xboxvideo_print(HX_XBV *xbv);

#ifdef __cplusplus
}
#endif
#endif
