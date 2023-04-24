#include "imhex/patterns/color.hexpat"

enum BITMAP_ENCODING : u32 {
	RGBA = 3,
	DXT1_BC1 = 8,
	DXT5_BC3 = 24,
	ATI2_BC5 = 32,
	TPL_CMP = 72,
	TPL_CMP_ALPHA = 328
};

fn mipmapped_pixel_count(u32 width, u32 height, u8 mipmapLevels)
{
	u64 layerPixels = width * height;
	if (mipmapLevels == 0) {
		return layerPixels;
	}
	return layerPixels + mipmapped_pixel_count(width>>1, height>>1, mipmapLevels - 1);
};

struct HX_BITMAP {
	u8 version;
	u8 bpp;
	BITMAP_ENCODING encoding;
	u8 mipmapLevels;
	u16 width;
	u16 height;
	u16 bytesPerLine;

	padding[19];

	HX_COLOR_8888 colorPalette[1 << bpp];

	if (encoding == BITMAP_ENCODING::RGBA) {
		u64 pixelCount = mipmapped_pixel_count(width, height, mipmapLevels);
		if (bpp == 4) {
			HX_PALCOLOR_BPP4_RGBA texData[pixelCount / 2]; // 2 pixels per palcolor
		} else if (bpp == 8) {
			HX_PALCOLOR_BPP8_RGBA texData[pixelCount]; // 1 pixel per palcolor
		}
	}
};
