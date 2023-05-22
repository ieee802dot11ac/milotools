// hmxtrans.h - Harmonix Transform structure and functions
#ifndef HMXTRANS_H
#define HMXTRANS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include "hmxstring.h"
#include "hmxmatrix.h"

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
	HX_TRANSFORM_CONSTRAINT_AMOUNT
} HX_TRANSFORM_CONSTRAINT;

extern char const *const HX_TRANSFORM_CONSTRAINT_NAME[HX_TRANSFORM_CONSTRAINT_AMOUNT];
typedef struct {
	u32 version; // Amplitude (2003) is 4, Guitar Hero is 8
	HX_MATRIX localTransMtx; // local transformation matrix
	HX_MATRIX worldTransMtx; // world transformation matrix

	// i don't even know but trans so based
	u32 transCount;
	HX_STRING *transObjects; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	HX_TRANSFORM_CONSTRAINT constraint;
	HX_STRING targetRef;
	bool preserveScale;
	HX_STRING parentRef;
} HX_TRANSFORM;


HX_TRANSFORM hmx_transform_load(FILE *file);
void hmx_transform_cleanup(HX_TRANSFORM transform);
void hmx_transform_print(HX_TRANSFORM transform);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
