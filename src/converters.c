#include "converters.h"
#include "argparse.h"
#include "hmx.h"
#include "filetypes.h"
#include "programinfo.h"
#include "err.h"
#include "fast_obj.h"
#include "stbwrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int convert(HXConverterArgs args)
{
	bool isBigEndian = args.isBigEndian;
	if (args.inputFileType == IFILETYPE_HX_MESH && args.outputFileType == OFILETYPE_WAVEFRONT_OBJ) {

		if (!conv_hxmesh_to_obj(args.inputPath, args.outputPath, args.recursePath, isBigEndian))
			return EXIT_FAILURE;

	} else if (args.inputFileType == IFILETYPE_WAVEFRONT_OBJ && args.outputFileType == OFILETYPE_HX_MESH) {
		if (args.outVersion == 0) {
			perror("no given output version!");
			return EXIT_FAILURE;
		}
		if (!conv_obj_to_hxmesh(args.inputPath, args.outputPath, args.outVersion, isBigEndian))
			return EXIT_FAILURE;

	} else if (args.inputFileType == IFILETYPE_HX_TEX && args.outputFileType == OFILETYPE_NETPBM_PAM) {

		if (!conv_hxtex_to_pam(args.inputPath, args.outputPath, isBigEndian))
			return EXIT_FAILURE;

	} else if (args.inputFileType == IFILETYPE_HX_BMP && args.outputFileType == OFILETYPE_NETPBM_PAM) {

		FILE* hxBmpFile = fopen(args.inputPath, "r");
		HX_BITMAP hxBmpData = hmx_bitmap_load(hxBmpFile, isBigEndian);
		fclose(hxBmpFile);
		if (!conv_hxbmp_to_pam(&hxBmpData, args.outputPath))
			return EXIT_FAILURE;

	} else if (args.inputFileType == IFILETYPE_HX_TEX && args.outputFileType == OFILETYPE_PNG) {

		if (!conv_hxtex_to_png(args.inputPath, args.outputPath, isBigEndian))
			return EXIT_FAILURE;

	} else if (args.inputFileType == IFILETYPE_HX_BMP && args.outputFileType == OFILETYPE_PNG) {

		FILE* hxBmpFile = fopen(args.inputPath, "r");
		HX_BITMAP hxBmpData = hmx_bitmap_load(hxBmpFile, isBigEndian);
		fclose(hxBmpFile);
		if (!conv_hxbmp_to_png(hxBmpData, args.outputPath))
			return EXIT_FAILURE;

	} else if (args.inputFileType == IFILETYPE_HX_MAT && args.outputFileType == OFILETYPE_WAVEFRONT_MTL) {

		FILE *file = fopen(args.inputPath, "r");
		HX_MATERIAL mat = hmx_material_load(file, isBigEndian);
		fclose(file);

		hmx_material_print(mat);
		hmx_material_cleanup(mat);

	} else if (args.inputFileType == IFILETYPE_HX_MILO && args.outputFileType == OFILETYPE_HX_RAWMILO) {
		
		FILE *file = fopen(args.inputPath, "r");
		int status = hmx_milo_decompress(file, args.outputPath, isBigEndian);
		if (status != 0) {
			printf("decompression error! error: %d", status);
		}
		fclose(file);
		
	} else if (args.inputFileType == IFILETYPE_HX_RAWMILO && args.outputFileType == OFILETYPE_DIR) {

		FILE *file = fopen(args.inputPath, "r");
		HX_MILOFILE *milo = hmx_milo_load(file, isBigEndian); // TODO implement this
		fclose(file);

		hmx_milo_print(milo);
		hmx_milo_cleanup(milo);

	} else if (args.inputFileType == IFILETYPE_HX_LIT) {

		FILE *file = fopen(args.inputPath, "r");
		HX_LIGHT light = hmx_light_load(file, isBigEndian);
		fclose(file);

		hmx_light_print(light);
		hmx_light_cleanup(light);

	} else if (args.inputFileType == IFILETYPE_HX_CAM) {

		FILE *file = fopen(args.inputPath, "r");
		HX_CAMERA camera = hmx_camera_load(file, isBigEndian);
		fclose(file);

		hmx_camera_print(camera);
		hmx_camera_cleanup(camera);

	} else if (args.inputFileType == IFILETYPE_HX_ENVIRON) {

		FILE *file = fopen(args.inputPath, "r");
		HX_ENVIRON environ = hmx_environ_load(file, isBigEndian);
		fclose(file);

		hmx_environ_print(environ);
		hmx_environ_cleanup(environ);

	} else if (args.inputFileType == IFILETYPE_HX_LBLX) {
		
		FILE *file = fopen(args.inputPath, "r");
		HX_LABEL_EX *label = hmx_labelex_load(file, isBigEndian);
		fclose(file);

		hmx_labelex_print(label);
		hmx_labelex_cleanup(label);

	} else if (args.inputFileType == IFILETYPE_HX_BTNX) {
		
		FILE *file = fopen(args.inputPath, "r");
		HX_BUTTON_EX *button = hmx_buttonex_load(file, isBigEndian);
		fclose(file);

		hmx_buttonex_print(button);
		hmx_buttonex_cleanup(button);

	} else if (args.inputFileType == IFILETYPE_HX_PICX) {
		
		FILE *file = fopen(args.inputPath, "r");
		HX_PICTURE_EX *pic = hmx_pictureex_load(file, isBigEndian);
		fclose(file);

		hmx_pictureex_print(pic);
		hmx_pictureex_cleanup(pic);

	} else if (args.inputFileType == IFILETYPE_HX_ARK) {
		
		FILE *file = fopen(args.inputPath, "r");
		u32 tmp = iohelper_read_u32(file);
		printf("%d\n", tmp);
		fseek(file, 0, SEEK_SET);
		if (tmp == (0 << 24 | 'K' << 16 | 'R' << 8 | 'A')) { // 'ARK\0' in LE
			HX_FREQARK *ark = hmx_freq_ark_load(file, NULL, isBigEndian);
			// fclose(file); // apparently this makes it crash. oops
			hmx_freq_ark_print(ark);
			hmx_freq_ark_cleanup(ark);
		}
		else if (tmp == 1 || tmp == 2) { // amp... hopefully
			HX_AMPARK* ark = hmx_ampark_load(file);

			hmx_ampark_print(ark);
			hmx_ampark_cleanup(ark);
		}

	/*} else if (args.inputFileType == IFILETYPE_HX_TNM) { // straight borked rn, so we're gonna ignore that
		
		FILE *file = fopen(args.inputPath, "r");
		HX_TRANSFORM_ANIM *tnm = hmx_transanim_load(file, isBigEndian);
		hmx_transanim_print(tnm);
		hmx_transanim_cleanup(tnm);*/	
	} else if (args.inputFileType == IFILETYPE_HX_TEXT) {
		
		FILE *file = fopen(args.inputPath, "r");
		HX_TEXT *text = hmx_text_load(file, isBigEndian);
		fclose(file);
		hmx_text_print(text);

	} else {
		fputs("Unknown conversion!\n", stderr);
	}

	return EXIT_SUCCESS;
}

bool conv_hxbmp_to_png(HX_BITMAP hxBmp, char const *const pngFilePath) {
	// PNG SHIT STARTS HERE
	HX_COLOR_8888 *pixels = malloc(sizeof(HX_COLOR_8888) * hxBmp.width * hxBmp.height);
	bool ret = true;

	for (int mip = 0; mip < hxBmp.mipmapLevels; mip++) {
		for (int y = 0; y < hxBmp.height; ++y) {
			for (int x = 0; x < hxBmp.width; ++x) {
				u8 pixel;
				if (hxBmp.bpp == 8) {
					pixel = hxBmp.texData[mip][x + y * hxBmp.width];
				} else if (hxBmp.bpp == 4) {
					size_t addr = (x / 2) + y * (hxBmp.width / 2);
					u8 shift = (x & 1) << 2;
					u8 mask = 0xF << shift;
					pixel = (hxBmp.texData[mip][addr] & mask) >> shift;
				} else {
					fprintf(stderr, "Unsupported number of bits per pixel (%u bpp) in texture file.\n",
							hxBmp.bpp);
					goto CLEAN_UP_FAILURE;
				}
				HX_COLOR_8888 color = hxBmp.colorPalette[pixel];
				color = hmx_color_8888_fix_alpha(color);
				pixels[x + y * hxBmp.width] = color;
			}
		}
	}
	//export_png(pngFilePath, hxBmp.width, hxBmp.height, pixels);

	goto CLEAN_UP_SUCCESS;
CLEAN_UP_FAILURE:
	ret = false;
CLEAN_UP_SUCCESS:
	free(pixels);
	return ret;
}

bool conv_hxtex_to_png(char const *const hxFilePath, char const *const pngFilePath, bool isBigEndian)
{
	FILE *hxTexFile = fopen(hxFilePath, "r");
	bool ret = true;

	if (hxTexFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for reading: %s\n",
				hxFilePath, strerror(errno));
		return false;
	}

	HX_TEXTURE hxTexData = hmx_texture_load(hxTexFile, false, isBigEndian);
	HX_BITMAP hxBmp = hxTexData.bmp;
	ret = conv_hxbmp_to_png(hxBmp, pngFilePath);
	hmx_texture_cleanup(hxTexData);
	fclose(hxTexFile);
	return ret;
}

bool conv_hxbmp_to_pam (HX_BITMAP *hxBmp, char const *const pamFilePath)
{
	FILE *pamFile = fopen(pamFilePath, "w");
	bool ret = true;

	if (pamFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for writing: %s\n",
				pamFilePath, strerror(errno));
		return false;
	}
	
	// PAM SHIT STARTS HERE
	fputs("P7\n", pamFile);
	fprintf(pamFile, "WIDTH %u\n", hxBmp->width);
	fprintf(pamFile, "HEIGHT %u\n", hxBmp->height);
	fputs("DEPTH 4\n", pamFile);
	fputs("MAXVAL 255\n", pamFile);
	fputs("TUPLTYPE RGB_ALPHA\n", pamFile);
	fputs("ENDHDR\n", pamFile);
	for (int mip = 0; mip < hxBmp->mipmapLevels; mip++) {
		for (int y = 0; y < hxBmp->height; ++y) {
			for (int x = 0; x < hxBmp->width; ++x) {
				u8 pixel;
				if (hxBmp->bpp == 8) {
					pixel = hxBmp->texData[mip][x + y * hxBmp->width];
				} else if (hxBmp->bpp == 4) {
					size_t addr = (x / 2) + y * (hxBmp->width / 2);
					u8 shift = (x & 1) << 2;
					u8 mask = 0xF << shift;
					pixel = (hxBmp->texData[mip][addr] & mask) >> shift;
				} else {
					fprintf(stderr, "Unsupported number of bits per pixel (%u bpp) in texture file.\n",
							hxBmp->bpp);
					goto CLEAN_UP_FAILURE;
				}
				HX_COLOR_8888 color = hxBmp->colorPalette[pixel];
				color = hmx_color_8888_fix_alpha(color);
				fprintf(pamFile, "%c%c%c%c", color.r,
							     color.g,
							     color.b,
							     color.a);
			}
		}
	}
	goto CLEAN_UP_SUCCESS;
CLEAN_UP_FAILURE:
	ret = false;
CLEAN_UP_SUCCESS:
	fclose(pamFile);
	return ret;
}

bool conv_hxtex_to_pam(char const *const hxFilePath, char const *const pamFilePath, bool isBigEndian)
{
	FILE *hxTexFile = fopen(hxFilePath, "r");
	bool ret = true;

	if (hxTexFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for reading: %s\n",
				hxFilePath, strerror(errno));
		return false;
	}

	HX_TEXTURE hxTexData = hmx_texture_load(hxTexFile, false, isBigEndian);
	HX_BITMAP hxBmp = hxTexData.bmp;
	ret = conv_hxbmp_to_pam(&hxBmp, pamFilePath);
	hmx_texture_cleanup(hxTexData);
	fclose(hxTexFile);
	return ret;
}

bool conv_hxmat_to_mtl(char const *const hxFilePath, char const *const outFilePath, char const *const recursePath, bool isBigEndian)
{
	FILE *hxMatFile = fopen(hxFilePath, "r");
	FILE *mtlMatFile = fopen(outFilePath, "w");

	if (hxMatFile == NULL) {
		warn("Failed to open file `%s` for reading", hxFilePath);
		return false;
	} else if (mtlMatFile == NULL) {
		warn("Failed to open file `%s` for writing", outFilePath);
		return false;
	}

	HX_MATERIAL hxMat = hmx_material_load(hxMatFile, isBigEndian);
	fclose(hxMatFile);
	fputs("# Generated using " PROGRAM_NAME " " PROGRAM_VERSION "\n", mtlMatFile);
	fputs("newmtl DEFAULT\n", mtlMatFile);
	fprintf(mtlMatFile, "Ka %f %f %f\n", hxMat.color.r, hxMat.color.g, hxMat.color.b);
	fprintf(mtlMatFile, "Ka %f %f %f\n", hxMat.color.r, hxMat.color.g, hxMat.color.b);
	fprintf(mtlMatFile, "Tr %f\n", 1.0 - hxMat.color.a); // ?
	fprintf(mtlMatFile, "Tf %f %f %f\n", hxMat.color.r, hxMat.color.g, hxMat.color.b);
	if (hxMat.textureCount != 0 && recursePath != NULL) {
		char *const texPath = hmx_string_cstring(hxMat.textures[0].texName);
		char *const resourcePath = malloc(strlen(texPath) + strlen(recursePath) + 16);
		strcpy(resourcePath, recursePath);
		if (recursePath[strlen(recursePath) - 1] != '/') {
			resourcePath[strlen(recursePath)] = '/';
			resourcePath[strlen(recursePath) + 1] = 0;
		}
		strcat(resourcePath, texPath);
		// jank -> png
		char *const resourceOutPath = malloc(strlen(outFilePath) + strlen(texPath) + 16);
		strcpy(resourceOutPath, outFilePath);
		// find and remove the filename from the objFilePath
		for (char *c = &resourceOutPath[strlen(outFilePath)], *pc=c; c > resourceOutPath; --c) {
			if (*c == '/') {
				*pc = 0;
				break;
			}
			pc = c;
		}
		strcat(resourceOutPath, texPath);
		// png file extension
		resourceOutPath[strlen(resourceOutPath) - 1] = 'g';
		resourceOutPath[strlen(resourceOutPath) - 2] = 'n';
		resourceOutPath[strlen(resourceOutPath) - 3] = 'p';
		texPath[strlen(texPath) - 1] = 'g';
		texPath[strlen(texPath) - 2] = 'n';
		texPath[strlen(texPath) - 3] = 'p';

		printf("%s -> %s\n", resourcePath, resourceOutPath);
		if (conv_hxtex_to_png(resourcePath, resourceOutPath, isBigEndian)) {
			fprintf(mtlMatFile, "map_Ka %s\nmap_Kd %s\n", texPath, texPath);
		} else {
			fprintf(stderr, "Failed to load texture file `%s`\n", resourcePath);
		}
		free(texPath);
		free(resourcePath);
		free(resourceOutPath);
	}

	hmx_material_cleanup(hxMat);

	fclose(mtlMatFile);
	return true;
}

bool conv_hxmesh_to_obj(char const *const hxFilePath, char const *const objFilePath, char const *const recursePath, bool isBigEndian)
{
	FILE *hxMeshFile = fopen(hxFilePath, "r");
	FILE *objMeshFile = fopen(objFilePath, "w");

	if (hxMeshFile == NULL) {
		warn("Failed to open file `%s` for reading", hxFilePath);
		return false;
	} else if (objMeshFile == NULL) {
		warn("Failed to open file `%s` for writing", objFilePath);
		return false;
	}
	/*
	HX_MESH *hxMeshData = hmx_mesh_load(hxMeshFile, isBigEndian);
	fclose(hxMeshFile);
	OBJData obj = obj_from_hmx(*hxMeshData);
	fputs("# Generated using " PROGRAM_NAME " " PROGRAM_VERSION "\n", objMeshFile);

	if (recursePath != NULL) {
		char *const matPath = hmx_string_cstring(hxMeshData->matPath);
		char *const resourcePath = malloc(strlen(matPath) + strlen(recursePath) + 16);

		strcpy(resourcePath, recursePath);
		if (recursePath[strlen(recursePath) - 1] != '/') {
			resourcePath[strlen(recursePath)] = '/';
			resourcePath[strlen(recursePath)+1] = 0;
		}
		strcat(resourcePath, matPath);

		// jank -> mtl
		char *const resourceOutPath = malloc(strlen(objFilePath) + strlen(matPath) + 16);
		strcpy(resourceOutPath, objFilePath);
		// find and remove the filename from the objFilePath
		for (char *c = &resourceOutPath[strlen(objFilePath)], *pc=c; c > resourceOutPath; --c) {
			if (*c == '/') {
				*pc = 0;
				break;
			}
			pc = c;
		}
		strcat(resourceOutPath, matPath);
		// mtl file extension
		resourceOutPath[strlen(resourceOutPath) - 1] = 'l';
		resourceOutPath[strlen(resourceOutPath) - 2] = 't';
		resourceOutPath[strlen(resourceOutPath) - 3] = 'm';
		matPath[strlen(matPath) - 1] = 'l';
		matPath[strlen(matPath) - 2] = 't';
		matPath[strlen(matPath) - 3] = 'm';

		printf("%s -> %s\n", resourcePath, resourceOutPath);
		if (conv_hxmat_to_mtl(resourcePath, resourceOutPath, recursePath)) {
			fprintf(objMeshFile, "mtllib %s\n", matPath);
			fputs("usemtl DEFAULT\n", objMeshFile);
		} else {
			fprintf(stderr, "Failed to load material file `%s`\n", resourcePath);
		}
		free(matPath);
		free(resourcePath);
		free(resourceOutPath);
	}
	//hmx_mesh_cleanup(hxMeshData); // makes it crash? no clue why, probably a double free

	obj_write(obj, objMeshFile);
	obj_cleanup(obj);

	fclose(objMeshFile);*/
	return false;
}

bool conv_obj_to_hxmesh( char const *const objFilePath, char const *const hxFilePath, int version, bool isBigEndian)
{
	fastObjMesh *objMesh = fast_obj_read(objFilePath);
	FILE *hxMeshFile = fopen(hxFilePath, "w");

	if (hxMeshFile == NULL) {
		warn("Failed to open file `%s` for reading", hxFilePath);
		return false;
	} else if (objMesh == NULL) {
		warn("Failed to open file `%s` for writing", objFilePath);
		return false;
	}

	if (objMesh->position_count != objMesh->normal_count || objMesh->position_count != objMesh->texcoord_count) {
		printf("vert counts don't match!\n");
		printf("pos %d norm %d tex %d",objMesh->position_count,objMesh->normal_count,objMesh->texcoord_count);
	}
	
	HX_MESH *hxMeshData = malloc(sizeof(HX_MESH));
	if (isBigEndian) {
		hxMeshData->meta = &HX_META_EMPTY_NG;
	} else hxMeshData->meta = &HX_META_EMPTY_PS2;
	hxMeshData->transform = HX_TRANSFORM_EMPTY;
	hxMeshData->draw = HX_DRAW_EMPTY;

	if (version >= 28) {
		hxMeshData->transform.version = 9;
		hxMeshData->draw.version = 3;
		hxMeshData->version = version;
	}

	hxMeshData->vertTableNu = malloc(sizeof(HX_VERTEX_NU)*objMesh->position_count);
	for (u32 i = 0; i < objMesh->position_count; i++) {
		u32 j = i * 3;
		u32 tex = i * 2;
		HX_VERTEX_NU vert = (HX_VERTEX_NU){
			.x = objMesh->positions[j],
			.y = objMesh->positions[j+1],
			.z = objMesh->positions[j+2],
			.nx = objMesh->normals[j],
			.ny = objMesh->normals[j+1],
			.nz = objMesh->normals[j+1],
			.u = objMesh->texcoords[tex],
			.v = objMesh->texcoords[tex+1]
		};
		hxMeshData->vertCount++;
		hxMeshData->vertTableNu[i] = vert;
	}


	hmx_mesh_write(hxMeshFile, hxMeshData, isBigEndian);
	fast_obj_destroy(objMesh);
	return true;
}
