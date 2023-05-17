#include "hmxprimitive.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "hmxdraw.h"
#include <stdio.h>
#include <stdlib.h>


HX_DRAW hmx_draw_load(FILE *file)
{
	HX_DRAW draw;
	draw.version = iohelper_read_u32(file); // should be 1

	draw.showing = iohelper_read_u8(file) != 0;

	draw.drawableCount = iohelper_read_u32(file);
	draw.drawables = malloc(sizeof(HX_STRING) * draw.drawableCount);
	for (u32 i = 0; i < draw.drawableCount; ++i)
		draw.drawables[i] = hmx_string_load(file);

	draw.bounding = hmx_primitive_sphere_load(file);

	return draw;
}

void hmx_draw_cleanup(HX_DRAW draw)
{
	for (u32 i = 0; i < draw.drawableCount; ++i)
		hmx_string_cleanup(draw.drawables[i]);
	free(draw.drawables);
}

void hmx_draw_print(HX_DRAW draw, char* str)
{
	sprintf(str, "VERSION: %u\n", draw.version);

	if (!draw.showing)
		sprintf(str, "SHOWING: FALSE\n");
	else
		sprintf(str, "SHOWING: TRUE\n");

	sprintf(str, "DRAWABLES: [");
	for (u32 i = 0; i < draw.drawableCount; ++i) {
		strcat(str, hmx_string_cstring(draw.drawables[i]));
		if (i != draw.drawableCount - 1)
			sprintf(str, ", ");
	}
	sprintf(str, "]");

	sprintf(str, "BOUNDING: ");
	hmx_primitive_sphere_print(draw.bounding);
}
