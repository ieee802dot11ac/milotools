#include "hmxenviron.h"
#include "hmxcolor.h"
#include "iohelper.h"

HX_FOG hmx_fog_load(FILE *file) {
    HX_FOG fog;
    fog.fogStart = iohelper_read_f32(file);
    fog.fogEnd = iohelper_read_f32(file);
    fog.fogColor = hmx_color_4f_load(file);
}

void hmx_fog_print(HX_FOG fog) {

}

HX_ENVIRON hmx_environ_load(FILE *file) {

}

void hmx_environ_print(HX_ENVIRON environ) {

}
