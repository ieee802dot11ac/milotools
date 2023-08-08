// common.h - Common utilities / types
#ifndef COMMON_H
#define COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define INLINE static inline

#define ALIGN(n) __attribute__((aligned(n)))
#define PACKED __attribute__((packed))

#define DEPRECATED __attribute__((deprecated))

typedef void      u0;

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t    us;

typedef int8_t   i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef ssize_t  is;

typedef float  f32;
typedef double f64;

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

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
