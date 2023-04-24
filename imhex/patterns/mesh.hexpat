struct HX_STRING {
	u32 strLen;
	char refName[strLen];
};

struct HX_SPHERE {
	float x;
	float y;
	float z;
	float r;
};


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

enum VOLUME_ENUM : u32 {
	kVolumeEmpty,
	kVolumeTriangles,
	kVolumeBSP,
	kVolumeBox
};

enum MUTABLE_ENUM : u32 {
	kMutableNone = 0,
	kMutableVerts = 31,
	kMutableFaces = 32,
	kMutableAll = 63
};

struct HX_TRANS {
	u32 version; // should be 8
	HX_MATRIX localTransform; // local transformation 
	HX_MATRIX worldTransform; // world transformation 

	// i don't even know but trans so based
	u32 transCount;
	HX_STRING transObjects[transCount]; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	CONSTRAINT_ENUM constraint;
	HX_STRING targetRef;
	bool preserveScale;
	HX_STRING parentRef;
};

struct HX_VERT_GH {
	float x; // standard coord system
	float y; // standard coord system
	float z; // standard coord system
	float normX; // normal map coords
	float normY; // normal map coords
	float normZ; // normal map coords
	float r; // 0-1
	float g; // 0-1
	float b; // 0-1
	float a; // 0-1, usually like half cause hmx
	float u; // texture space stuff
	float v; // texture space stuff
};

struct HX_TRI_GH {
	u16 vert[3];
};

struct HX_MESH_FILE_GH {
	u32 version; // should be 25
	HX_TRANS transform; // love me some 3d environments

	// bounding stuff. textures. fun times!
	HX_SPHERE bounding;

	u8 _unknown0[9];

	HX_STRING matName;

	HX_STRING geometryOwnerName;
	MUTABLE_ENUM mutableParts;
	VOLUME_ENUM volume;
	u8 bsp; // no clue

	u32 vertCount;
	HX_VERT_GH vertTable[vertCount];
	u32 triCount;
	HX_TRI_GH triTable[triCount];
	u32 _unknown1[16];
};

HX_MESH_FILE_GH meshFile @ 0x00;
