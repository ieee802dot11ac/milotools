// hmxenums.h - Harmonix enums I guess?
#ifndef HMXENUMS_H
#define HMXENUMS_H
#ifdef __cplusplus
extern "C" {
#endif


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
	kConstraintFastBillboardXYZ
} CONSTRAINT_ENUM; // i'm just stealing shit at this point, sorry cisco

typedef enum
{
	kVolumeEmpty,
	kVolumeTriangles,
	kVolumeBSP,
	kVolumeBox
} VOLUME_ENUM;

typedef enum
{
	kMutableNone = 0,
	kMutableVerts = 31,
	kMutableFaces = 32,
	kMutableAll = 63
} MUTABLE_ENUM;


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
