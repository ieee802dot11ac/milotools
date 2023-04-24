#pragma once
#include "imhex/patterns/string.hexpat"
#include "imhex/patterns/draw.hexpat"
#include "imhex/patterns/color.hexpat"

struct HX_FOG {
	float fogStart;
	float fogEnd;
	if (version < 1) {
		padding[4];
	}
	HX_COLOR_4F fogColor; // Guessing alpha is last float?
};

struct HX_ENVIRONMENT {
	s32 version;

	HX_DRAW draw;

	u32 lightsCount;
	HX_STRING lights[lightsCount];

	HX_COLOR_4F ambient_color;

	HX_FOG fog;
	if (version < 1) {
		u32 fogEnable;
	} else {
		u8 fogEnable;
	}

	if (version > 3) {
		u8 animateFromPreset;
	}

	if (version > 4) {
		u8 fadeOut;
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
		u8 useColorAdjust;
	}
};
