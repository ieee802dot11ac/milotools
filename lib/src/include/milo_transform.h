// milo_trans.h - Harmonix Transform structure and functions
#ifndef MILO_TRANS_H
#define MILO_TRANS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "milo_common.h"
#include "milo_string.h"

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
	MILO_STRING *transObjects; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	CONSTRAINT_ENUM constraint;
	MILO_STRING targetRef;
	bool preserveScale;
	MILO_STRING parentRef;
} MILO_TRANSFORM;


MILO_TRANSFORM milo_transform_load(FILE *file);
void milo_transform_print(MILO_TRANSFORM transform);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
