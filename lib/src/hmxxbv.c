#include "iohelper.h"
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "hmxxbv.h"

HX_XBV *hmx_xboxvideo_load(FILE *file) {
    HX_XBV *xbv = malloc(sizeof(HX_XBV));
    xbv->width = iohelper_read_u32(file);
    xbv->height = iohelper_read_u32(file);
    xbv->frame_count = iohelper_read_u32(file);
    xbv->bytes_per_frame = iohelper_read_u32(file);
    for (u32 i = 0; i < xbv->frame_count; i++) {
        for (u32 j = 0; j < xbv->bytes_per_frame; j++) {
            xbv->frames[i].data[j] = iohelper_read_u8(file);
        }
    }
    return xbv;
}

void hmx_xboxvideo_cleanup(HX_XBV *xbv) {
    for (u32 i = 0; i < xbv->frame_count; i++) {
        free(xbv->frames[i].data);
    }
    free(xbv->frames);
    free(xbv);
}
void hmx_xboxvideo_print(HX_XBV *xbv) {
    printf("width: %d\n", xbv->width);
    printf("height: %d\n", xbv->height);
    printf("frame count: %d\n", xbv->frame_count);
    printf("bytes/frame: %d\n", xbv->bytes_per_frame);
    printf("not printing these frames lmao\n");
}
#ifdef __cplusplus
}
#endif
