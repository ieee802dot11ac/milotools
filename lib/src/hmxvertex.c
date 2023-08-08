#include "hmxvertex.h"
#include "iohelper.h"
#include <stdio.h>

HX_VERTEX_FREQ hmx_freqvertex_load(FILE *file, bool isBigEndian)
{
	HX_VERTEX_FREQ vertex;
	vertex.x = iohelper_read_f32_ve(file, isBigEndian);
	vertex.y = iohelper_read_f32_ve(file, isBigEndian);
	vertex.z = iohelper_read_f32_ve(file, isBigEndian);

	vertex.nx = iohelper_read_f32_ve(file, isBigEndian);
	vertex.ny = iohelper_read_f32_ve(file, isBigEndian);
	vertex.nz = iohelper_read_f32_ve(file, isBigEndian);

	vertex.u = iohelper_read_f32_ve(file, isBigEndian);
	vertex.v = iohelper_read_f32_ve(file, isBigEndian);

	vertex.weight_0 = iohelper_read_f32_ve(file, isBigEndian);
	vertex.weight_1 = iohelper_read_f32_ve(file, isBigEndian);
	vertex.weight_2 = iohelper_read_f32_ve(file, isBigEndian);
	vertex.weight_3 = iohelper_read_f32_ve(file, isBigEndian);

	vertex.bone_0 = iohelper_read_u16_ve(file, isBigEndian);
	vertex.bone_1 = iohelper_read_u16_ve(file, isBigEndian);
	vertex.bone_2 = iohelper_read_u16_ve(file, isBigEndian);
	vertex.bone_3 = iohelper_read_u16_ve(file, isBigEndian);

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

HX_VERTEX_AMP hmx_ampvertex_load(FILE *file, bool isBigEndian)
{
	HX_VERTEX_AMP vertex;
	vertex.x = iohelper_read_f32_ve(file, isBigEndian);
	vertex.y = iohelper_read_f32_ve(file, isBigEndian);
	vertex.z = iohelper_read_f32_ve(file, isBigEndian);

	vertex.bone_0 = iohelper_read_u16_ve(file, isBigEndian);
	vertex.bone_1 = iohelper_read_u16_ve(file, isBigEndian);
	vertex.bone_2 = iohelper_read_u16_ve(file, isBigEndian);
	vertex.bone_3 = iohelper_read_u16_ve(file, isBigEndian);

	vertex.nx = iohelper_read_f32_ve(file, isBigEndian);
	vertex.ny = iohelper_read_f32_ve(file, isBigEndian);
	vertex.nz = iohelper_read_f32_ve(file, isBigEndian);

	vertex.weight_0 = iohelper_read_f32_ve(file, isBigEndian);
	vertex.weight_1 = iohelper_read_f32_ve(file, isBigEndian);
	vertex.weight_2 = iohelper_read_f32_ve(file, isBigEndian);
	vertex.weight_3 = iohelper_read_f32_ve(file, isBigEndian);

	vertex.u = iohelper_read_f32_ve(file, isBigEndian);
	vertex.v = iohelper_read_f32_ve(file, isBigEndian);

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

HX_VERTEX_NU hmx_nu_vertex_load(FILE *file, int version, bool isBigEndian)
{
	HX_VERTEX_NU vertex;
	vertex.x = iohelper_read_f32_ve(file, isBigEndian);
	vertex.y = iohelper_read_f32_ve(file, isBigEndian);
	vertex.z = iohelper_read_f32_ve(file, isBigEndian);
	if (version == 34) vertex.w = iohelper_read_f32_ve(file, isBigEndian);

	vertex.nx = iohelper_read_f32_ve(file, isBigEndian);
	vertex.ny = iohelper_read_f32_ve(file, isBigEndian);
	vertex.nz = iohelper_read_f32_ve(file, isBigEndian);
	if (version == 34) vertex.nw = iohelper_read_f32_ve(file, isBigEndian);

	if (version >= 38) {
		vertex.u = iohelper_read_f32_ve(file, isBigEndian);
		vertex.v = iohelper_read_f32_ve(file, isBigEndian);

		vertex.weight_0 = iohelper_read_f32_ve(file, isBigEndian);
		vertex.weight_1 = iohelper_read_f32_ve(file, isBigEndian);
		vertex.weight_2 = iohelper_read_f32_ve(file, isBigEndian);
		vertex.weight_3 = iohelper_read_f32_ve(file, isBigEndian);
	} else {
		vertex.weight_0 = iohelper_read_f32_ve(file, isBigEndian);
		vertex.weight_1 = iohelper_read_f32_ve(file, isBigEndian);
		vertex.weight_2 = iohelper_read_f32_ve(file, isBigEndian);
		vertex.weight_3 = iohelper_read_f32_ve(file, isBigEndian);

		vertex.u = iohelper_read_f32_ve(file, isBigEndian);
		vertex.v = iohelper_read_f32_ve(file, isBigEndian);
	}
	if (version >= 34) {
		vertex.bone_0 = iohelper_read_u16_ve(file, isBigEndian);
		vertex.bone_1 = iohelper_read_u16_ve(file, isBigEndian);
		vertex.bone_2 = iohelper_read_u16_ve(file, isBigEndian);
		vertex.bone_3 = iohelper_read_u16_ve(file, isBigEndian);

		if (version < 38) {
			vertex.tangent_0 = iohelper_read_f32_ve(file, isBigEndian);
			vertex.tangent_1 = iohelper_read_f32_ve(file, isBigEndian);
			vertex.tangent_2 = iohelper_read_f32_ve(file, isBigEndian);
			vertex.tangent_3 = iohelper_read_f32_ve(file, isBigEndian);
		} else {
			iohelper_read_u32_ve(file, isBigEndian);
			iohelper_read_u32_ve(file, isBigEndian);
			iohelper_read_f32_ve(file, isBigEndian);
			iohelper_read_f32_ve(file, isBigEndian);
		}
	}
	return vertex;
}

void hmx_nu_vertex_write(FILE *file, HX_VERTEX_NU vertex, int version, bool isBigEndian) {
	iohelper_write_f32_ve(file, vertex.x, isBigEndian);
	iohelper_write_f32_ve(file, vertex.y, isBigEndian);
	iohelper_write_f32_ve(file, vertex.z, isBigEndian);
	if (version == 34) iohelper_write_f32_ve(file, vertex.w, isBigEndian);

	iohelper_write_f32_ve(file, vertex.nx, isBigEndian);
	iohelper_write_f32_ve(file, vertex.ny, isBigEndian);
	iohelper_write_f32_ve(file, vertex.nz, isBigEndian);
	if (version == 34) iohelper_write_f32_ve(file, vertex.nw, isBigEndian);

	if (version >= 38) {
		iohelper_write_f32_ve(file, vertex.u, isBigEndian);
		iohelper_write_f32_ve(file, vertex.v, isBigEndian);

		iohelper_write_f32_ve(file, vertex.weight_0, isBigEndian);
		iohelper_write_f32_ve(file, vertex.weight_1, isBigEndian);
		iohelper_write_f32_ve(file, vertex.weight_2, isBigEndian);
		iohelper_write_f32_ve(file, vertex.weight_3, isBigEndian);
	} else {
		iohelper_write_f32_ve(file, vertex.weight_0, isBigEndian);
		iohelper_write_f32_ve(file, vertex.weight_1, isBigEndian);
		iohelper_write_f32_ve(file, vertex.weight_2, isBigEndian);
		iohelper_write_f32_ve(file, vertex.weight_3, isBigEndian);

		iohelper_write_f32_ve(file, vertex.u, isBigEndian);
		iohelper_write_f32_ve(file, vertex.v, isBigEndian);
	}
	if (version >= 34) {
		iohelper_write_u16_ve(file, vertex.bone_0, isBigEndian);
		iohelper_write_u16_ve(file, vertex.bone_1, isBigEndian);
		iohelper_write_u16_ve(file, vertex.bone_2, isBigEndian);
		iohelper_write_u16_ve(file, vertex.bone_3, isBigEndian);

		if (version < 38) {
			iohelper_write_f32_ve(file, vertex.tangent_0, isBigEndian);
			iohelper_write_f32_ve(file, vertex.tangent_1, isBigEndian);
			iohelper_write_f32_ve(file, vertex.tangent_2, isBigEndian);
			iohelper_write_f32_ve(file, vertex.tangent_3, isBigEndian);
		} else {
			iohelper_write_u32_ve(file, 0, isBigEndian);
			iohelper_write_u32_ve(file, 0, isBigEndian);
			iohelper_write_f32_ve(file, -1.0f, isBigEndian);
	// these are the default values. can you tell i didn't bother making a var for them
			iohelper_write_f32_ve(file, 1.0f, isBigEndian);
	 // these are the default values. can you tell i didn't bother making a var for them
		}
	}
}

void hmx_nu_vertex_print(HX_VERTEX_NU vertex)
{
	printf("HXVertexNu(position=(%f, %f, %f), normal=(%f, %f, %f, %f), weights=(%f, %f, %f, %f), tex=(%f, %f))",
			vertex.x, vertex.y, vertex.z,
			vertex.nx, vertex.ny, vertex.nz, vertex.nw,
			vertex.weight_0, vertex.weight_1, vertex.weight_2, vertex.weight_3,
			vertex.u, vertex.v
			//vertex.bone_0,vertex.bone_1,vertex.bone_2,vertex.bone_3,
			//vertex.tangent_0, vertex.tangent_1, vertex.tangent_2, vertex.tangent_3
			);
			
}
