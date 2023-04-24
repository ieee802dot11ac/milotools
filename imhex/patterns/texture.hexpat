#include "string.hexpat"
#include "bitmap.hexpat"

struct HX_TEXTURE {
	u32 version;
	u32 width;
	u32 height;
	u32 bpp;
	HX_STRING bmpName;
	float index_f;
	u32 index;
	u8 useExtPath;
	HX_BITMAP bmp;
};
TexFile texfile @ 0x00;
