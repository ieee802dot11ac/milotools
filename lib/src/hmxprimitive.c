#include "hmxprimitive.h"
#include "iohelper.h"
#include <stdio.h>


HX_SPHERE hmx_primitive_sphere_load(FILE *file)
{
	HX_SPHERE sphere;
	fread(&sphere, 1, sizeof(HX_SPHERE), file);

	return sphere;
}

void hmx_primitive_sphere_print(HX_SPHERE sphere)
{
	printf("HXSphere(radius=%f, center=(%f,%f,%f))", sphere.r,
							 sphere.x,
							 sphere.y,
							 sphere.z);
}

HX_RECT hmx_primitive_rect_load(FILE *file)
{
	HX_RECT rect;
	fread(&rect, 1, sizeof(HX_RECT), file);
	return rect;
}

void hmx_primitive_rect_print(HX_RECT sphere)
{
	printf("HXRect(pos=(%f,%f), size=(%f,%f))", sphere.x,
							 sphere.y,
							 sphere.w,
							 sphere.h);
}
