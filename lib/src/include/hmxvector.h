// hmxvector.h - HMX Vector stuff
#ifndef HMXVECTOR_H
#define HMXVECTOR_H

typedef struct {
	// Union-izing these allows you to access like:
	// (Vector2f.x, Vector2f.y) AKA (x, y)
	// (Vector2f.g, Vector2f.a) AKA (g, a)
	// (Vector2f.u, Vector2f.v) AKA (u, v)
	union {
		float x, g, u; // x, grayscale, u
	};
	union {
		float y, a, v; // y, alpha, v
	};
} Vector2f;

typedef struct {
	union {
		float x, r;
	};
	union {
		float y, g;
	};
	union {
		float z, b;
	};
} Vector3f;

typedef struct {
	union {
		float x, r;
	};
	union {
		float y, g;
	};
	union {
		float z, b;
	};
	union {
		float w, a;
	};
} Vector4f;

#include "hmxcommon.h"

Vector2f hmx_vec2f_load(FILE *const file, bool isBigEndian);
Vector3f hmx_vec3f_load(FILE *const file, bool isBigEndian);
Vector4f hmx_vec4f_load(FILE *const file, bool isBigEndian);
bool hmx_vec2f_write(FILE *const file, Vector2f vec, bool isBigEndian);
bool hmx_vec3f_write(FILE *const file, Vector3f vec, bool isBigEndian);
bool hmx_vec4f_write(FILE *const file, Vector4f vec, bool isBigEndian);

#endif
