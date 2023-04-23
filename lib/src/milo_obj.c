#include "milo_obj.h"
#include "milo_common.h"
#include "milo_mesh.h"
#include "milo_triangle.h"
#include "milo_vertex.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


OBJData obj_from_milo(MILO_MESH_FILE_GH const milomesh)
{
	OBJData objmesh = {
		.vertexCount	= milomesh.vertCount,
		.vertices	= malloc(milomesh.vertCount * sizeof(Vector3f)),
		.normalsCount	= milomesh.vertCount,
		.normals	= malloc(milomesh.vertCount * sizeof(Vector3f)),
		.texVertexCount	= milomesh.vertCount,
		.texVertices	= malloc(milomesh.vertCount * sizeof(Vector2f)),
		.faceCount	= milomesh.triCount,
		.faces		= malloc(milomesh.triCount * sizeof(OBJFace)),
	};

	MILO_VERTEX *miloverts = milomesh.vertTable;
	for (size_t i = 0; i < milomesh.vertCount; ++i) {
		MILO_VERTEX milovert = miloverts[i];
		Vector3f vertex =	{ .x = milovert.x,
					  .y = milovert.y,
					  .z = milovert.z };

		Vector3f normal =	{ .x = milovert.normX,
					  .y = milovert.normY,
					  .z = milovert.normZ };

		Vector4f color =	{ .r = milovert.r,
					  .g = milovert.g,
					  .b = milovert.b,
					  .a = milovert.a };

		Vector2f tex =		{ .u = milovert.u,
					  .v = milovert.v };

		objmesh.vertices[i] = vertex;
		objmesh.normals[i] = normal;
		objmesh.texVertices[i] = tex;
	}

	MILO_TRIANGLE *milotris = milomesh.triTable;
	for (size_t i = 0; i < milomesh.triCount; ++i) {
		MILO_TRIANGLE milotri = milotris[i];
		objmesh.faces[i] = (OBJFace) {
			.vertexIdCount		= 3,
			.vertexIds		= malloc(sizeof(ssize_t) * 3),
			.texVertexIdCount	= 3,
			.texVertexIds		= malloc(sizeof(ssize_t) * 3),
			.normalIdCount		= 3,
			.normalIds		= malloc(sizeof(ssize_t) * 3),
		};

		for (size_t j = 0; j < 3; ++j) {
			objmesh.faces[i].vertexIds[j] = milotri.vert[j] + 1;
			objmesh.faces[i].texVertexIds[j] = milotri.vert[j] + 1;
			objmesh.faces[i].normalIds[j] = milotri.vert[j] + 1;
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
