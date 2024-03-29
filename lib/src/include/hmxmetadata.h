// hmxmetadata.h: the shit added in gh2 that makes shit inconvenient (do meshes *really* need inline dta?!)
#ifndef HMXMETADATA_H
#define HMXMETADATA_H
#ifdef __cplusplus
extern "C" {
#endif
#include "hmxstring.h"
#include "hmxcommon.h"
#include "hmxdtx.h"


typedef struct {
    u32 revision;
    HX_STRING type;
    HX_DTX *node; // hopefully we can just ignore it but i fear we cannot
    HX_STRING comment; // ever just leave a comment in a finished product? yeah, me neither; not on ps2
} HX_METADATA;

#define HX_META_EMPTY_PS2 ((HX_METADATA) { .revision = 0, .type = HX_STRING_EMPTY, .node = NULL, .comment = HX_STRING_EMPTY })
#define HX_META_EMPTY_NG ((HX_METADATA) { .revision = 1, .type = HX_STRING_EMPTY , .node = NULL, .comment = HX_STRING_EMPTY })

HX_METADATA *hmx_metadata_load(FILE *file, bool isBigEndian);
void hmx_metadata_write(FILE *file, HX_METADATA *meta, bool isBigEndian);
void hmx_metadata_print(HX_METADATA *meta);
void hmx_metadata_cleanup(HX_METADATA *meta);

#ifdef __cplusplus
}
#endif
#endif
