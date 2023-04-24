#include "hmxlight.h"
#include "hmxcolor.h"
#include "iohelper.h"
#include "hmxtransform.h"
#include <stdio.h>


HX_LIGHT hmx_light_load(FILE *file)
{
	HX_LIGHT light;
	light.version = iohelper_read_u32(file);
	light.trans = hmx_transform_load(file);
	light.color = hmx_color_3f_load(file);
	light.intensity = iohelper_read_u32(file);
	light.range = iohelper_read_u32(file);
	light.type = iohelper_read_u32(file);
	return light;
}

void hmx_light_print(HX_LIGHT light)
{
	printf("VERSION: %u\n", light.version);
	printf("TRANSFORM:\n"); hmx_transform_print(light.trans); printf("END TRANSFORM\n");
	printf("COLOR: "); hmx_color_3f_print(light.color);
	printf("\nINTENSITY: %f\n", light.intensity);
	printf("RANGE: %f\n", light.range);
	printf("TYPE: %d\n", light.type);
}
