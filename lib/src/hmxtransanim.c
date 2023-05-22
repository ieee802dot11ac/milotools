#include "hmx.h"
#include "hmxanim.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>

HX_TRANSFORM_ANIM *hmx_transanim_load(FILE *file) {
	HX_TRANSFORM_ANIM *tnm = malloc(sizeof(HX_TRANSFORM_ANIM));
	tnm->version = iohelper_read_u32(file);
	return tnm;
}

void hmx_transanim_cleanup(HX_TRANSFORM_ANIM *tnm) {
	free(tnm->anim.anim_entries);
	free(tnm->anim.anim_objects);
	free(tnm);
	return;
}

void hmx_transanim_print(HX_TRANSFORM_ANIM *tnm) {
	printf("VERSION: %d\n", tnm->version);
	printf("BEGIN ANIM\n"); hmx_anim_print(tnm->anim); printf("END ANIM\n");
	printf("TRANS OBJECT: %s\n", hmx_string_cstring(tnm->trans_object));
	return;
}
