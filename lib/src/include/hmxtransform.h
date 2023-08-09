// hmxtrans.h - Harmonix Transform structure and functions
#ifndef HMXTRANS_H
#define HMXTRANS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include "hmxstring.h"
#include "hmxmatrix.h"
#include "hmxvector.h"

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
	u32 version; // 5 (Freq/Amp Demo/Amp), 8 (AntiGrav/GH1), 9 (GH2 4-song/GH2/GH2 360/RB1/TBRB/GDRB/RB3)
	HX_MATRIX localTransMtx; // local transformation matrix
	HX_MATRIX worldTransMtx; // world transformation matrix

	// i don't even know but trans so based
	u32 transCount;
	HX_STRING *transObjects; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	HX_TRANSFORM_CONSTRAINT constraint; // >6
	u32 constraint2; // 6
	u32 some_number; // 0 < x < 3
	u32 some_flags; // 3, 4, 5

	u32 unknown1; // <7
	u32 unknown2; // <7
	u32 unknown3; // <7

	bool unknown_bool; // <5

	Vector4f unknown_floats; //  <2

	HX_STRING targetRef; // >5
	bool preserveScale; // >6
	HX_STRING parentRef; // some weird shit, no clue
} HX_TRANSFORM;

#define HX_TRANSFORM_EMPTY ((HX_TRANSFORM) {\
	.version=9,\
	.localTransMtx=(HX_MATRIX){0,0,0, 0,0,0, 0,0,0, 0,0,0},\
	.worldTransMtx=(HX_MATRIX){0,0,0, 0,0,0, 0,0,0, 0,0,0},\
	.transCount=0,\
	.transObjects=NULL,\
	.constraint=kConstraintNone,\
	.constraint2=0,\
	.some_number=0,\
	.some_flags=0,\
	.unknown1=0, .unknown2=0, .unknown3=0,\
	.unknown_bool=false,\
	.unknown_floats=(Vector4f){0,0,0,0},\
	.targetRef=HX_STRING_EMPTY,\
	.preserveScale=true,\
	.parentRef=HX_STRING_EMPTY})

HX_TRANSFORM hmx_transform_load(FILE *file, bool isBigEndian);
bool hmx_transform_write(FILE *file, HX_TRANSFORM transform, bool isBigEndian);
void hmx_transform_cleanup(HX_TRANSFORM transform);
void hmx_transform_print(HX_TRANSFORM transform);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
