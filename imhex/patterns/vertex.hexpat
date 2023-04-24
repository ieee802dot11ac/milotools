#pragma once

#include "imhex/patterns/vector.hexpat"

struct HX_VERTEX {
	HX_VEC3F position;	// standard coord system
	HX_VEC3F normal;	// normal coords
	HX_VEC4F color;		// 0-1, *even on alpha*
	HX_VEC2F tex;		// texture coords
} [[static]];
