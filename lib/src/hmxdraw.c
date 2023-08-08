#include "hmxprimitive.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "hmxdraw.h"
#include <stdio.h>
#include <stdlib.h>


HX_DRAW hmx_draw_load(FILE *file)
{
	HX_DRAW draw;
	draw.version = iohelper_read_u32(file);

	draw.showing = iohelper_read_u8(file) != 0;

	if (draw.version < 2) {
		draw.drawableCount = iohelper_read_u32(file); printf("drawable count: %d\n", draw.drawableCount);
		draw.drawables = malloc(sizeof(HX_STRING) * draw.drawableCount);
		for (u32 i = 0; i < draw.drawableCount; ++i)
			draw.drawables[i] = hmx_string_load(file);
	}
	if (draw.version > 0) draw.bounding = hmx_primitive_sphere_load(file);
	if (draw.version > 2) draw.draw_order = iohelper_read_f32(file);
	if (draw.version >= 4) draw.depthpass = iohelper_read_u32(file);
	return draw;
}

bool hmx_draw_write(FILE *file, HX_DRAW draw) {
	iohelper_write_u32(file, draw.version);
	iohelper_write_u8(file, draw.showing);
	if (draw.version < 2) {
		iohelper_write_u32(file, draw.drawableCount);
		draw.drawables = malloc(sizeof(HX_STRING) * draw.drawableCount);
		for (u32 i = 0; i < draw.drawableCount; ++i)
			hmx_string_write(file, draw.drawables[i]);
	}
	if (draw.version > 0) fwrite(&draw.bounding, sizeof(HX_SPHERE), 1, file);
	if (draw.version > 2) iohelper_write_f32(file, draw.draw_order);
	if (draw.version >= 4) iohelper_write_u32(file, draw.depthpass);
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

	if (!draw.showing)
		printf("SHOWING: FALSE\n");
	else
		printf("SHOWING: TRUE\n");

	fputs("DRAWABLES: [", stdout);
	for (u32 i = 0; i < draw.drawableCount; ++i) {
		hmx_string_print(draw.drawables[i]);
		if (i != draw.drawableCount - 1)
			fputs(", ", stdout);
	}
	puts("]");

	fputs("BOUNDING: ", stdout);
	hmx_primitive_sphere_print(draw.bounding);
}
