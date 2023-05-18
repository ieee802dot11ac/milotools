#include <stdio.h>
#include <stdlib.h>
#include "hmxex.h"
#include "hmx.h"
#include "hmxstring.h"
#include "iohelper.h"

extern HX_BUTTON_EX *hmx_buttonex_load(FILE *file) {
    HX_BUTTON_EX *button = malloc(sizeof(HX_BUTTON_EX) + 0xFF);
    button->version = iohelper_read_u32(file);
    button->trans = hmx_transform_load(file);
    button->draw = hmx_draw_load(file);
    button->unknown = iohelper_read_u32(file);
    button->always0.x = iohelper_read_f32(file); button->always0.y = iohelper_read_f32(file); button->always0.z = iohelper_read_f32(file);
    button->textType = hmx_string_load(file);
    button->showing = iohelper_read_u8(file);
    button->enabled = iohelper_read_u8(file);
    button->hundredSomething = iohelper_read_f32(file);
    button->tenSomething = iohelper_read_f32(file);
    button->buttonText = hmx_string_load(file);
    return button;
}
extern void hmx_buttonex_cleanup(HX_BUTTON_EX *button) {
    hmx_transform_cleanup(button->trans);
    hmx_draw_cleanup(button->draw);
    hmx_string_cleanup(button->textType);
    hmx_string_cleanup(button->buttonText);
    free(button);
    return;
}
extern void hmx_buttonex_print(HX_BUTTON_EX *button) {
    printf("VERSION: %d\n", button->version);
	printf("TRANSFORM:\n"); hmx_transform_print(button->trans); printf("END TRANSFORM\n");
    printf("DRAW:\n"); hmx_draw_print(button->draw); printf("\nEND DRAW\n");
    printf("UNKNOWN: %d", button->unknown);
    printf("VEC3 ALWAYS 0: X %f Y %f Z %f\n", button->always0.x, button->always0.y, button->always0.z);
    printf("TEXT TYPE: %s\n", hmx_string_cstring(button->textType));
    printf("SHOWING: %d\n", button->showing);
    printf("ENABLED: %d\n", button->enabled);
    printf("HUNDRED SOMETHING: %f\n", button->hundredSomething);
    printf("TEN SOMETHING: %f\n", button->tenSomething);
    printf("TEXT: %s\n", hmx_string_cstring(button->buttonText));
    printf("END BUTTONEX");
    return;
}

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
