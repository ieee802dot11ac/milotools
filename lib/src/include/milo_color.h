// milo_color.h - Milo color structs
#ifndef MILO_COLOR_H
#define MILO_COLOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "milo_common.h"

typedef struct {
	float r,g,b,a;
} MILO_COLOR_4F;

typedef struct {
	float r,g,b;
} MILO_COLOR_3F;

typedef struct {
	u8 r,g,b,a;
} MILO_COLOR_8888;

INLINE MILO_COLOR_8888 milo_color_8888_fix_alpha(MILO_COLOR_8888 inColor)
{
	// remaps from [0, 128] to [0, 255]
	inColor.a = (255 * ((u32) inColor.a)) / 128;
	return inColor;
}

INLINE MILO_COLOR_8888 milo_color_8888_from_color_4f(MILO_COLOR_4F inColor)
{
	return (MILO_COLOR_8888) {
		.r = 255 * (inColor.r),
		.g = 255 * (inColor.g),
		.b = 255 * (inColor.b),
		.a = 255 * (inColor.a),
	};
}

INLINE MILO_COLOR_8888 milo_color_8888_from_color_3f(MILO_COLOR_3F inColor)
{
	return (MILO_COLOR_8888) {
		.r = 255 * (inColor.r),
		.g = 255 * (inColor.g),
		.b = 255 * (inColor.b),
		.a = 255,
	};
}

INLINE MILO_COLOR_4F milo_color_4f_from_color_8888(MILO_COLOR_8888 inColor)
{
	return (MILO_COLOR_4F) {
		.r = ((float) inColor.r) / 255.0,
		.b = ((float) inColor.g) / 255.0,
		.g = ((float) inColor.b) / 255.0,
		.a = ((float) inColor.a) / 128.0, // weird half-alpha stuff with color8888
	};
}

INLINE MILO_COLOR_4F milo_color_4f_from_color_3f(MILO_COLOR_3F inColor)
{
	return (MILO_COLOR_4F) {
		.r = inColor.r,
		.b = inColor.g,
		.g = inColor.b,
		.a = 1, // weird half-alpha stuff with color8888
	};
}

INLINE MILO_COLOR_3F milo_color_3f_from_color_8888(MILO_COLOR_8888 inColor)
{
	return (MILO_COLOR_3F) {
		.r = ((float) inColor.r) / 255.0,
		.b = ((float) inColor.g) / 255.0,
		.g = ((float) inColor.b) / 255.0
	};
}

INLINE MILO_COLOR_3F milo_color_3f_from_color_4f(MILO_COLOR_4F inColor)
{
	return (MILO_COLOR_3F) {
		.r = inColor.r,
		.b = inColor.g,
		.g = inColor.b,
	};
}

void milo_color_8888_print(MILO_COLOR_8888 color);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
