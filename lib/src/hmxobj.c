#include "hmxobj.h"
#include "hmxcommon.h"
#include "hmxmesh.h"
#include "hmxtriangle.h"
#include "hmxvertex.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


OBJData obj_from_hmx(HX_MESH_FILE_GH const hxmesh)
{
	OBJData objmesh = {
		.vertexCount	= hxmesh.vertCount,
		.vertices	= malloc(hxmesh.vertCount * sizeof(Vector3f)),
		.normalsCount	= hxmesh.vertCount,
		.normals	= malloc(hxmesh.vertCount * sizeof(Vector3f)),
		.texVertexCount	= hxmesh.vertCount,
		.texVertices	= malloc(hxmesh.vertCount * sizeof(Vector2f)),
		.faceCount	= hxmesh.triCount,
		.faces		= malloc(hxmesh.triCount * sizeof(OBJFace)),
	};

	HX_VERTEX *hxverts = hxmesh.vertTable;
	for (size_t i = 0; i < hxmesh.vertCount; ++i) {
		HX_VERTEX hxvert = hxverts[i];
		Vector3f vertex =	{ .x = hxvert.x,
					  .y = hxvert.y,
					  .z = hxvert.z };

		Vector3f normal =	{ .x = hxvert.normX,
					  .y = hxvert.normY,
					  .z = hxvert.normZ };

		Vector4f color =	{ .r = hxvert.r,
					  .g = hxvert.g,
					  .b = hxvert.b,
					  .a = hxvert.a };

		Vector2f tex =		{ .u = hxvert.u,
					  .v = hxvert.v };

		objmesh.vertices[i] = vertex;
		objmesh.normals[i] = normal;
		objmesh.texVertices[i] = tex;
	}

	HX_TRIANGLE *hxtris = hxmesh.triTable;
	for (size_t i = 0; i < hxmesh.triCount; ++i) {
		HX_TRIANGLE hxtri = hxtris[i];
		objmesh.faces[i] = (OBJFace) {
			.vertexIdCount		= 3,
			.vertexIds		= malloc(sizeof(ssize_t) * 3),
			.texVertexIdCount	= 3,
			.texVertexIds		= malloc(sizeof(ssize_t) * 3),
			.normalIdCount		= 3,
			.normalIds		= malloc(sizeof(ssize_t) * 3),
		};

		for (size_t j = 0; j < 3; ++j) {
			objmesh.faces[i].vertexIds[j] = hxtri.vert[j] + 1;
			objmesh.faces[i].texVertexIds[j] = hxtri.vert[j] + 1;
			objmesh.faces[i].normalIds[j] = hxtri.vert[j] + 1;
		}
	}

	return objmesh;
}

void obj_write(OBJData const mesh, FILE *const file)
{
	fputs("# Vertices\n", file);
	for (size_t i = 0; i < mesh.vertexCount; ++i) {
		fprintf(file, "v %f %f %f\n", mesh.vertices[i].x,
					      mesh.vertices[i].y,
					      mesh.vertices[i].z);
	}

	fputs("\n# Texture Coordinates\n", file);
	for (size_t i = 0; i < mesh.texVertexCount; ++i) {
		fprintf(file, "vt %f %f\n", mesh.texVertices[i].u,
					    mesh.texVertices[i].v);
	}

	fputs("\n# Normals\n", file);
	for (size_t i = 0; i < mesh.normalsCount; ++i) {
		fprintf(file, "vn %f %f %f\n", mesh.normals[i].x,
					       mesh.normals[i].y,
					       mesh.normals[i].z);
	}

	fputs("\n# Faces\n", file);
	for (size_t i = 0; i < mesh.faceCount; ++i) {
		OBJFace face = mesh.faces[i];
		fputs("f ", file);
#define MAX(a, b) (a > b ? a : b)
		size_t maxNumVerts = MAX(MAX(face.vertexIdCount, face.texVertexIdCount), face.normalIdCount);
#undef MAX
		for (size_t j = 0; j < maxNumVerts; ++j) {
			ssize_t vertId = (j >= face.vertexIdCount) ? -1 : face.vertexIds[j];
			ssize_t texId = (j >= face.texVertexIdCount) ? -1 : face.texVertexIds[j];
			ssize_t normalId = (j >= face.normalIdCount) ? -1 : face.normalIds[j];

			if (vertId >= 0)
				fprintf(file, "%ld", vertId);
			if (texId >= 0 || normalId >= 0)
				fputc('/', file);
			if (texId >= 0)
				fprintf(file, "%ld", texId);
			if (normalId >= 0)
				fprintf(file, "/%ld", normalId);

			if (j != maxNumVerts - 1)
				fputc(' ', file);
		}
		fputc('\n', file);
	}
}

void obj_print(OBJData const mesh)
{
	puts("OBJ(");

	fputs("Vertices: [", stdout);
	for (size_t i = 0; i < mesh.vertexCount; ++i) {
		printf("(%f, %f, %f)", mesh.vertices[i].x,
				       mesh.vertices[i].y,
				       mesh.vertices[i].z);
		if (i != mesh.vertexCount - 1)
			fputs(", ", stdout);
	}
	fputs("]\n", stdout);

	fputs("Tex: [", stdout);
	for (size_t i = 0; i < mesh.texVertexCount; ++i) {
		printf("(%f, %f)", mesh.texVertices[i].u,
				   mesh.texVertices[i].v);
		if (i != mesh.texVertexCount - 1)
			fputs(", ", stdout);
	}
	fputs("]\n", stdout);

	fputs("Normals: [", stdout);
	for (size_t i = 0; i < mesh.normalsCount; ++i) {
		printf("(%f, %f, %f)", mesh.normals[i].x,
				       mesh.normals[i].y,
				       mesh.normals[i].z);
		if (i != mesh.normalsCount - 1)
			fputs(", ", stdout);
	}
	fputs("]\n", stdout);

	fputs("Faces: [", stdout);
	for (size_t i = 0; i < mesh.faceCount; ++i) {
		fputs("OBJFace([", stdout);
		OBJFace face = mesh.faces[i];
#define MAX(a, b) (a > b ? a : b)
		size_t maxNumVerts = MAX(face.vertexIdCount, face.texVertexIdCount);
#undef MAX
		for (size_t j = 0; j < maxNumVerts; j++) {
			ssize_t vertId = (j >= face.vertexIdCount) ? -1 : face.vertexIds[j];
			ssize_t texId = (j >= face.texVertexIdCount) ? -1 : face.texVertexIds[j];

			if (vertId >= 0)
				printf("%ld", vertId);
			putchar('/');
			if (texId >= 0)
				printf("%ld", texId);

			if (j != maxNumVerts - 1)
				putchar(' ');
		}
		fputs("])", stdout);
		if (i != mesh.faceCount - 1)
			fputs(", ", stdout);
	}
	fputs("]\n)\n", stdout);
}
