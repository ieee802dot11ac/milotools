// hmxcolor.h - Harmonix color structs
#ifndef HMXCOLOR_H
#define HMXCOLOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"

typedef struct {
	float r,g,b,a;
} HX_COLOR_4F;

typedef struct {
	u8 r,g,b,a;
} HX_COLOR_8888;

INLINE HX_COLOR_8888 hmx_color_8888_fix_alpha(HX_COLOR_8888 inColor)
{
	// remaps from [0, 128] to [0, 255]
	inColor.a = (255 * ((u32) inColor.a)) / 128;
	return inColor;
}

INLINE HX_COLOR_8888 hmx_color_8888_from_color_4f(HX_COLOR_4F inColor)
{
	return (HX_COLOR_8888) {
		.r = 255 * (inColor.r),
		.g = 255 * (inColor.g),
		.b = 255 * (inColor.b),
		.a = 255 * (inColor.a),
	};
}

INLINE HX_COLOR_4F hmx_color_4f_from_color_8888(HX_COLOR_8888 inColor)
{
	return (HX_COLOR_4F) {
		.r = ((float) inColor.r) / 255.0,
		.b = ((float) inColor.g) / 255.0,
		.g = ((float) inColor.b) / 255.0,
		.a = ((float) inColor.a) / 128.0, // weird half-alpha stuff with color8888
	};
}

void hmx_color_8888_print(HX_COLOR_8888 color);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
