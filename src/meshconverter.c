#include <stddef.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hmxreference.h"
#include "hmx.h"

FILE *hxMeshFile;
FILE *objtowriteto;
HX_MESH_FILE_GH hxMeshData;

size_t fsize(FILE *file);
void print_entire_file(FILE *file);

int main(int argc, char **argv)
{
	int exitCode = EXIT_FAILURE;
	if (argc < 2) {
		printf("no file, so sad\nusage: %s <mesh_file>\n", argv[0]); 
		goto EXIT_FAILED;
	}

	hxMeshFile = fopen(argv[1], "r");
	if (hxMeshFile == NULL) {
		printf("couldn't open file, so sad\n"); 
		goto EXIT_FAILED;
	}
	// print_entire_file(hxMeshFile);

	hxMeshData = hmx_mesh_load(hxMeshFile);
	hmx_mesh_print(hxMeshData);

	exitCode = EXIT_SUCCESS;
EXIT_FAILED:
	fcloseall();
	return exitCode;
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
