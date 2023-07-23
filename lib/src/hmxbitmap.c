#include "hmxbitmap.h"
#include "iohelper.h"
#include "hmxstring.h"
#include "hmxcolor.h"
#include <stdio.h>
#include <stdlib.h>

HX_BITMAP hmx_bitmap_load(FILE *file)
{
	HX_BITMAP bmp;
	bool freq = 0;
	bmp.version = iohelper_read_u8(file);

	if (bmp.version == 0) { // header gen
		if (fseek(file, 3, SEEK_CUR), bmp.freqencoding = iohelper_read_u16(file), bmp.freqencoding == 0xD000 || bmp.freqencoding == 0x1500) { // why is freq like this
			freq = true;

			bmp.encoding = RGBA; // freq is always rgba!
			bmp.width = iohelper_read_u16(file);
			bmp.height = iohelper_read_u16(file);
			bmp.bytesPerLine = iohelper_read_u16(file);

			bmp.freqalways_0_1 = iohelper_read_u32(file);
			bmp.freqimg_data_size = iohelper_read_u32(file);
			bmp.freqalways_0_2 = iohelper_read_u32(file);

			bmp.bpp = (bmp.bytesPerLine * 8) / bmp.width; // hacky workaround, necessary cause freq a shit
			bmp.mipmapLevels = 0;
		} else { // amp
			fseek(file, -5, SEEK_CUR); // unfuck that headache
			bmp.bpp = iohelper_read_u8(file);
			bmp.encoding = iohelper_read_u16(file); // *should* always be 3
			bmp.width = iohelper_read_u16(file);
			bmp.height = iohelper_read_u16(file);
			bmp.bytesPerLine = iohelper_read_u16(file);
			fseek(file, 6, SEEK_CUR); // cause 1+1+2+2+2+2 is only 10, not 16
		}
	} else { // everything else just uses the same header lmao
		bmp.bpp = iohelper_read_u8(file);
		bmp.encoding = iohelper_read_u32(file);
		bmp.mipmapLevels = iohelper_read_u8(file);

		bmp.width = iohelper_read_u16(file);
		bmp.height = iohelper_read_u16(file);
		bmp.bytesPerLine = iohelper_read_u16(file);
		fseek(file, 19, SEEK_CUR);
	}
	
	if (bmp.encoding == 3 && (bmp.bpp == 4 || bmp.bpp == 8)) {
		u32 size = 1 << (bmp.bpp + 2); // loop
		bmp.colorPalette = malloc(1 << (bmp.bpp + 2));
		for (u32 i = 0; i < size; i+=4) {
			bmp.colorPalette[i] = hmx_color_8888_load(file);
		}
	} else if (freq) {
		bmp.colorPalette = malloc(1024); // always 256 colors, insert VGA joke here
		for (int i = 0; i < 1024; i+=4) bmp.colorPalette[i] = hmx_color_8888_load(file);
		bmp.freqalways_0_3 = iohelper_read_u32(file);
		bmp.freqcolorcount = iohelper_read_u32(file);
		if (bmp.freqencoding == 0x1500) {
			bmp.texData = malloc(bmp.bytesPerLine*bmp.height);
			for (u32 i = 0; i < bmp.bytesPerLine*bmp.height; i++) {
				bmp.texData[0][i] = iohelper_read_u8(file);
			}
			return bmp;
		}
	}

	u32 w = bmp.width;
	u32 h = bmp.height;
	bmp.texData = malloc(sizeof(u8 *) * (bmp.mipmapLevels + 1));
	for (u32 i = 0; i <= bmp.mipmapLevels; i++) {
		u32 data_size = (w * h * bmp.bpp) / 8;
		bmp.texData[i] = malloc(data_size);
		for (u32 j = 0; j < data_size; j+=4) {
			bmp.texData[i][j] = iohelper_read_u8(file);
		}
		w >>= 1;
		h >>= 1;
	}

	return bmp;
}

void hmx_bitmap_write(FILE *file, HX_BITMAP bmp) {
	iohelper_write_u32(file, bmp.version);
}

void hmx_bitmap_cleanup(HX_BITMAP bmp)
{
	free(bmp.colorPalette);
	free(bmp.texData);
}

void hmx_bitmap_print(HX_BITMAP bmp)
{
	printf("VERSION: %u\n", bmp.version);

	printf("BPP: %u\n", bmp.bpp);
	printf("ENCODING: %s\n", HX_BITMAP_ENCODING_name(bmp.encoding));
	printf("WIDTH: %u\n", bmp.width);
	printf("HEIGHT: %u\n", bmp.height);
	printf("BYTES_PER_LINE: %u\n", bmp.bytesPerLine);

	fputs("COLOR PALETTE: [", stdout);
	for (size_t i = 0; i < hmx_bitmap_len_color_palette(bmp); ++i) {
		hmx_color_8888_print(bmp.colorPalette[i]);
		if (i != hmx_bitmap_len_color_palette(bmp) - 1)
			fputs(", ", stdout);
	}
	puts("]");

	puts("TEXTURE DATA: not printing all of this");
}
