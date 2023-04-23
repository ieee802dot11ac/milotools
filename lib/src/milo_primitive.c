#include "milo_primitive.h"
#include "iohelper.h"
#include <stdio.h>


MILO_SPHERE milo_primitive_sphere_load(FILE *file)
{
	MILO_SPHERE sphere;
	fread(&sphere, 1, sizeof(MILO_SPHERE), file);

	return sphere;
}

void milo_primitive_sphere_print(MILO_SPHERE sphere)
{
	printf("MILOSphere(radius=%f, center=(%f,%f,%f))", sphere.r,
							 sphere.x,
							 sphere.y,
							 sphere.z);
}
