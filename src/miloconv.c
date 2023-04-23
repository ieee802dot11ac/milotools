#include "milo_bitmap.h"
#include "milo_texture.h"
#include <stdbool.h>
#include <stddef.h>
#define _GNU_SOURCE // For fcloseall()
#include <stdio.h>
#undef _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "milo_common.h"
#include "milo_string.h"
#include "milo_obj.h"
#include "miloconv.h"
#include "milo_color.h"

#define PROGRAM_NAME "MILOConverter"
#define PROGRAM_VERSION "v0.1.0"


int main(int const argc, char const *const *const argv)
{
	int exitCode = EXIT_FAILURE;

	char const *inputPath = NULL;
	char const *outputPath = NULL;
	SUPPORTED_INPUT_FILETYPE inputFileType = IFILETYPE_UNKNOWN;
	SUPPORTED_OUTPUT_FILETYPE outputFileType = OFILETYPE_UNKNOWN;
	bool acceptPosixArgs = true;

	int skipArgs = 0;
	for (int i = 1; i < argc; ++i) {
		if (skipArgs > 0) {
			--skipArgs;
			continue;
		}
		char const *const arg = argv[i];
		if (acceptPosixArgs) {
			if (streq(arg, "--")) {
				acceptPosixArgs = false;
			} else if (streq(arg, "--help") || streq(arg, "-h")) {
				print_help(argv[0], stdout);
				goto EXIT_SUCCEED;
			} else if (streq(arg, "--input") || streq(arg, "-i")) {
				if (i == argc - 1) {
					fprintf(stderr, "Not enough arguments to `%s`.\n", arg);
					goto EXIT_FAILED;
				}
				if ((inputFileType = get_input_filetype_arg(argv[i + 1])) == IFILETYPE_UNKNOWN) {
					fprintf(stderr, "Unimplemented input filetype: `%s`.\n", arg);
					goto EXIT_FAILED;
				}
				skipArgs = 1;
			} else if (streq(arg, "--input") || streq(arg, "-i")) {
				if (i == argc - 1) {
					fprintf(stderr, "Not enough arguments to `%s`.\n", arg);
					goto EXIT_FAILED;
				}
				if ((outputFileType = get_output_filetype_arg(argv[i + 1])) == OFILETYPE_UNKNOWN) {
					fprintf(stderr, "Unimplemented output filetype: `%s`.\n", arg);
					goto EXIT_FAILED;
				}
				skipArgs = 1;
			} else {
				goto ACCEPT_PATHS;
			}
			continue;
		}
ACCEPT_PATHS:
		if (inputPath == NULL) {
			inputPath = arg;
		} else if (outputPath == NULL) {
			outputPath = arg;
		} else {
			fputs("Too many arguments provided.\n", stderr);
			print_help(argv[0], stderr);
			goto EXIT_FAILED;
		}
	}

	if (inputPath == NULL) {
		fputs("No input or output file provided.\n\n", stderr);

		print_help(argv[0], stderr);
		goto EXIT_FAILED;
	} else if (outputPath == NULL) {
		fputs("No output file provided.\n\n", stderr);

		print_help(argv[0], stderr);
		goto EXIT_FAILED;
	}

	if (inputFileType == IFILETYPE_UNKNOWN) {
		size_t extensionLength = 0;
		for (size_t i = strlen(inputPath) - 1; i > 0; --i) {
			if (inputPath[i] == '.')
				break;
			++extensionLength;
		}
		char *const extension = malloc(sizeof(char) * (extensionLength + 1));
		strcpy(extension, &inputPath[strlen(inputPath) - extensionLength]);
		if ((inputFileType = get_input_filetype_ext(extension)) == IFILETYPE_UNKNOWN) {
			fprintf(stderr, "Unknown input file extension `.%s`\n", extension);
			free(extension);
			goto EXIT_FAILED;
		}
		free(extension);
	}
	if (outputFileType == OFILETYPE_UNKNOWN) {
		size_t extensionLength = 0;
		for (size_t i = strlen(outputPath) - 1; i > 0; --i) {
			if (outputPath[i] == '.')
				break;
			++extensionLength;
		}
		char *const extension = malloc(sizeof(char) * (extensionLength + 1));
		strcpy(extension, &outputPath[strlen(outputPath) - extensionLength]);
		if ((outputFileType = get_output_filetype_ext(extension)) == OFILETYPE_UNKNOWN) {
			fprintf(stderr, "Unknown output file extension `.%s`\n", extension);
			free(extension);
			goto EXIT_FAILED;
		}
		free(extension);
	}

	if (inputFileType == IFILETYPE_MILO_MESH && outputFileType == OFILETYPE_WAVEFRONT_OBJ) {
		if (!conv_milomesh_to_obj(inputPath, outputPath))
			goto EXIT_FAILED;
	} else if (inputFileType == IFILETYPE_MILO_TEX && outputFileType == OFILETYPE_NETPBM_PAM) {
		if (!conv_milotex_to_pam(inputPath, outputPath))
			goto EXIT_FAILED;
	}

EXIT_SUCCEED:
	exitCode = EXIT_SUCCESS;
EXIT_FAILED:
	fcloseall();
	return exitCode;
}

SUPPORTED_INPUT_FILETYPE get_input_filetype_arg(char const *const arg)
{
	if (streq(arg, "milomesh") || streq(arg, "milom")) {
		return IFILETYPE_MILO_MESH;
	} else if (streq(arg, "milotex") || streq(arg, "milot")) {
		return IFILETYPE_MILO_TEX;
	}
	return IFILETYPE_UNKNOWN;
}

SUPPORTED_OUTPUT_FILETYPE get_output_filetype_arg(char const *const arg)
{
	if (streq(arg, "obj") || streq(arg, "wavefront")) {
		return OFILETYPE_WAVEFRONT_OBJ;
	} else if (streq(arg, "pam")) {
		return OFILETYPE_NETPBM_PAM;
	}
	return OFILETYPE_UNKNOWN;
}

SUPPORTED_INPUT_FILETYPE get_input_filetype_ext(char const *const ext)
{
	if (streq(ext, "milomesh") || streq(ext, "milom")) {
		return IFILETYPE_MILO_MESH;
	} else if (streq(ext, "milotex") || streq(ext, "milot")) {
		return IFILETYPE_MILO_TEX;
	}
	return IFILETYPE_UNKNOWN;
}

SUPPORTED_OUTPUT_FILETYPE get_output_filetype_ext(char const *const ext)
{
	if (streq(ext, "obj")) {
		return OFILETYPE_WAVEFRONT_OBJ;
	} else if (streq(ext, "pam")) {
		return OFILETYPE_NETPBM_PAM;
	}
	return OFILETYPE_UNKNOWN;
}

bool is_conversion_supported(SUPPORTED_INPUT_FILETYPE in, SUPPORTED_OUTPUT_FILETYPE out)
{
	if (in == IFILETYPE_UNKNOWN || out == OFILETYPE_UNKNOWN)
		return false;

	if (in == IFILETYPE_MILO_MESH && out == OFILETYPE_WAVEFRONT_OBJ)
		return true;

	if (in == IFILETYPE_MILO_TEX && out == OFILETYPE_NETPBM_PAM)
		return true;

	return false;

	/* Until we can promise reliable conversions between various formats,
	 * we should just bruteforce check and not actually use this code.
	 * Note that the enum values were specifically designed along with the
	 * macros TYPE_MESH, TYPE_TEX, TYPE_MAT, etc. so that this code
	 * WILL work even if you uncomment it now.
	 */
	// return (in & TYPE_MASK) == (out & TYPE_MASK);
}

bool conv_milotex_to_pam(char const *const miloFilePath, char const *const pamFilePath)
{
	FILE *miloTexFile = fopen(miloFilePath, "r");
	FILE *pamFile = fopen(pamFilePath, "w");
	bool ret = true;

	if (miloTexFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for reading: %s\n",
				miloFilePath, strerror(errno));
		return false;
	} else if (pamFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for writing: %s\n",
				pamFilePath, strerror(errno));
		return false;
	}

	MILO_TEXTURE miloTexData = milo_texture_load(miloTexFile);
	MILO_BITMAP miloBmp = miloTexData.bmp;

	fputs("P7\n", pamFile);
	fprintf(pamFile, "WIDTH %u\n", miloBmp.width);
	fprintf(pamFile, "HEIGHT %u\n", miloBmp.height);
	fputs("DEPTH 4\n", pamFile);
	fputs("MAXVAL 255\n", pamFile);
	fputs("TUPLTYPE RGB_ALPHA\n", pamFile);
	fputs("ENDHDR\n", pamFile);

	for (int y = 0; y < miloBmp.height; ++y) {
		for (int x = 0; x < miloBmp.width; ++x) {
			u8 pixel;
			if (miloBmp.bpp == 8) {
				pixel = miloBmp.texData[x + y * miloBmp.width];
			} else if (miloBmp.bpp == 4) {
				size_t addr = (x / 2) + y * (miloBmp.width / 2);
				u8 shift = (x & 1) << 2;
				u8 mask = 0xF << shift;
				pixel = (miloBmp.texData[addr] & mask) >> shift;
			} else {
				fprintf(stderr, "Unsupported number of bits per pixel (%u bpp) in texture file `%s`",
						miloBmp.bpp,
						miloFilePath);
				goto CLEAN_UP_FAILURE;
			}
			MILO_COLOR_8888 color = miloBmp.colorPalette[pixel];
			color = milo_color_8888_fix_alpha(color);
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
	fclose(miloTexFile);
	fclose(pamFile);
	return ret;
}

bool conv_milomesh_to_obj(char const *const miloFilePath, char const *const objFilePath)
{
	FILE *miloMeshFile = fopen(miloFilePath, "r");
	FILE *objMeshFile = fopen(objFilePath, "w");

	if (miloMeshFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for reading: %s\n",
				miloFilePath, strerror(errno));
		return false;
	} else if (objMeshFile == NULL) {
		fprintf(stderr, "Failed to open file `%s` for writing: %s\n",
				objFilePath, strerror(errno));
		return false;
	}

	MILO_MESH_FILE_GH miloMeshData = milo_mesh_load(miloMeshFile);
	fclose(miloMeshFile);
	OBJData obj = obj_from_milo(miloMeshData);

	fputs("# Generated using " PROGRAM_NAME " " PROGRAM_VERSION "\n", objMeshFile);
	obj_write(obj, objMeshFile);

	fclose(objMeshFile);
	return true;
}

void print_help(char const *const fileName, FILE *const writeTo)
{
	fputs(PROGRAM_NAME PROGRAM_VERSION"\n", writeTo);

	fprintf(writeTo, "%s [-h | --help]: Show this help text.\n", fileName);
	fprintf(writeTo, "%s [-i | --input <inputtype>] [-o | --output <outputtype>] <input> <output>: Convert files. If -i or -o aren't provided, guess corresponding file type from extension.\n", fileName);
}

void print_entire_file(FILE *file)
{
	size_t fileLen = 0;
	int c;
	while ((c = getc(file)) != EOF) {
		// dump everything in the file to stdout with binary representation for debugging, newlining every 8 indices
		fileLen++;
		printf(" 0x%02x ", c);
		printf("%u", (c & 0x80 ? 1 : 0));
		printf("%u", (c & 0x40 ? 1 : 0));
		printf("%u", (c & 0x20 ? 1 : 0));
		printf("%u ", (c & 0x10 ? 1 : 0));
		printf("%u", (c & 0x08 ? 1 : 0));
		printf("%u", (c & 0x04 ? 1 : 0));
		printf("%u", (c & 0x02 ? 1 : 0));
		printf("%u ", (c & 0x01 ? 1 : 0));
		if (fileLen % 4 == 0) printf("  ");
		if (fileLen % 8 == 0) printf("\n");
	}
	printf("len: %lu\n",fileLen);
	fseek(file, 0, 0);
}

size_t fsize(FILE *file)
{
	size_t curr = ftell(file);
	fseek(file, 0, SEEK_END);
	size_t len = ftell(file);
	fseek(file, curr, SEEK_SET);
	return len;
}
