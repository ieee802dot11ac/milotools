#include "hmxtexture.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "hmxbitmap.h"
#include <stdio.h>

HX_TEXTURE hmx_texture_load(FILE *file)
{
	HX_TEXTURE tex;
	tex.version = iohelper_read_u32(file);

	tex.width = iohelper_read_u32(file);
	tex.height = iohelper_read_u32(file);
	tex.bpp = iohelper_read_u32(file);

	tex.bmpName = hmx_string_load(file);

	tex.index_f = iohelper_read_f32(file);
	tex.index = iohelper_read_u32(file);

	tex.useExtPath = (iohelper_read_u8(file) != 0);

	tex.bmp = hmx_bitmap_load(file);
	return tex;
}

void hmx_texture_print(HX_TEXTURE tex)
{
	printf("Version: %u\n", tex.version);

	printf("Width: %u\n", tex.width);
	printf("Height: %u\n", tex.height);
	printf("BPP: %u\n", tex.bpp);

	fputs("BMP Name: ", stdout);
	hmx_string_print(tex.bmpName);
	putchar('\n');

	printf("IndexF: %f\n", tex.index_f);
	printf("Index: %u\n", tex.index);

	if (tex.useExtPath) {
		puts("UseExtPath: YES");
	} else {
		puts("UseExtPath: No");
	}

	puts("Bitmap: {");
	hmx_bitmap_print(tex.bmp);
	puts("}");
}
