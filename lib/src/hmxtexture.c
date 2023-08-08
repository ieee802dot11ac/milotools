#include "hmxtexture.h"
#include "hmxmetadata.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "hmxbitmap.h"
#include <stdio.h>

HX_TEXTURE hmx_texture_load(FILE *file, bool gdrb)
{
	HX_TEXTURE tex;
	tex.version = iohelper_read_u32(file);
	if (tex.version > 8) hmx_metadata_load(file);

	if (tex.version >= 11 && gdrb) tex.some_bool = iohelper_read_u8(file);

	tex.width = iohelper_read_u32(file);
	tex.height = iohelper_read_u32(file);
	tex.bpp = iohelper_read_u32(file);

	tex.bmpName = hmx_string_load(file);

	if (tex.version >= 8) tex.index_f = iohelper_read_f32(file);
	tex.index = iohelper_read_u32(file);

	if (tex.version >= 11 && !gdrb) tex.some_bool2 = iohelper_read_u8(file);

	if (tex.version != 7) tex.useExtPath = (iohelper_read_u8(file) != 0);
	else tex.useExtPathAntiGrav = iohelper_read_u32(file);
	if (!tex.useExtPath || tex.useExtPathAntiGrav == 0) tex.bmp = hmx_bitmap_load(file);
	return tex;
}

void hmx_texture_write(FILE *file, HX_TEXTURE tex, bool gdrb) {
	iohelper_write_u32(file, tex.version);

	if (tex.version > 8) hmx_metadata_write(file, tex.meta);
	if (tex.version >= 11 && gdrb) iohelper_write_u8(file, tex.some_bool);

	iohelper_write_u32(file, tex.width);
	iohelper_write_u32(file, tex.height);
	iohelper_write_u32(file, tex.bpp);

	hmx_string_write(file, tex.bmpName);

	if (tex.version >= 8) iohelper_write_f32(file, tex.index_f);
	iohelper_write_u32(file, tex.index);

	if (tex.version >= 11 && !gdrb) iohelper_write_u8(file, tex.some_bool2);

	if (tex.version != 7) iohelper_write_u8(file, tex.useExtPath);
	else iohelper_write_u32(file, tex.useExtPathAntiGrav);
	if (!tex.useExtPath || tex.useExtPathAntiGrav == 0) hmx_bitmap_write(file, tex.bmp);
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
