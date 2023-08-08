#include "hmxlight.h"
#include "hmxcolor.h"
#include "iohelper.h"
#include "hmxtransform.h"
#include <stdio.h>


HX_LIGHT hmx_light_load(FILE *file, bool isBigEndian)
{
	HX_LIGHT light;
	light.version = iohelper_read_u32_ve(file, isBigEndian);
	light.transform = hmx_transform_load(file, isBigEndian);
	light.color = hmx_color_3f_load(file, isBigEndian);
	light.intensity = iohelper_read_u32_ve(file, isBigEndian);
	light.range = iohelper_read_u32_ve(file, isBigEndian);
	light.type = iohelper_read_u32_ve(file, isBigEndian);
	return light;
}

void hmx_light_cleanup(HX_LIGHT light)
{
	hmx_transform_cleanup(light.transform);
}

void hmx_light_print(HX_LIGHT light)
{
	printf("VERSION: %u\n", light.version);
	printf("TRANSFORM:\n"); hmx_transform_print(light.transform); printf("END TRANSFORM\n");
	printf("COLOR: "); hmx_color_3f_print(light.color);
	printf("\nINTENSITY: %f\n", light.intensity);
	printf("RANGE: %f\n", light.range);
	printf("TYPE: %d\n", light.type);
}
