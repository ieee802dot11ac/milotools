#include <stdio.h>
#include <stdlib.h>
#include "hmxmatrix.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "hmxmaterial.h"

HX_MATERIAL hmx_material_load(FILE *file)
{
	HX_MATERIAL mat;
	mat.version = iohelper_read_u32(file);
	mat.textureCount = iohelper_read_u32(file);
	mat.textures = malloc(mat.textureCount * sizeof(HX_MATERIAL_TEXTURE_ENTRY));
	for (u32 i = 0; i < mat.textureCount; ++i)
		mat.textures[i] = hmx_material_texture_entry_load(file);
	mat.always3 = iohelper_read_u32(file);
	mat.color.r = iohelper_read_f32(file);
	mat.color.g = iohelper_read_f32(file);
	mat.color.b = iohelper_read_f32(file);
	mat.color.a = iohelper_read_f32(file);

	mat.always1_1 = iohelper_read_u8(file);
	mat.always0_1 = iohelper_read_u16(file);
	mat.always1_2 = iohelper_read_u32(file);
	mat.always0_2 = iohelper_read_u16(file);

	mat.blend = iohelper_read_u32(file);
	mat.always0_3 = iohelper_read_u16(file);

	return mat;
}

void hmx_material_cleanup(HX_MATERIAL mat)
{
	for (u32 i = 0; i < mat.textureCount; ++i)
		hmx_material_texture_entry_cleanup(mat.textures[i]);
	free(mat.textures);
}

void hmx_material_print(HX_MATERIAL mat)
{
	printf("VERSION: %u\n", mat.version);
	puts("TEXTURES: [");
	for (u32 i = 0; i < mat.textureCount; ++i) {
		hmx_material_texture_entry_print(mat.textures[i]);
		if (i != mat.textureCount - 1)
			fputs(", ", stdout);
	}
	puts("]");
	printf("ALWAYS3: %u\n", mat.always3);
	printf("ALWAYS1(1): %u\n", mat.always1_1);
	printf("ALWAYS0(1): %u\n", mat.always0_1);
	printf("ALWAYS1(2): %u\n", mat.always1_2);
	printf("ALWAYS0(2): %u\n", mat.always0_2);

	printf("BLEND: %s\n", HX_BLEND_NAME[mat.blend]);
	printf("ALWAYS0(3): %u\n", mat.always0_3);
}

void hmx_material_texture_entry_print(HX_MATERIAL_TEXTURE_ENTRY texEnt)
{
	fputs("TEXTURE_NAME: ", stdout);
	hmx_string_print(texEnt.texName);
	putchar('\n');
	printf("UNKNOWN1: %u\n", texEnt.unknown1);
	printf("TEXGEN: %s\n", HX_TEXGEN_NAME[texEnt.texGen]);
	printf("TEXWRAP: %s\n", HX_TEXWRAP_NAME[texEnt.texWrap]);
	fputs("MATRIX: ", stdout);
	hmx_matrix_print(texEnt.matx);
	putchar('\n');
}

HX_MATERIAL_TEXTURE_ENTRY hmx_material_texture_entry_load(FILE *file)
{
	HX_MATERIAL_TEXTURE_ENTRY texEnt;
	texEnt.unknown1 = iohelper_read_u32(file);
	texEnt.texGen = iohelper_read_u32(file);
	texEnt.matx = hmx_matrix_load(file);
	texEnt.texWrap = iohelper_read_u32(file);
	texEnt.texName = hmx_string_load(file);
	return texEnt;
}

void hmx_material_texture_entry_cleanup(HX_MATERIAL_TEXTURE_ENTRY texEnt)
{
	hmx_string_cleanup(texEnt.texName);
}

char const *const HX_TEXGEN_NAME[HX_TEXGEN_COUNT] = {
	"TexGenNone",
	"TexGenXfm",
	"TexGenSphere",
	"TexGenProjected",
	"TexGenXfmOrigin",
	"TexGenEnviron",
};
char const *const HX_TEXWRAP_NAME[HX_TEXWRAP_COUNT] = {
	"TexWrapClamp",
	"TexWrapRepeat",
};
char const *const HX_ZMODE_NAME[HX_ZMODE_COUNT] = {
	"ZModeDisable",
	"ZModeNormal",
	"ZModeTransparent",
	"ZModeForce",
	"ZModeDecal",
};
char const *const HX_BLEND_NAME[HX_BLEND_COUNT] = {
	"BlendDest",
	"BlendSrc",
	"BlendAdd",
	"BlendSrcAlpha",
	"BlendSrcAlphaAdd",
	"BlendSubtract",
	"BlendMultiply",
};
