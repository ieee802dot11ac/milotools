struct HX_STRING {
    u32 length;
    char s[length];
};

struct Draw {
    u32 version;
    bool showing;
    u32 drawCount;
    HX_STRING drawObjects[drawCount];
    float bounding[4];
};

struct HX_COLOR_4F {
	float r,g,b,a;
};

struct HX_FOG {
    float fogStart;
    float fogEnd;
    if (version < 1) {
    	u32 ignore_num;
    }
    HX_COLOR_4F fogColor; // Guessing alpha is last float?
};

struct EnvironmentData {
    s32 version;

    Draw draw;

    u32 lightsCount;
    HX_STRING lights[lightsCount];

    HX_COLOR_4F ambient_color;

    HX_FOG fog;
    if (version < 1) {
        u32 fogEnable;
    } else {
        bool fogEnable;
    }

    if (version > 3) {
        bool animateFromPreset;
    }

    if (version > 4) {
        bool fadeOut;
        float fadeStart;
        float fadeEnd;

        if (version > 5) {
            float fadeMax;
	}
    }

    if (version > 8) {
        HX_STRING fadeRef; // RndTransformable
        float leftOut;
        float leftOpaque;
        float rightOpaque;
        float rightOut;
    }

    if (version > 7) {
        bool useColorAdjust;
    }
};

EnvironmentData envData @ 0x00;
