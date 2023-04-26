#include "converters.h"
#include "argparse.h"
#include "hmxenviron.h"
#include "programinfo.h"

#include "hmxcolor.h"
#include "hmxtexture.h"
#include "hmxbitmap.h"
#include "hmxmesh.h"
#include "hmxobj.h"
#include "spngwrapper.h"
#include "hmxlight.h"
#include "hmxmaterial.h"
#include "hmxcamera.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int convert(HXConverterArgs args)
{
	if (args.inputFileType == IFILETYPE_HX_MESH && args.outputFileType == OFILETYPE_WAVEFRONT_OBJ) {
		if (!conv_hxmesh_to_obj(args.inputPath, args.outputPath))
			return EXIT_FAILURE;
	} else if (args.inputFileType == IFILETYPE_HX_TEX && args.outputFileType == OFILETYPE_NETPBM_PAM) {
		if (!conv_hxtex_to_pam(args.inputPath, args.outputPath))
			return EXIT_FAILURE;
	} else if (args.inputFileType == IFILETYPE_HX_TEX && args.outputFileType == OFILETYPE_PNG) {
		if (!conv_hxtex_to_png(args.inputPath, args.outputPath))
			return EXIT_FAILURE;
	} else if (args.inputFileType == IFILETYPE_HX_LIT) {
		FILE *file = fopen(args.inputPath, "r");
		HX_LIGHT light = hmx_light_load(file);
		fclose(file);

		hmx_light_print(light);
		hmx_light_cleanup(light);
	} else if (args.inputFileType == IFILETYPE_HX_CAM) {
		FILE *file = fopen(args.inputPath, "r");
		HX_CAMERA camera = hmx_camera_load(file);
		fclose(file);

		hmx_camera_print(camera);
		hmx_camera_cleanup(camera);
	} else if (args.inputFileType == IFILETYPE_HX_MAT && args.outputFileType == OFILETYPE_WAVEFRONT_MTL) {
		FILE *file = fopen(args.inputPath, "r");
		HX_MATERIAL mat = hmx_material_load(file);
		fclose(file);

		hmx_material_print(mat);
		hmx_material_cleanup(mat);
	} else if (args.inputFileType == IFILETYPE_HX_ENVIRON) {
		FILE *file = fopen(args.inputPath, "r");
		HX_ENVIRON environ = hmx_environ_load(file);
		fclose(file);

		hmx_environ_print(environ);
		hmx_environ_cleanup(environ);
	} else {
		fputs("Unknown conversion!\n", stderr);
	}

	return EXIT_SUCCESS;
}

bool conv_hxtex_to_png(char const *const hxFilePath, char const *const pngFilePath)
{
	FILE *hxTexFile = fopen(hxFilePath, "r");
	bool ret = true;

	if (hxTexFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for reading: %s\n",
				hxFilePath, strerror(errno));
		return false;
	}

	HX_TEXTURE hxTexData = hmx_texture_load(hxTexFile);
	HX_BITMAP hxBmp = hxTexData.bmp;

	HX_COLOR_8888 *pixels = malloc(sizeof(HX_COLOR_8888) * hxBmp.width * hxBmp.height);

	for (int y = 0; y < hxBmp.height; ++y) {
		for (int x = 0; x < hxBmp.width; ++x) {
			u8 pixel;
			if (hxBmp.bpp == 8) {
				pixel = hxBmp.texData[x + y * hxBmp.width];
			} else if (hxBmp.bpp == 4) {
				size_t addr = (x / 2) + y * (hxBmp.width / 2);
				u8 shift = (x & 1) << 2;
				u8 mask = 0xF << shift;
				pixel = (hxBmp.texData[addr] & mask) >> shift;
			} else {
				fprintf(stderr, "Unsupported number of bits per pixel (%u bpp) in texture file `%s`",
						hxBmp.bpp,
						hxFilePath);
				goto CLEAN_UP_FAILURE;
			}
			HX_COLOR_8888 color = hxBmp.colorPalette[pixel];
			color = hmx_color_8888_fix_alpha(color);
			pixels[x + y * hxBmp.height] = color;
		}
	}
	export_png(pngFilePath, hxBmp.width, hxBmp.height, pixels);

	goto CLEAN_UP_SUCCESS;
CLEAN_UP_FAILURE:
	ret = false;
CLEAN_UP_SUCCESS:
	hmx_texture_cleanup(hxTexData);
	free(pixels);
	fclose(hxTexFile);
	return ret;
}

bool conv_hxtex_to_pam(char const *const hxFilePath, char const *const pamFilePath)
{
	FILE *hxTexFile = fopen(hxFilePath, "r");
	FILE *pamFile = fopen(pamFilePath, "w");
	bool ret = true;

	if (hxTexFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for reading: %s\n",
				hxFilePath, strerror(errno));
		return false;
	} else if (pamFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for writing: %s\n",
				pamFilePath, strerror(errno));
		return false;
	}

	HX_TEXTURE hxTexData = hmx_texture_load(hxTexFile);
	HX_BITMAP hxBmp = hxTexData.bmp;

	fputs("P7\n", pamFile);
	fprintf(pamFile, "WIDTH %u\n", hxBmp.width);
	fprintf(pamFile, "HEIGHT %u\n", hxBmp.height);
	fputs("DEPTH 4\n", pamFile);
	fputs("MAXVAL 255\n", pamFile);
	fputs("TUPLTYPE RGB_ALPHA\n", pamFile);
	fputs("ENDHDR\n", pamFile);

	for (int y = 0; y < hxBmp.height; ++y) {
		for (int x = 0; x < hxBmp.width; ++x) {
			u8 pixel;
			if (hxBmp.bpp == 8) {
				pixel = hxBmp.texData[x + y * hxBmp.width];
			} else if (hxBmp.bpp == 4) {
				size_t addr = (x / 2) + y * (hxBmp.width / 2);
				u8 shift = (x & 1) << 2;
				u8 mask = 0xF << shift;
				pixel = (hxBmp.texData[addr] & mask) >> shift;
			} else {
				fprintf(stderr, "Unsupported number of bits per pixel (%u bpp) in texture file `%s`",
						hxBmp.bpp,
						hxFilePath);
				goto CLEAN_UP_FAILURE;
			}
			HX_COLOR_8888 color = hxBmp.colorPalette[pixel];
			color = hmx_color_8888_fix_alpha(color);
			fprintf(pamFile, "%c%c%c%c", color.r,
						     color.g,
						     color.b,
						     color.a);
		}
	}
	goto CLEAN_UP_SUCCESS;
CLEAN_UP_FAILURE:
	ret = false;
CLEAN_UP_SUCCESS:
	hmx_texture_cleanup(hxTexData);
	fclose(hxTexFile);
	fclose(pamFile);
	return ret;
}

bool conv_hxmesh_to_obj(char const *const hxFilePath, char const *const objFilePath)
{
	FILE *hxMeshFile = fopen(hxFilePath, "r");
	FILE *objMeshFile = fopen(objFilePath, "w");

	if (hxMeshFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for reading: %s\n",
				hxFilePath, strerror(errno));
		return false;
	} else if (objMeshFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for writing: %s\n",
				objFilePath, strerror(errno));
		return false;
	}

	HX_MESH hxMeshData = hmx_mesh_load(hxMeshFile);
	fclose(hxMeshFile);
	OBJData obj = obj_from_hmx(hxMeshData);
	hmx_mesh_cleanup(hxMeshData);

	fputs("# Generated using " PROGRAM_NAME " " PROGRAM_VERSION "\n", objMeshFile);
	obj_write(obj, objMeshFile);
	obj_cleanup(obj);

	fclose(objMeshFile);
	return true;
}
