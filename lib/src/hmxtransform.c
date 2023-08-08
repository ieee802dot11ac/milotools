#include "hmxtransform.h"
#include "hmxcommon.h"
#include "hmxmatrix.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>


HX_TRANSFORM hmx_transform_load(FILE *file, bool isBigEndian)
{
	HX_TRANSFORM transform;
	transform.version = iohelper_read_u32_ve(file, isBigEndian);

	transform.localTransMtx = hmx_matrix_load(file, isBigEndian);
	transform.worldTransMtx = hmx_matrix_load(file, isBigEndian);

	if (transform.version < 9) {
		transform.transCount = iohelper_read_u32_ve(file, isBigEndian);
		transform.transObjects = malloc(transform.transCount * sizeof(HX_STRING));
		for (u32 i = 0; i < transform.transCount; ++i)
			transform.transObjects[i] = hmx_string_load(file, isBigEndian); // these are cstrings in freq but we're just gonna hope we don't have that problem
	}

	if (transform.version > 6) transform.constraint = iohelper_read_u32_ve(file, isBigEndian);
	else if (transform.version == 6) transform.constraint2 = iohelper_read_u32_ve(file, isBigEndian);
	else if (transform.version < 3 && transform.version > 0) transform.some_number = iohelper_read_u32_ve(file, isBigEndian);
	else transform.some_flags = iohelper_read_u32_ve(file, isBigEndian);

	if (transform.version < 7) {
		transform.unknown1 = iohelper_read_u32_ve(file, isBigEndian);
		transform.unknown2 = iohelper_read_u32_ve(file, isBigEndian);
		transform.unknown3 = iohelper_read_u32_ve(file, isBigEndian);
	}

	if (transform.version < 5) transform.unknown_bool = iohelper_read_u8(file);

	if (transform.version < 2) {
		transform.unknown_floats.r = iohelper_read_f32_ve(file, isBigEndian);
		transform.unknown_floats.g = iohelper_read_f32_ve(file, isBigEndian);
		transform.unknown_floats.b = iohelper_read_f32_ve(file, isBigEndian);
		transform.unknown_floats.a = iohelper_read_f32_ve(file, isBigEndian);
	}
	
	if (transform.version > 5) transform.targetRef = hmx_string_load(file, isBigEndian);

	if (transform.version > 6) transform.preserveScale = (iohelper_read_u8(file) != 0);

	transform.parentRef = hmx_string_load(file, isBigEndian); // some weird shit going on in the notes. this is basically it, though

	return transform;
}

bool hmx_transform_write(FILE *file, HX_TRANSFORM transform, bool isBigEndian) {
	iohelper_write_u32(file, transform.version);
	hmx_matrix_write(file, transform.localTransMtx, isBigEndian);
	hmx_matrix_write(file, transform.worldTransMtx, isBigEndian);
	if (transform.version < 9) {
		iohelper_write_u32(file, transform.transCount);
		for (u32 i = 0; i < transform.transCount; ++i)
			hmx_string_write(file, transform.transObjects[i], isBigEndian); // these are cstrings in freq but we're just gonna hope we don't have that problem
	}

	if (transform.version > 6) iohelper_write_u32_ve(file, transform.constraint, isBigEndian);
	else if (transform.version == 6) iohelper_write_u32_ve(file, transform.constraint2, isBigEndian);
	else if (transform.version < 3 && transform.version > 0) iohelper_write_u32_ve(file, transform.some_number, isBigEndian);
	else iohelper_write_u32_ve(file, transform.some_flags, isBigEndian);

	if (transform.version < 7) {
		iohelper_write_u32_ve(file, transform.unknown1, isBigEndian);
		iohelper_write_u32_ve(file, transform.unknown2, isBigEndian);
		iohelper_write_u32_ve(file, transform.unknown3, isBigEndian);
	}

	if (transform.version < 5) iohelper_write_u8(file, transform.unknown_bool);

	if (transform.version < 2) {
		iohelper_write_f32_ve(file, transform.unknown_floats.r, isBigEndian);
		iohelper_write_f32_ve(file, transform.unknown_floats.g, isBigEndian);
		iohelper_write_f32_ve(file, transform.unknown_floats.b, isBigEndian);
		iohelper_write_f32_ve(file, transform.unknown_floats.a, isBigEndian);
	}

	if (transform.version > 5) hmx_string_write(file, transform.targetRef, isBigEndian);

	if (transform.version > 6) iohelper_write_u8(file, transform.preserveScale);

	hmx_string_write(file, transform.parentRef, isBigEndian);

	return true;
}

void hmx_transform_cleanup(HX_TRANSFORM transform) {
	for (u32 i = 0; i < transform.transCount; ++i)
		hmx_string_cleanup(transform.transObjects[i]);
	free(transform.transObjects);

	hmx_string_cleanup(transform.targetRef);
	hmx_string_cleanup(transform.parentRef);
}

void hmx_transform_print(HX_TRANSFORM transform) {
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
