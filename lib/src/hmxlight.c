#include "hmxlight.h"
#include "iohelper.h"
#include "hmxtransform.h"
#include <stdio.h>


HX_LIGHT hmx_light_load(FILE *file)
{
	HX_LIGHT light;
	fread(&light, sizeof(u32), 1, file);
    light.trans = hmx_transform_load(file);
    fread(&light.color, 4, 6, file);
	return light;
}

void hmx_light_print(HX_LIGHT light)
{
    printf("VERSION: %u\n", light.version);
    hmx_transform_print(light.trans);
    printf("COLOR: R %f G %f B %f\n", light.color.r, light.color.g, light.color.b);
    printf("INTENSITY: %f\n", light.intensity);
    printf("RANGE: %f\n", light.range);
    printf("TYPE: %d\n", light.type);
}
