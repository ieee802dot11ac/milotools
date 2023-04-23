using Byte = u8;
struct Color {
    float r;
    float g;
    float b;
};

struct HX_REFERENCE {
    u32 strLen;
    char refName[strLen];
};
enum LIGHT_TYPE_ENUM : u32 {
    kLightPoint,
    kLightDirectional,
    kLightFakeSpot,
    kLightFloorSpot,
    kLightShadowRef
};

struct Trans {
	u32 version; // should be 8
	float localTransMtx[12]; // local transformation matrix
	float worldTransMtx[12]; // world transformation matrix

	// i don't even know but trans so based
	u32 transCount;
	HX_REFERENCE transObjects[transCount]; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	u32 constraint;
	HX_REFERENCE targetRef;
	bool preserveScale;
	HX_REFERENCE parentRef;
} ;

struct LightData {
    u32 version;
    Trans transform;
    Color color;
    float intensity;
    float range;
    LIGHT_TYPE_ENUM type;
};

LightData light @ 0x00;