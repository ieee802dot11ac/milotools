#include "hmxdtx.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>
HX_DTX *hmx_dtx_load(FILE *file) {
    HX_DTX *dtx = malloc(sizeof(HX_DTX));
    dtx->hasTree = iohelper_read_u8(file);
    if (dtx->hasTree) {
        // TODO read dtx lmao
    } else dtx->root = NULL;
    return dtx;
}
void hmx_dtx_print(HX_DTX *dtx) {
    printf("HasTree: %d\n", dtx->hasTree);
}
void hmx_dtx_cleanup(HX_DTX *dtx) {
    free(dtx);
}
