// hmxmetadata.h: the shit added in gh2 that makes shit inconvenient (do meshes *really* need inline dta?!)
#ifndef HMXMETADATA_H
#define HMXMETADATA_H
#ifdef __cplusplus
extern "C" {
#endif
#include "hmxstring.h"
#include "hmxcommon.h"
#include "hmxdtx.h"

#define EMPTY_META_PS2 (HX_METADATA){0,(HX_STRING){0,NULL},NULL}
#define EMPTY_META_NG (HX_METADATA){1,(HX_STRING){0,NULL},NULL,(HX_STRING){0,NULL}}

typedef struct {
    u32 revision;
    HX_STRING type;
    HX_DTX *node; // hopefully we can just ignore it but i fear we cannot
    HX_STRING comment; // ever just leave a comment in a finished product? yeah, me neither; not on ps2
} HX_METADATA;

HX_METADATA *hmx_metadata_load(FILE *file, bool isBigEndian);
void hmx_metadata_write(FILE *file, HX_METADATA *meta, bool isBigEndian);
void hmx_metadata_print(HX_METADATA *meta);
void hmx_metadata_cleanup(HX_METADATA *meta);

#ifdef __cplusplus
}
#endif
#endif
