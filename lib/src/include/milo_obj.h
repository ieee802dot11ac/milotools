// milo_obj.h - Object file format, but more binary
#ifndef MILO_OBJ_H
#define MILO_OBJ_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>
#include "milo_mesh.h"


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

typedef struct {
	// NEGATIVE values in lists represent
	// a missing value at that point. I don't know if OBJs can *have* "holes"
	// where only one type of vertex is supplied, but this allows them to have
	// it just in case they exist somehow.
	size_t vertexIdCount;
	ssize_t *vertexIds;
	size_t texVertexIdCount;
	ssize_t *texVertexIds;
	size_t normalIdCount;
	ssize_t *normalIds;
} OBJFace;

typedef struct {
	size_t vertexCount;
	Vector3f *vertices;
	size_t texVertexCount;
	Vector2f *texVertices;
	size_t normalsCount;
	Vector3f *normals;
	size_t faceCount;
	OBJFace *faces;
} OBJData;

OBJData obj_from_milo(MILO_MESH_FILE_GH const milomesh);
void obj_write(OBJData const mesh, FILE *const write);
void obj_print(OBJData const mesh);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
