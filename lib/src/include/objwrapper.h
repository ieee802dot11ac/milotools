// objwrapper.h - Object file format, but more binary
#ifndef HMXOBJ_H
#define HMXOBJ_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>
#include "hmxmesh.h"
#include "hmxcommon.h"

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

OBJData obj_from_hmx(HX_MESH const hxmesh);
void obj_cleanup(OBJData mesh);
void obj_write(OBJData const mesh, FILE *const write);
OBJData obj_read(char *const filename);
void obj_print(OBJData const mesh);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
