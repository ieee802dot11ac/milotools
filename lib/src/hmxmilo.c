#include "hmxmilo.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

HX_MILOFILE* hmx_milo_load(FILE* file) {
    HX_MILOFILE* milo = malloc(sizeof(HX_MILOFILE));
    BlockStructure strType = iohelper_read_u32(file) & 0xFF;
    printf("0x%.2x", strType);
    return milo;
}

void hmx_milo_cleanup(HX_MILOFILE* milo) {
    free(milo);
    return;
}

void hmx_milo_print(HX_MILOFILE* milo) {
    printf("version: %d\n", milo->version);
    return;
}
