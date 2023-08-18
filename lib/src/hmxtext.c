#include "hmxtext.h"
#include "hmxcolor.h"
#include "hmxdraw.h"
#include "hmxmetadata.h"
#include "hmxtransform.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>
HX_TEXT *hmx_text_load(FILE *file, bool isBigEndian) {
    HX_TEXT *text = malloc(sizeof(HX_TEXT));
    text->version = iohelper_read_u32_ve(file, isBigEndian);
    text->meta = hmx_metadata_load(file, isBigEndian);
    text->draw = hmx_draw_load(file, isBigEndian);
    text->transform = hmx_transform_load(file, isBigEndian);
    text->font = hmx_string_load(file, isBigEndian);
    text->align = iohelper_read_u32_ve(file, isBigEndian);
    text->text = hmx_string_load(file, isBigEndian);
    #ifdef BAILEARLY
    return text;
    #endif
    text->color = hmx_color_4f_load(file, isBigEndian);
    text->wrap_width = iohelper_read_f32_ve(file, isBigEndian);
    text->leading = iohelper_read_f32_ve(file, isBigEndian);
    text->fixed_length = iohelper_read_u32_ve(file, isBigEndian);
    text->italics = iohelper_read_f32_ve(file, isBigEndian);
    text->size = iohelper_read_f32_ve(file, isBigEndian);
    text->markup = iohelper_read_u8(file);
    text->caps_mode = iohelper_read_u32_ve(file, isBigEndian);
    return text;
}

void hmx_text_write(FILE *file, HX_TEXT *text, bool isBigEndian) {

}

void hmx_text_cleanup(HX_TEXT *text) {
    hmx_metadata_cleanup(text->meta);
    hmx_draw_cleanup(text->draw);
    hmx_transform_cleanup(text->transform);
    hmx_string_cleanup(text->font);
    hmx_string_cleanup(text->text);
}

void hmx_text_print(HX_TEXT *text) {
    printf("VERSION: %d\n", text->version);
    printf("\n");
    hmx_metadata_print(text->meta);
    printf("\n");
    hmx_draw_print(text->draw);
    printf("\n");
    hmx_transform_print(text->transform);
    printf("\n");
    printf("FONT: %s\n", hmx_string_cstring(text->font));
    printf("ALIGNMENT: %d\n", text->align);
    printf("TEXT: %s\n", hmx_string_cstring(text->text));
    #ifdef BAILEARLY
    return;
    #endif
    printf("COLOR: "); hmx_color_4f_print(text->color); printf("\n");
    printf("WRAP WIDTH: %f\n", text->wrap_width);
    printf("SPACING: %f\n", text->leading);
    printf("FIXED LENGTH: %d\n", text->fixed_length);
    printf("ITALIC STRENGTH: %f\n", text->italics);
    printf("SIZE: %f\n", text->size);
    printf("MARKUP? %s\n", text->markup ? "YES" : "NO");
    printf("CAPS MODE: %d\n", text->caps_mode);
}
