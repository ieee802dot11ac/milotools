#include "hmxtransform.h"
#include "hmxcommon.h"
#include "hmxmatrix.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>


HX_TRANSFORM hmx_transform_load(FILE *file)
{
	HX_TRANSFORM transform;
	transform.version = iohelper_read_u32(file);

	transform.localTransMtx = hmx_matrix_load(file);
	transform.worldTransMtx = hmx_matrix_load(file);

	transform.transCount = iohelper_read_u32(file);
	transform.transObjects = malloc(transform.transCount * sizeof(HX_STRING));
	for (u32 i = 0; i < transform.transCount; ++i)
		transform.transObjects[i] = hmx_string_load(file);

	transform.constraint = iohelper_read_u32(file);

	transform.targetRef = hmx_string_load(file);

	transform.preserveScale = (iohelper_read_u8(file) != 0);

	transform.parentRef = hmx_string_load(file);

	return transform;
}

void hmx_transform_cleanup(HX_TRANSFORM transform)
{
	for (u32 i = 0; i < transform.transCount; ++i)
		hmx_string_cleanup(transform.transObjects[i]);
	free(transform.transObjects);

	hmx_string_cleanup(transform.targetRef);
	hmx_string_cleanup(transform.parentRef);
}

void hmx_transform_print(HX_TRANSFORM transform)
{
	printf("VERSION: %u\n", transform.version);

	fputs("LOCAL_MATRIX: ", stdout);
	hmx_matrix_print(transform.localTransMtx);
	fputs("WORLD_MATRIX: ", stdout);
	hmx_matrix_print(transform.worldTransMtx);

	if (transform.transCount != 0) {
		puts("TRANS_OBJECTS:");
		for (u32 i = 0; i < transform.transCount; ++i) {
			hmx_string_print(transform.transObjects[i]);
			fputs(", ", stdout);
		}
	} else {
		puts("TRANS_OBJECTS: NONE");
	}

	fputs("CONSTRAINT: ", stdout);
	puts(HX_TRANSFORM_CONSTRAINT_NAME[transform.constraint]);

	fputs("TARGET_REFERENCE: ", stdout);
	hmx_string_print(transform.targetRef);
	putchar('\n');

	if (transform.preserveScale)
		puts("PRESERVE_SCALE: TRUE");
	else
		puts("PRESERVE_SCALE: FALSE");

	fputs("PARENT_REFERENCE: ", stdout);
	hmx_string_print(transform.parentRef);
	putchar('\n');
}

char const *const HX_TRANSFORM_CONSTRAINT_NAME[HX_TRANSFORM_CONSTRAINT_AMOUNT] = {
	"ConstraintNone",
	"ConstraintLocalRotate",
	"ConstraintParentWorld",
	"ConstraintLookAtTarget",
	"ConstraintShadowTarget",
	"ConstraintBillboardZ",
	"ConstraintBillboardXZ",
	"ConstraintBillboardXYZ",
	"ConstraintFastBillboardXYZ",
};
