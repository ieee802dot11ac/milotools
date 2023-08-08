#include <stdio.h>
#include <stdlib.h>
#include "hmx.h"
#include "hmxanim.h"
#include "hmxstring.h"
#include "iohelper.h"

HX_ANIM *hmx_anim_load(FILE *file, bool isBigEndian) {
	HX_ANIM *anim = malloc(sizeof(HX_ANIM));
	anim->version = iohelper_read_u32_ve(file, isBigEndian);
	anim->anim_entry_count = iohelper_read_u32_ve(file, isBigEndian);
	if (anim->anim_entry_count != 0) {
		anim->anim_entries = malloc(sizeof(AnimEntry) * anim->anim_entry_count);
		for (u32 i = 0; i < anim->anim_entry_count; i++) {
			anim->anim_entries[i].name = hmx_string_load(file, isBigEndian);
			anim->anim_entries[i].f1 = iohelper_read_f32_ve(file, isBigEndian);
			anim->anim_entries[i].f2 = iohelper_read_f32_ve(file, isBigEndian);
		}
	} else anim->anim_entries = NULL;
	if (anim->anim_count != 0) {
		anim->anim_objects = malloc(sizeof(HX_STRING) * anim->anim_count);
		for (u32 i = 0; i < anim->anim_count; i++) {
			anim->anim_objects[i] = hmx_string_load(file, isBigEndian);
		}
	} else anim->anim_objects = NULL;
	return anim;
}

void hmx_anim_cleanup(HX_ANIM *anim) {
	free(anim->anim_entries);
	free(anim->anim_objects);
	return;
}

void hmx_anim_print(HX_ANIM *anim) {
	printf("VERSION: %d\n", anim->version);
	printf("ANIM ENTRY COUNT: %d\n", anim->anim_entry_count);
	if (anim->anim_entry_count > 0) {
		for (u32 i = 0; i < anim->anim_entry_count; i++) \
			printf("AnimEntry[%d](name = %s, f1 = %f, f2 = %f)\n", \
			i, hmx_string_cstring(anim->anim_entries[i].name), \
			anim->anim_entries[i].f1, anim->anim_entries[i].f2);
	} else printf("NO ANIM ENTRIES\n");
	printf("ANIM COUNT: %d\n", anim->anim_count);
	if (anim->anim_count > 0) {
		for (u32 i = 0; i < anim->anim_count; i++) {
			printf("ANIM OBJECT %d: %s\n", i, hmx_string_cstring(anim->anim_objects[i]));
		}
	} else printf("NO ANIM OBJECTS\n");
	return;
}
