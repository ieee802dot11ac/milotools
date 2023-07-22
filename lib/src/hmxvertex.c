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

HX_VERTEX_NU hmx_nu_vertex_load(FILE *file, int version)
{
	HX_VERTEX_NU vertex;
	vertex.x = iohelper_read_f32(file);	vertex.y = iohelper_read_f32(file);	vertex.z = iohelper_read_f32(file); if (version == 34) vertex.w = iohelper_read_f32(file);
	vertex.nx = iohelper_read_f32(file); vertex.ny = iohelper_read_f32(file); vertex.nz = iohelper_read_f32(file); if (version == 34) vertex.nw = iohelper_read_f32(file);
	if (version >= 38) {
		vertex.u = iohelper_read_f32(file);	vertex.v = iohelper_read_f32(file);
		vertex.weight_0 = iohelper_read_f32(file); vertex.weight_1 = iohelper_read_f32(file); vertex.weight_2 = iohelper_read_f32(file); vertex.weight_3 = iohelper_read_f32(file);
	} else {
		vertex.weight_0 = iohelper_read_f32(file); vertex.weight_1 = iohelper_read_f32(file); vertex.weight_2 = iohelper_read_f32(file); vertex.weight_3 = iohelper_read_f32(file);
		vertex.u = iohelper_read_f32(file);	vertex.v = iohelper_read_f32(file);
	}
	if (version >= 34) {
		vertex.bone_0 = iohelper_read_u16(file); vertex.bone_1 = iohelper_read_u16(file); vertex.bone_2 = iohelper_read_u16(file); vertex.bone_3 = iohelper_read_u16(file);
		if (version < 38) {
			vertex.tangent_0 = iohelper_read_f32(file); vertex.tangent_1 = iohelper_read_f32(file); vertex.tangent_2 = iohelper_read_f32(file); vertex.tangent_3 = iohelper_read_f32(file);
		} else {
			iohelper_read_u32(file);
			iohelper_read_u32(file);
			iohelper_read_f32(file);
			iohelper_read_f32(file);
		}
	}
	return vertex;
}

void hmx_nu_vertex_write(FILE *file, HX_VERTEX_NU vertex, int version) {
	iohelper_write_f32(file, vertex.x); iohelper_write_f32(file, vertex.y); iohelper_write_f32(file, vertex.z); if (version == 34) iohelper_write_f32(file, vertex.w);
	iohelper_write_f32(file, vertex.nx); iohelper_write_f32(file, vertex.ny); iohelper_write_f32(file, vertex.nz); if (version == 34) iohelper_write_f32(file, vertex.nw);
	if (version >= 38) {
		iohelper_write_f32(file, vertex.u); iohelper_write_f32(file, vertex.v);
		iohelper_write_f32(file, vertex.weight_0); iohelper_write_f32(file, vertex.weight_1); iohelper_write_f32(file, vertex.weight_2); iohelper_write_f32(file, vertex.weight_3);
	} else {
		iohelper_write_f32(file, vertex.weight_0); iohelper_write_f32(file, vertex.weight_1); iohelper_write_f32(file, vertex.weight_2); iohelper_write_f32(file, vertex.weight_3);
		iohelper_write_f32(file, vertex.u); iohelper_write_f32(file, vertex.v);
	}
	if (version >= 34) {
		iohelper_write_u16(file, vertex.bone_0); iohelper_write_u16(file, vertex.bone_1); iohelper_write_u16(file, vertex.bone_2); iohelper_write_u16(file, vertex.bone_3);
		if (version < 38) {
			iohelper_write_f32(file, vertex.tangent_0); iohelper_write_f32(file, vertex.tangent_1); iohelper_write_f32(file, vertex.tangent_2); iohelper_write_f32(file, vertex.tangent_3);
		} else {
			iohelper_write_u32(file, 0);
			iohelper_write_u32(file, 0);
			iohelper_write_f32(file, -1.0f); // these are the default values. can you tell i didn't bother making a var for them
			iohelper_write_f32(file, 1.0f);  // these are the default values. can you tell i didn't bother making a var for them
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
