#include <stdbool.h>
#include <stddef.h>
#define _GNU_SOURCE // For fcloseall()
#include <stdio.h>
#undef _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "hmxcommon.h"
#include "hmxreference.h"
#include "hmx.h"
#include "mconv.h"


int main(int const argc, char const *const *const argv)
{
	int exitCode = EXIT_FAILURE;

	char const *hmxPath = NULL;
	char const *objPath = NULL;
	bool acceptPosixArgs = true;

	for (int i = 1; i < argc; ++i) {
		char const *const arg = argv[i];
		if (acceptPosixArgs) {
			if (streq(arg, "--")) {
				acceptPosixArgs = false;
			} else if (streq(arg, "--help") || streq(arg, "-h")) {
				print_help(argv[0], stdout);
				goto EXIT_SUCCEED;
			} else {
				goto ACCEPT_PATHS;
			}
			continue;
		}
ACCEPT_PATHS:
		if (hmxPath == NULL) {
			hmxPath = arg;
		} else if (objPath == NULL) {
			objPath = arg;
		} else {
			fputs("Too many arguments provided!\n", stderr);
			print_help(argv[0], stderr);
			goto EXIT_FAILED;
		}
	}

	if (hmxPath == NULL) {
		fputs("No input or output file provided!\n\n", stderr);

		print_help(argv[0], stderr);
		goto EXIT_FAILED;
	} else if (objPath == NULL) {
		fputs("No output file provided!\n\n", stderr);

		print_help(argv[0], stderr);
		goto EXIT_FAILED;
	}

	FILE *hxMeshFile;
	FILE *objtowriteto;
	HX_MESH_FILE_GH hxMeshData;

	hxMeshFile = fopen(argv[1], "r");
	if (hxMeshFile == NULL) {
		fprintf(stderr, "Failed to open file %s: %s\n",
				argv[1], strerror(errno));
		goto EXIT_FAILED;
	}
	// print_entire_file(hxMeshFile);

	hxMeshData = hmx_mesh_load(hxMeshFile);
	hmx_mesh_print(hxMeshData);

EXIT_SUCCEED:
	exitCode = EXIT_SUCCESS;
EXIT_FAILED:
	fcloseall();
	return exitCode;
}

void print_help(char const *const fileName, FILE *const writeTo)
{
	fputs("HMXOBJConverter v0.1.0\n\n", writeTo);

	fprintf(writeTo, "%s [-h | --help]: Show this help text.\n", fileName);
	fprintf(writeTo, "%s <hmx_mesh_input> <obj_output>: Convert hmx mesh to obj file.\n", fileName);
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
