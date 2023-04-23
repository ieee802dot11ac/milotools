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
	kConstraintFastBillboardXYZ,
	CONSTRAINT_ENUM_AMOUNT
} CONSTRAINT_ENUM; // i'm just stealing shit at this point, sorry cisco

extern char const *const CONSTRAINT_ENUM_NAME[CONSTRAINT_ENUM_AMOUNT];

typedef enum
{
	kVolumeEmpty,
	kVolumeTriangles,
	kVolumeBSP,
	kVolumeBox,
	VOLUME_ENUM_AMOUNT
} VOLUME_ENUM;

extern char const *const VOLUME_ENUM_NAME[VOLUME_ENUM_AMOUNT];

typedef enum
{
	kMutableNone = 0,
	kMutableVerts = 31,
	kMutableFaces = 32,
	kMutableAll = 63,
} MUTABLE_ENUM;

#define MUTABLE_ENUM_AMOUNT 4

typedef enum
{
    kLightPoint,
    kLightDirectional,
    kLightFakeSpot,
    kLightFloorSpot,
    kLightShadowRef
} LIGHT_TYPE_ENUM;

extern char const *const MUTABLE_ENUM_NAME[MUTABLE_ENUM_AMOUNT];


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
