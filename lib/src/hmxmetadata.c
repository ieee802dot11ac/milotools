#include "hmxmetadata.h"
#include "hmxdtx.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>
HX_METADATA *hmx_metadata_load(FILE *file, bool endian) {
    HX_METADATA *meta = malloc(sizeof(HX_METADATA));
    if (endian) {
        meta->revision = iohelper_read_u32_be(file);
    } else {
        meta->revision = iohelper_read_u32(file);
    }
    meta->type = hmx_string_load(file, endian);
    meta->node = hmx_dtx_load(file);
    if (meta->revision != 0) meta->comment = hmx_string_load(file, endian);
    return meta;
}

void hmx_metadata_write(FILE *file, HX_METADATA *meta, bool endian) {
    if (endian) {
        iohelper_write_u32_be(file, meta->revision);
    } else {
        iohelper_write_u32(file, meta->revision);
    }
    hmx_string_write(file, meta->type, endian);
    iohelper_write_u8(file, 0); // fuck you i'm not putting dta in shit
    if (meta->revision != 0) hmx_string_write(file, (HX_STRING){20, "Generated by HXConv"}, endian);
    return;
}

void hmx_metadata_print(HX_METADATA *meta) {
    printf("revision: %d\n", meta->revision);
    printf("type: %s\n", hmx_string_cstring(meta->type));
    printf("node:\n"); hmx_dtx_print(meta->node);
    printf("revision: %s\n", hmx_string_cstring(meta->comment));
}

void hmx_metadata_cleanup(HX_METADATA *meta) {
    hmx_dtx_cleanup(meta->node);
    free(meta);
}