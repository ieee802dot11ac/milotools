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
void hmx_labelex_print(HX_LABEL_EX *label) {
    printf("VERSION: %d\n", label->version);
	printf("TRANSFORM:\n"); hmx_transform_print(label->trans); printf("END TRANSFORM\n");
    printf("DRAW:\n"); hmx_draw_print(label->draw); printf("\nEND DRAW\n");
    printf("SHOWING: %d\n", label->showing);
    printf("POSITION: X %f Y %f Z %f\n", label->position.x, label->position.y, label->position.z);
    printf("SIZE: %d\n", label->size);
    printf("SPHERE: X %f Y %f Z %f R %f\n", label->bounding.x, label->bounding.y, label->bounding.z, label->bounding.r);
    printf("FONT TYPE: %s\n", hmx_string_cstring(label->fontType));
    printf("UNKNOWN BOOL: %d\n", label->always0);
    printf("TEXT: %s\n", hmx_string_cstring(label->text));
    printf("FSIZE: %f\n", label->fSize);
    printf("END LABELEX\n");
    return;
}
