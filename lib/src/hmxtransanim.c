#include "hmx.h"
#include "hmxanim.h"
#include "hmxcommon.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>

HX_TRANSFORM_ANIM *hmx_transanim_load(FILE *file) {
	HX_TRANSFORM_ANIM *tnm = malloc(sizeof(HX_TRANSFORM_ANIM));
	tnm->version = iohelper_read_u32(file);
	tnm->anim = hmx_anim_load(file);
	tnm->trans_object = hmx_string_load(file);
	tnm->rot_keys_count = iohelper_read_u32(file);
	if (tnm->rot_keys_count > 0) {
		for (u32 i = 0; i < tnm->rot_keys_count; i++) {
			tnm->rot_keys[i].quat.w = iohelper_read_f32(file);
			tnm->rot_keys[i].quat.x = iohelper_read_f32(file);
			tnm->rot_keys[i].quat.y = iohelper_read_f32(file);
			tnm->rot_keys[i].quat.z = iohelper_read_f32(file);
			tnm->rot_keys[i].pos = iohelper_read_f32(file);
		}
	} else tnm->rot_keys = NULL;
	tnm->trans_keys_count = iohelper_read_u32(file);
	if (tnm->trans_keys_count > 0) {
		for (u32 i = 0; i < tnm->trans_keys_count; i++) {
			tnm->trans_keys[i].vec3.x = iohelper_read_f32(file);
			tnm->trans_keys[i].vec3.y = iohelper_read_f32(file);
			tnm->trans_keys[i].vec3.z = iohelper_read_f32(file);
			tnm->trans_keys[i].pos = iohelper_read_f32(file);
		}
	} else tnm->trans_keys = NULL;
	tnm->trans_anim_owner = hmx_string_load(file);
	tnm->trans_spline = iohelper_read_u8(file);
	tnm->repeat_trans = iohelper_read_u8(file);
	tnm->scale_keys_count = iohelper_read_u32(file);
	if (tnm->scale_keys_count > 0) {
		for (u32 i = 0; i < tnm->scale_keys_count; i++) {
			tnm->scale_keys[i].vec3.x = iohelper_read_f32(file);
			tnm->scale_keys[i].vec3.y = iohelper_read_f32(file);
			tnm->scale_keys[i].vec3.z = iohelper_read_f32(file);
			tnm->scale_keys[i].pos = iohelper_read_f32(file);
		}
	} else tnm->scale_keys = NULL;
	tnm->scale_spline = iohelper_read_u8(file);
	tnm->follow_path = iohelper_read_u8(file);
	tnm->rot_slerp = iohelper_read_u8(file);
	return tnm;
}

void hmx_transanim_cleanup(HX_TRANSFORM_ANIM *tnm) {
	free(tnm->anim->anim_entries);
	free(tnm->anim->anim_objects);
	free(tnm->anim);
	free(tnm->rot_keys);
	free(tnm->trans_keys);
	free(tnm->scale_keys);
	free(tnm);
	return;
}

void hmx_transanim_print(HX_TRANSFORM_ANIM *tnm) {
	printf("VERSION: %d\n", tnm->version);
	printf("BEGIN ANIM\n"); hmx_anim_print(tnm->anim); printf("END ANIM\n");
	printf("TRANS OBJECT: %s\n", hmx_string_cstring(tnm->trans_object));
	printf("ROTATION KEY COUNT: %d\nROTATION KEYS:\n", tnm->rot_keys_count);
	if (tnm->rot_keys_count > 0) {
		for (u32 i = 0; i < tnm->rot_keys_count; i++) {
			printf("KeyQuart[%d](quat = WXYZ %f%f%f%f, pos = %f)\n", i,
			tnm->rot_keys[i].quat.w,
			tnm->rot_keys[i].quat.x,
			tnm->rot_keys[i].quat.y,
			tnm->rot_keys[i].quat.z,
			tnm->rot_keys[i].pos);
		}
	} else printf("NO ROTATION KEYS\n");
	printf("TRANSFORMATION KEY COUNT: %d\nTRANSFORMATION KEYS:\n", tnm->trans_keys_count);
	if (tnm->trans_keys_count > 0) {
		for (u32 i = 0; i < tnm->trans_keys_count; i++) {
			printf("KeyVec3[%d](vec3 = XYZ %f%f%f, pos = %f)\n", i,
			tnm->trans_keys[i].vec3.x,
			tnm->trans_keys[i].vec3.y,
			tnm->trans_keys[i].vec3.z,
			tnm->trans_keys[i].pos);
		}
	} else printf("NO TRANSFORMATION KEYS\n");
	printf("TRANS ANIM OWNER: %s\n", hmx_string_cstring(tnm->trans_anim_owner));
	printf("TRANS SPLINE: %d\n", tnm->trans_spline);
	printf("REPEAT TRANSFORM: %d\n", tnm->repeat_trans);
	printf("SCALE KEY COUNT: %d\nSCALE KEYS:\n", tnm->scale_keys_count);
	if (tnm->scale_keys_count > 0) {
		for (u32 i = 0; i < tnm->scale_keys_count; i++) {
			printf("KeyVec3[%d](vec3 = XYZ %f%f%f, pos = %f)\n", i,
			tnm->scale_keys[i].vec3.x,
			tnm->scale_keys[i].vec3.y,
			tnm->scale_keys[i].vec3.z,
			tnm->scale_keys[i].pos);
		}
	} else printf("NO SCALE KEYS\n");
	printf("SCALE SPLINE: %d\n", tnm->scale_spline);
	printf("FOLLOW PATH: %d\n", tnm->follow_path);
	printf("ROTATION SLERP: %d\n", tnm->rot_slerp);
	return;
}
