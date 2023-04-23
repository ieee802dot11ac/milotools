#include "milo_texture.h"
#include "milo_string.h"
#include "iohelper.h"
#include "milo_bitmap.h"
#include <stdio.h>

MILO_TEXTURE milo_texture_load(FILE *file)
{
	MILO_TEXTURE tex;
	tex.version = iohelper_readu32(file);

	tex.width = iohelper_readu32(file);
	tex.height = iohelper_readu32(file);
	tex.bpp = iohelper_readu32(file);

	tex.bmpName = milo_string_load(file);

	tex.index_f = iohelper_readf(file);
	tex.index = iohelper_readu32(file);

	tex.useExtPath = (iohelper_readu8(file) != 0);

	tex.bmp = milo_bitmap_load(file);
	return tex;
}

void milo_texture_print(MILO_TEXTURE tex)
{
	printf("Version: %u\n", tex.version);

	printf("Width: %u\n", tex.width);
	printf("Height: %u\n", tex.height);
	printf("BPP: %u\n", tex.bpp);

	fputs("BMP Name: ", stdout);
	milo_string_print(tex.bmpName);
	putchar('\n');

	printf("IndexF: %f\n", tex.index_f);
	printf("Index: %u\n", tex.index);

	if (tex.useExtPath) {
		puts("UseExtPath: YES");
	} else {
		puts("UseExtPath: No");
	}

	puts("Bitmap: {");
	milo_bitmap_print(tex.bmp);
	puts("}");
}
