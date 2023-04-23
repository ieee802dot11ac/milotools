#include "milo_bitmap.h"
#include "iohelper.h"
#include "milo_string.h"
#include "milo_color.h"
#include <stdio.h>
#include <stdlib.h>

MILO_BITMAP milo_bitmap_load(FILE *file)
{
	MILO_BITMAP bmp;
	bmp.version = iohelper_readu8(file);

	bmp.bpp = iohelper_readu8(file);
	bmp.encoding = iohelper_readu32(file);
	if (bmp.encoding != RGBA) {
		fprintf(stderr, "Can only handle RGBA encoding for texture bitmaps currently, sorry!\n");
	}

	bmp.mipmapLevels = iohelper_readu8(file);
	bmp.width = iohelper_readu16(file);
	bmp.height = iohelper_readu16(file);
	bmp.bytesPerLine = iohelper_readu16(file);

	fread(bmp.padding, 1, 19, file);

	bmp.colorPalette = malloc(sizeof(MILO_COLOR_8888) * milo_bitmap_len_color_palette(bmp));
	fread(bmp.colorPalette, sizeof(MILO_COLOR_8888), milo_bitmap_len_color_palette(bmp), file);
	bmp.texData = malloc(sizeof(u8) * milo_bitmap_len_tex_data(bmp));
	fread(bmp.texData, sizeof(u8), milo_bitmap_len_tex_data(bmp), file);

	return bmp;
}

void milo_bitmap_print(MILO_BITMAP bmp)
{
	printf("VERSION: %u\n", bmp.version);

	printf("BPP: %u\n", bmp.bpp);
	printf("ENCODING: %s\n", BITMAP_ENCODING_ENUM_name(bmp.encoding));
	printf("WIDTH: %u\n", bmp.width);
	printf("HEIGHT: %u\n", bmp.height);
	printf("BYTES_PER_LINE: %u\n", bmp.bytesPerLine);

	fputs("PADDING: [", stdout);
	for (int i = 0; i < 19; ++i) {
		printf("%u", bmp.padding[i]);
		if (i != 18)
			fputs(", ", stdout);
	}
	puts("]");

	fputs("COLOR PALETTE: [", stdout);
	for (size_t i = 0; i < milo_bitmap_len_color_palette(bmp); ++i) {
		milo_color_8888_print(bmp.colorPalette[i]);
		if (i != milo_bitmap_len_color_palette(bmp) - 1)
			fputs(", ", stdout);
	}
	puts("]");

	puts("TEXTURE DATA: not printing all of this");
}
