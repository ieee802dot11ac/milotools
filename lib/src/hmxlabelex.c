#include <stdio.h>
#include <stdlib.h>
#include "hmxlabelex.h"
#include "hmx.h"
#include "hmxstring.h"
#include "iohelper.h"
HX_LABEL_EX *hmx_labelex_load(FILE *file) {
    HX_LABEL_EX *label = malloc(sizeof(HX_LABEL_EX) + 0xFF);
    label->version = iohelper_read_u32(file);
    label->trans = hmx_transform_load(file);
    label->draw = hmx_draw_load(file);
    label->showing = iohelper_read_u8(file);
    label->position.x = iohelper_read_f32(file); label->position.y = iohelper_read_f32(file); label->position.z = iohelper_read_f32(file);
    label->size = iohelper_read_u32(file);
    label->bounding = hmx_primitive_sphere_load(file);
    label->fontType = hmx_string_load(file);
    label->always0 = iohelper_read_u8(file);
    label->text = hmx_string_load(file);
    label->fSize = iohelper_read_f32(file);
    return label;
}
void hmx_labelex_cleanup(HX_LABEL_EX *label) {
    hmx_transform_cleanup(label->trans);
    hmx_draw_cleanup(label->draw);
    hmx_string_cleanup(label->fontType);
    hmx_string_cleanup(label->text);
    free(label);
    return;
}
void hmx_labelex_print(HX_LABEL_EX *label, char* str) {
    sprintf(str, "VERSION: %d\n", label->version);
	sprintf(str, "TRANSFORM:\n"); hmx_transform_print(label->trans, str); sprintf(str, "END TRANSFORM\n");
    sprintf(str, "DRAW:\n"); hmx_draw_print(label->draw, str); sprintf(str, "\nEND DRAW\n");
    sprintf(str, "SHOWING: %d\n", label->showing);
    sprintf(str, "POSITION: X %f Y %f Z %f\n", label->position.x, label->position.y, label->position.z);
    sprintf(str, "SIZE: %d\n", label->size);
    sprintf(str, "SPHERE: X %f Y %f Z %f R %f\n", label->bounding.x, label->bounding.y, label->bounding.z, label->bounding.r);
    sprintf(str, "FONT TYPE: %s\n", hmx_string_cstring(label->fontType));
    sprintf(str, "UNKNOWN BOOL: %d\n", label->always0);
    sprintf(str, "TEXT: %s\n", hmx_string_cstring(label->text));
    sprintf(str, "FSIZE: %f\n", label->fSize);
    sprintf(str, "END LABELEX\n");
    return;
}
