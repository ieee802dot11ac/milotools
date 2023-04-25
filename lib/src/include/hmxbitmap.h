// hmxbitmap.h - Harmonix bitmap format
#ifndef HMXBITMAP_H
#define HMXBITMAP_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>
#include "hmxcommon.h"
#include "hmxcolor.h"

typedef enum {
	RGBA = 3,
	DXT1_BC1 = 8,
	DXT5_BC3 = 24,
	ATI2_BC5 = 32,
	TPL_CMP = 72,
	TPL_CMP_ALPHA = 328
} HX_BITMAP_ENCODING;

INLINE char *HX_BITMAP_ENCODING_name(HX_BITMAP_ENCODING encoding)
{
	switch (encoding) {
	case RGBA:
		return "RGBA";
	case DXT1_BC1:
		return "DXT1_BC1";
	case DXT5_BC3:
		return "DXT5_BC3";
	case ATI2_BC5:
		return "ATI2_BC5";
	case TPL_CMP:
		return "TPL_CMP";
	case TPL_CMP_ALPHA:
		return "TPL_CMP_ALPHA";
	}
	return "UNKNOWN";
}

typedef struct {
	u8 version;
	u8 bpp;
	HX_BITMAP_ENCODING encoding;
	u8 mipmapLevels;
	u16 width;
	u16 height;
	u16 bytesPerLine;

	u8 padding[19];

	// Neither of these need sizes, since they're calculated from the bpp
	// and mipmap levels and stuff (see hmx_bitmap_len_color_palette and
	// hmx_bitmap_len_tex_data).
	HX_COLOR_8888 *colorPalette;

	u8 *texData;
} HX_BITMAP;


INLINE size_t hmx_bitmap_len_color_palette(HX_BITMAP bmp)
{
	return (1 << bmp.bpp);
}

INLINE size_t hmx_bitmap_len_tex_data(HX_BITMAP bmp)
{
	size_t pixels = 0;
	for (u8 i = 0; i <= bmp.mipmapLevels; ++i) {
		pixels += bmp.width * bmp.height;

		bmp.width >>= 1;
		bmp.height >>= 1;
	}

	return (pixels * bmp.bpp) / 8;
}

HX_BITMAP hmx_bitmap_load(FILE *file);
void hmx_bitmap_cleanup(HX_BITMAP bmp);
void hmx_bitmap_print(HX_BITMAP bmp);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
