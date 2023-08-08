// hmxtransanim.h - Harmonix animations for transforms
#ifndef HMXTRANSANIM_H
#define HMXTRANSANIM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxstring.h"
#include "hmxvector.h"
#include "hmxanim.h"

typedef struct {
	Vector4f quat;
	float pos;
} KeyQuart;

typedef struct {
	Vector3f vec3;
	float pos;
} KeyVec3;

typedef struct {
	u32 version;
	HX_ANIM *anim;

	i32 version_min;
	bool unkown; // lol
	u32 string_count;
	HX_STRING *strings;
	i32 num[4]; // why
	HX_STRING trans_object;

	u32 rot_keys_count;
	KeyQuart *rot_keys;

	u32 trans_keys_count;
	KeyVec3 *trans_keys;

	HX_STRING trans_anim_owner;
	bool trans_spline;
	bool repeat_trans;

	u32 scale_keys_count;
    KeyVec3 *scale_keys;
	bool scale_spline;

	bool follow_path;
	bool rot_slerp;
} HX_TRANSFORM_ANIM; // so many version differences

extern HX_TRANSFORM_ANIM *hmx_transanim_load(FILE *file, bool isBigEndian);
extern void hmx_transanim_cleanup(HX_TRANSFORM_ANIM *tnm);
extern void hmx_transanim_print(HX_TRANSFORM_ANIM *tnm);

#ifdef __cplusplus
}
#endif
#endif
