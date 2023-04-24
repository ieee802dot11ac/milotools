#include "imhex/patterns/string.hexpat"
#include "imhex/patterns/matrix.hexpat"

enum CONSTRAINT_ENUM : u32 {
	kConstraintNone,
	kConstraintLocalRotate,
	kConstraintParentWorld,
	kConstraintLookAtTarget,
	kConstraintShadowTarget,
	kConstraintBillboardZ,
	kConstraintBillboardXZ,
	kConstraintBillboardXYZ,
	kConstraintFastBillboardXYZ
};

struct HX_TRANSFORM {
	u32 version;
	HX_MATRIX localTransform;
	HX_MATRIX worldTransform;

	u32 transCount;
	HX_STRING transObjects[transCount];

	CONSTRAINT_ENUM constraint;
	HX_STRING targetRef;
	bool preserveScale;
	HX_STRING parentRef;
};
