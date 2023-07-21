#include "hmxmetadata.h"
#include "hmxdtx.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>
HX_METADATA *hmx_metadata_load(FILE *file) {
    HX_METADATA *meta = malloc(sizeof(HX_METADATA));
    meta->revision = iohelper_read_u32(file);
    meta->type = hmx_string_load(file);
    meta->node = hmx_dtx_load(file);
    if (meta->revision != 0) meta->comment = hmx_string_load(file);
    return meta;
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
