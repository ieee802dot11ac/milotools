#include "hmxenums.h"


char const *const CONSTRAINT_ENUM_NAME[CONSTRAINT_ENUM_AMOUNT] = {
	"ConstraintNone",
	"ConstraintLocalRotate",
	"ConstraintParentWorld",
	"ConstraintLookAtTarget",
	"ConstraintShadowTarget",
	"ConstraintBillboardZ",
	"ConstraintBillboardXZ",
	"ConstraintBillboardXYZ",
	"ConstraintFastBillboardXYZ",
};


char const *const VOLUME_ENUM_NAME[VOLUME_ENUM_AMOUNT] = {
	"VolumeEmpty",
	"VolumeTriangles",
	"VolumeBSP",
	"VolumeBox",
};


char const *const MUTABLE_ENUM_NAME[MUTABLE_ENUM_AMOUNT] = {
	"MutableNone",
	"MutableVerts",
	"MutableFaces",
	"MutableAll",
};
