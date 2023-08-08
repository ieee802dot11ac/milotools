#include "hmxtexture.h"
#include "hmxmetadata.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "hmxbitmap.h"
#include <stdio.h>

HX_TEXTURE hmx_texture_load(FILE *file, bool gdrb, bool isBigEndian)
{
	HX_TEXTURE tex;
	tex.version = iohelper_read_u32_ve(file, isBigEndian);
	if (tex.version > 8) hmx_metadata_load(file, isBigEndian);

	if (tex.version >= 11 && gdrb) tex.some_bool = iohelper_read_u8(file);

	tex.width = iohelper_read_u32_ve(file, isBigEndian);
	tex.height = iohelper_read_u32_ve(file, isBigEndian);
	tex.bpp = iohelper_read_u32_ve(file, isBigEndian);

	tex.bmpName = hmx_string_load(file, isBigEndian);

	if (tex.version >= 8) tex.index_f = iohelper_read_f32_ve(file, isBigEndian);
	tex.index = iohelper_read_u32_ve(file, isBigEndian);

	if (tex.version >= 11 && !gdrb) tex.some_bool2 = iohelper_read_u8(file);

	if (tex.version != 7) tex.useExtPath = (iohelper_read_u8(file) != 0);
	else tex.useExtPathAntiGrav = iohelper_read_u32_ve(file, isBigEndian);
	if (!tex.useExtPath || tex.useExtPathAntiGrav == 0) tex.bmp = hmx_bitmap_load(file, isBigEndian);
	return tex;
}

void hmx_texture_write(FILE *file, HX_TEXTURE tex, bool gdrb, bool isBigEndian) {
	iohelper_write_u32(file, tex.version);

	if (tex.version > 8) hmx_metadata_write(file, tex.meta, isBigEndian);
	if (tex.version >= 11 && gdrb) iohelper_write_u8(file, tex.some_bool);

	iohelper_write_u32_ve(file, tex.width, isBigEndian);
	iohelper_write_u32_ve(file, tex.height, isBigEndian);
	iohelper_write_u32_ve(file, tex.bpp, isBigEndian);

	hmx_string_write(file, tex.bmpName, isBigEndian);

	if (tex.version >= 8) iohelper_write_f32_ve(file, tex.index_f, isBigEndian);
	iohelper_write_u32_ve(file, tex.index, isBigEndian);

	if (tex.version >= 11 && !gdrb) iohelper_write_u8(file, tex.some_bool2);

	if (tex.version != 7) iohelper_write_u8(file, tex.useExtPath);
	else iohelper_write_u32_ve(file, tex.useExtPathAntiGrav, isBigEndian);
	if (!tex.useExtPath || tex.useExtPathAntiGrav == 0) hmx_bitmap_write(file, tex.bmp, isBigEndian);
}

void hmx_texture_cleanup(HX_TEXTURE tex)
{
	hmx_string_cleanup(tex.bmpName);
	hmx_bitmap_cleanup(tex.bmp);
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
