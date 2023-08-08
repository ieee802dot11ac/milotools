#include "hmxcolor.h"
#include <stdio.h>

HX_COLOR_8888 hmx_color_8888_load(FILE* file, bool isBigEndian) {
	HX_COLOR_8888 color;
	// idk if endianness matters here, like if it's 4 bytes or if it's a u32?e
	fread(&color, sizeof(u8), 4, file);
	return color;
}

HX_COLOR_4F hmx_color_4f_load(FILE* file, bool isBigEndian) {
	HX_COLOR_4F color;
	// idk if endianness matters here, like if it's 4 bytes or if it's a u32?e
	fread(&color, sizeof(float), 4, file);
	return color;
}

HX_COLOR_3F hmx_color_3f_load(FILE* file, bool isBigEndian) {
	HX_COLOR_3F color;
	// idk if endianness matters here, like if it's 3 bytes or if it's a u24?e
	fread(&color, sizeof(float), 3, file);
	return color;
}

void hmx_color_8888_print(HX_COLOR_8888 color)
{
	color = hmx_color_8888_fix_alpha(color);
	printf("HXColor8888(%u, %u, %u, %u)", color.r,
					      color.g,
					      color.b,
					      color.a);
}

void hmx_color_4f_print(HX_COLOR_4F color)
{
	printf("HXColor4F(%f, %f, %f, %f)", color.r,
					      color.g,
					      color.b,
						  color.a);
}

void hmx_color_3f_print(HX_COLOR_3F color)
{
	printf("HXColor3F(%f, %f, %f)", color.r,
					      color.g,
					      color.b);
}
