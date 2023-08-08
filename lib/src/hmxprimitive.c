#include "hmxprimitive.h"
#include "iohelper.h"
#include <stdio.h>


HX_SPHERE hmx_primitive_sphere_load(FILE *file, bool isBigEndian)
{
	HX_SPHERE sphere;
	sphere.x = iohelper_read_f32_ve(file, isBigEndian);
	sphere.y = iohelper_read_f32_ve(file, isBigEndian);
	sphere.z = iohelper_read_f32_ve(file, isBigEndian);
	sphere.r = iohelper_read_f32_ve(file, isBigEndian);

	return sphere;
}

bool hmx_primitive_sphere_write(FILE *file, HX_SPHERE sphere, bool isBigEndian)
{
	iohelper_write_f32_ve(file, sphere.x, isBigEndian);
	iohelper_write_f32_ve(file, sphere.y, isBigEndian);
	iohelper_write_f32_ve(file, sphere.z, isBigEndian);
	iohelper_write_f32_ve(file, sphere.r, isBigEndian);
	return true; // oh
}

void hmx_primitive_sphere_print(HX_SPHERE sphere)
{
	printf("HXSphere(radius=%f, center=(%f,%f,%f))", sphere.r,
							 sphere.x,
							 sphere.y,
							 sphere.z);
}

HX_RECT hmx_primitive_rect_load(FILE *file, bool isBigEndian)
{
	HX_RECT rect;
	rect.x = iohelper_read_f32_ve(file, isBigEndian);
	rect.y = iohelper_read_f32_ve(file, isBigEndian);
	rect.w = iohelper_read_f32_ve(file, isBigEndian);
	rect.h = iohelper_read_f32_ve(file, isBigEndian);
	return rect;
}

bool hmx_primitive_rect_write(FILE *file, HX_RECT rect, bool isBigEndian)
{
	iohelper_write_f32_ve(file, rect.x, isBigEndian);
	iohelper_write_f32_ve(file, rect.y, isBigEndian);
	iohelper_write_f32_ve(file, rect.w, isBigEndian);
	iohelper_write_f32_ve(file, rect.h, isBigEndian);
	return true; // oh
}

void hmx_primitive_rect_print(HX_RECT sphere)
{
	printf("HXRect(pos=(%f,%f), size=(%f,%f))", sphere.x,
							 sphere.y,
							 sphere.w,
							 sphere.h);
}
