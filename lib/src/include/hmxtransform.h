// hmxtrans.h - Harmonix Transform structure and functions
#ifndef HMXTRANS_H
#define HMXTRANS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include "hmxstring.h"

typedef enum
{
	kConstraintNone,
	kConstraintLocalRotate,
	kConstraintParentWorld,
	kConstraintLookAtTarget,
	kConstraintShadowTarget,
	kConstraintBillboardZ,
	kConstraintBillboardXZ,
	kConstraintBillboardXYZ,
	kConstraintFastBillboardXYZ,
	CONSTRAINT_ENUM_AMOUNT
} CONSTRAINT_ENUM;

extern char const *const CONSTRAINT_ENUM_NAME[CONSTRAINT_ENUM_AMOUNT];
typedef struct {
	u32 version; // should be 8
	float localTransMtx[12]; // local transformation matrix
	float worldTransMtx[12]; // world transformation matrix

	// i don't even know but trans so based
	u32 transCount;
	HX_STRING *transObjects; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	CONSTRAINT_ENUM constraint;
	HX_STRING targetRef;
	bool preserveScale;
	HX_STRING parentRef;
} HX_TRANSFORM;


HX_TRANSFORM hmx_transform_load(FILE *file);
void hmx_transform_print(HX_TRANSFORM transform);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
