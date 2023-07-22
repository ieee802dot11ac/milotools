#include "hmxvertex.h"
#include "iohelper.h"
#include <stdio.h>

HX_VERTEX_FREQ hmx_freqvertex_load(FILE *file)
{
	HX_VERTEX_FREQ vertex;
	vertex.x = iohelper_read_f32(file);	vertex.y = iohelper_read_f32(file);	vertex.z = iohelper_read_f32(file);
	vertex.nx = iohelper_read_f32(file); vertex.ny = iohelper_read_f32(file); vertex.nz = iohelper_read_f32(file);
	vertex.u = iohelper_read_f32(file);	vertex.v = iohelper_read_f32(file);
	vertex.weight_0 = iohelper_read_f32(file); vertex.weight_1 = iohelper_read_f32(file); vertex.weight_2 = iohelper_read_f32(file); vertex.weight_3 = iohelper_read_f32(file);
	vertex.bone_0 = iohelper_read_u16(file); vertex.bone_1 = iohelper_read_u16(file); vertex.bone_2 = iohelper_read_u16(file); vertex.bone_3 = iohelper_read_u16(file);
	return vertex;
}

void hmx_freqvertex_print(HX_VERTEX_FREQ vertex)
{
	printf("HXVertexGH2(position=(%f, %f, %f), normal=(%f, %f, %f), tex=(%f, %f), weights=(%f, %f, %f, %f), bones=(%d, %d, %d, %d))",
			vertex.x, vertex.y, vertex.z,
			vertex.nx, vertex.ny, vertex.nz,
			vertex.u, vertex.v,
			vertex.weight_0, vertex.weight_1, vertex.weight_2, vertex.weight_3,
			vertex.bone_0,vertex.bone_1,vertex.bone_2,vertex.bone_3);
			
}

HX_VERTEX_AMP hmx_ampvertex_load(FILE *file)
{
	HX_VERTEX_AMP vertex;
	vertex.x = iohelper_read_f32(file);	vertex.y = iohelper_read_f32(file);	vertex.z = iohelper_read_f32(file);
	vertex.bone_0 = iohelper_read_u16(file); vertex.bone_1 = iohelper_read_u16(file); vertex.bone_2 = iohelper_read_u16(file); vertex.bone_3 = iohelper_read_u16(file);
	vertex.nx = iohelper_read_f32(file); vertex.ny = iohelper_read_f32(file); vertex.nz = iohelper_read_f32(file);
	vertex.weight_0 = iohelper_read_f32(file); vertex.weight_1 = iohelper_read_f32(file); vertex.weight_2 = iohelper_read_f32(file); vertex.weight_3 = iohelper_read_f32(file);
	vertex.u = iohelper_read_f32(file);	vertex.v = iohelper_read_f32(file);
	return vertex;
}

void hmx_ampvertex_print(HX_VERTEX_AMP vertex)
{
	printf("HXVertexAmp(position=(%f, %f, %f), bones=(%d, %d, %d, %d), normal=(%f, %f, %f), weights=(%f, %f, %f, %f), tex=(%f, %f))",
			vertex.x, vertex.y, vertex.z,
			vertex.bone_0,vertex.bone_1,vertex.bone_2,vertex.bone_3,
			vertex.nx, vertex.ny, vertex.nz,
			vertex.weight_0, vertex.weight_1, vertex.weight_2, vertex.weight_3,
			vertex.u, vertex.v);
			
}

HX_VERTEX_GH hmx_ghvertex_load(FILE *file)
{
	HX_VERTEX_GH vertex;
	fread(&vertex, sizeof(HX_VERTEX_GH), 1, file);

	return vertex;
}

void hmx_ghvertex_print(HX_VERTEX_GH vertex)
{
	printf("HXVertexGH(position=(%f, %f, %f), normal=(%f, %f, %f), color=(%f, %f, %f, %f), tex=(%f, %f))",
			vertex.x, vertex.y, vertex.z,
			vertex.normX, vertex.normY, vertex.normZ,
			vertex.r, vertex.g, vertex.b, vertex.a,
			vertex.u, vertex.v);
}

HX_VERTEX_GH2 hmx_gh2vertex_load(FILE *file, bool xbox)
{
	HX_VERTEX_GH2 vertex;
	vertex.x = iohelper_read_f32(file);	vertex.y = iohelper_read_f32(file);	vertex.z = iohelper_read_f32(file);
	vertex.nx = iohelper_read_f32(file); vertex.ny = iohelper_read_f32(file); vertex.nz = iohelper_read_f32(file); if (xbox) vertex.nw = iohelper_read_f32(file);
	vertex.weight_0 = iohelper_read_f32(file); vertex.weight_1 = iohelper_read_f32(file); vertex.weight_2 = iohelper_read_f32(file); vertex.weight_3 = iohelper_read_f32(file);
	vertex.u = iohelper_read_f32(file);	vertex.v = iohelper_read_f32(file);
	// vertex.bone_0 = iohelper_read_u16(file); vertex.bone_1 = iohelper_read_u16(file); vertex.bone_2 = iohelper_read_u16(file); vertex.bone_3 = iohelper_read_u16(file);
	// vertex.tangent_0 = iohelper_read_f32(file); vertex.tangent_1 = iohelper_read_f32(file); vertex.tangent_2 = iohelper_read_f32(file); vertex.tangent_3 = iohelper_read_f32(file);
	return vertex;
}

void hmx_gh2vertex_write(FILE *file, HX_VERTEX_GH2 vertex, bool xbox) {
	iohelper_write_f32(file, vertex.x); iohelper_write_f32(file, vertex.y); iohelper_write_f32(file, vertex.z);
	iohelper_write_f32(file, vertex.nx); iohelper_write_f32(file, vertex.ny); iohelper_write_f32(file, vertex.nz); if (xbox) iohelper_write_f32(file, vertex.nw);
	iohelper_write_f32(file, vertex.weight_0); iohelper_write_f32(file, vertex.weight_1); iohelper_write_f32(file, vertex.weight_2); iohelper_write_f32(file, vertex.weight_3);
	iohelper_write_f32(file, vertex.u); iohelper_write_f32(file, vertex.v);
}

void hmx_gh2vertex_print(HX_VERTEX_GH2 vertex)
{
	printf("HXVertexGH2(position=(%f, %f, %f), normal=(%f, %f, %f, %f), weights=(%f, %f, %f, %f), tex=(%f, %f))",
			vertex.x, vertex.y, vertex.z,
			vertex.nx, vertex.ny, vertex.nz, vertex.nw,
			vertex.weight_0, vertex.weight_1, vertex.weight_2, vertex.weight_3,
			vertex.u, vertex.v
			//vertex.bone_0,vertex.bone_1,vertex.bone_2,vertex.bone_3,
			//vertex.tangent_0, vertex.tangent_1, vertex.tangent_2, vertex.tangent_3
			);
			
}
