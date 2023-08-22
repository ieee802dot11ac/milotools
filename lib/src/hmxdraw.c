#include "hmxprimitive.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "hmxdraw.h"
#include <stdio.h>
#include <stdlib.h>


HX_DRAW hmx_draw_load(FILE *file, bool isBigEndian)
{
	HX_DRAW draw;
	draw.version = iohelper_read_u32_ve(file, isBigEndian);

	draw.showing = iohelper_read_u8(file) != 0;

	if (draw.version < 2) {
		draw.drawableCount = iohelper_read_u32_ve(file, isBigEndian);
		printf("drawable count: %d\n", draw.drawableCount);
		draw.drawables = malloc(sizeof(HX_STRING) * draw.drawableCount);
		for (u32 i = 0; i < draw.drawableCount; ++i)
			draw.drawables[i] = hmx_string_load(file, isBigEndian);
	}
	if (draw.version > 0) draw.bounding = hmx_primitive_sphere_load(file, isBigEndian);
	if (draw.version > 2) draw.draw_order = iohelper_read_f32_ve(file, isBigEndian);
	if (draw.version >= 4) draw.depthpass = iohelper_read_u32_ve(file, isBigEndian);
	return draw;
}

bool hmx_draw_write(FILE *file, HX_DRAW draw, bool isBigEndian) {
	iohelper_write_u32_ve(file, draw.version, isBigEndian);
	iohelper_write_u8(file, draw.showing);
	if (draw.version < 2) {
		iohelper_write_u32_ve(file, draw.drawableCount, isBigEndian);
		draw.drawables = malloc(sizeof(HX_STRING) * draw.drawableCount);
		for (u32 i = 0; i < draw.drawableCount; ++i)
			hmx_string_write(file, draw.drawables[i], isBigEndian);
	}
	if (draw.version > 0) hmx_primitive_sphere_write(file, draw.bounding, isBigEndian);
	if (draw.version > 2) iohelper_write_f32_ve(file, draw.draw_order, isBigEndian);
	if (draw.version >= 4) iohelper_write_u32_ve(file, draw.depthpass, isBigEndian);
	return true;
}

void hmx_draw_cleanup(HX_DRAW draw)
{
	if (draw.drawableCount != 0) {
		for (u32 i = 0; i < draw.drawableCount; ++i) hmx_string_cleanup(draw.drawables[i]);
		free(draw.drawables);
	} else perror("drawables is empty! if it crashes, god help you\n");
}

void hmx_draw_print(HX_DRAW draw)
{
	printf("VERSION: %u\n", draw.version);

	
	printf("SHOWING: %s\n", draw.showing ? "TRUE" : "FALSE");
	if (draw.version < 2) {
		fputs("DRAWABLES: [", stdout);
		for (u32 i = 0; i < draw.drawableCount; ++i) {
			hmx_string_print(draw.drawables[i]);
			if (i != draw.drawableCount - 1)
				fputs(", ", stdout);
		}
		puts("]");
	}
	if (draw.version > 0) {printf("BOUNDING: "); hmx_primitive_sphere_print(draw.bounding); printf("\n");}
	if (draw.version > 2) printf("DRAW ORDER: %f\n", draw.draw_order);
	if (draw.version >= 4) printf("DEPTH PASS ENUM: %d\n", draw.depthpass);
}
