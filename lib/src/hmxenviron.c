#include "hmxenviron.h"
#include "hmxcolor.h"
#include "hmxdraw.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>

HX_FOG hmx_fog_load(FILE *file, bool isBigEndian) {
    HX_FOG fog;
    fog.fogStart = iohelper_read_f32_ve(file, isBigEndian);
    fog.fogEnd = iohelper_read_f32_ve(file, isBigEndian);
    fog.fogColor = hmx_color_4f_load(file, isBigEndian);
    return fog;
}

void hmx_fog_print(HX_FOG fog) {
    printf("FOG START: %f\n", fog.fogStart);
    printf("FOG END: %f\n", fog.fogEnd);
    printf("FOG COLOR: "); hmx_color_4f_print(fog.fogColor);
}

HX_ENVIRON hmx_environ_load(FILE *file, bool isBigEndian) {
    HX_ENVIRON environment;
    environment.version = iohelper_read_u32_ve(file, isBigEndian);
    environment.draw = hmx_draw_load(file, isBigEndian);
    environment.lightsCount = iohelper_read_u32_ve(file, isBigEndian);
    if (environment.lightsCount != 0) {
        for (u32 i = 0; i < environment.lightsCount; i++) {
            environment.lights[i] = hmx_string_load(file, isBigEndian);
        }
    } else environment.lights = &(HX_STRING){0, ""};
    environment.ambient_color = hmx_color_4f_load(file, isBigEndian);
    environment.fog = hmx_fog_load(file, isBigEndian);
    environment.fogEnable = iohelper_read_u8(file);
    return environment;
}

void hmx_environ_cleanup(HX_ENVIRON environ) {
    hmx_draw_cleanup(environ.draw);
    hmx_string_cleanup(*environ.lights);
}

void hmx_environ_print(HX_ENVIRON environ) {
    printf("VERSION: %i\n", environ.version);
    printf("BEGIN DRAW\n"); hmx_draw_print(environ.draw); printf("\nEND DRAW\n"); 
    printf("LIGHT COUNT: %i\n", environ.lightsCount);
    printf("LIGHTS:\n");
    for (u32 i = 0; i < environ.lightsCount; i++) {
        hmx_string_print(environ.lights[i]);
    }
    printf("AMBIENT COLOR: "); hmx_color_4f_print(environ.ambient_color);
    printf("\nFOG: \n"); hmx_fog_print(environ.fog);
    printf("\nFOG ENABLE: %i\n", environ.fogEnable);
    printf("END ENVIRONMENT\n");
}
