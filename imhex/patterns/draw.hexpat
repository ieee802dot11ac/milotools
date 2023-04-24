#pragma once
#include "imhex/patterns/primitives.hexpat"
#include "imhex/patterns/string.hexpat"

struct HX_DRAW {
	u32 version; // should be 1
	u8 showing;

	u32 drawCount;
	HX_STRING drawObjects[drawCount];
	HX_SPHERE bounding;
};
