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
