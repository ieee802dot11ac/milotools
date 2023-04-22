#include <stddef.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hmxref.h"
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
	print_entire_file(hxMeshFile);

	if (hxMeshFile == NULL) {
		printf("couldn't open file, so sad\n"); 
		goto EXIT_FAILED;
	}
	fread(&hxMeshData, 4, 2, hxMeshFile);
	if (hxMeshData.version != 25) {
		printf("bad file, so sad\n"); 
		goto EXIT_FAILED;
	}
	printf("mesh ver: (GH1 is 25) %i", hxMeshData.version);
	fread(&hxMeshData.transform.localTransMtx, sizeof(float), 24, hxMeshFile);
	for (int i = 0; i < 12; i++) {
		if (i % 4 == 0) printf("\n");
		printf("%f ", hxMeshData.transform.localTransMtx[i]);
	}
	for (int i = 0; i < 12; i++) {
		if (i % 4 == 0) printf("\n");
		printf("%f ", hxMeshData.transform.worldTransMtx[i]);
	}
	printf("\nftell location (should be 104): %i\n", (int)ftell(hxMeshFile));
	fread(&hxMeshData.transform.transCount, 4, 1, hxMeshFile);
	printf("%i\n", hxMeshData.transform.transCount);
	if (hxMeshData.transform.transCount) { // i *do not* want to have to deal with these right now
		printf("fak\n"); 
		goto EXIT_FAILED;
	}
	printf("\nftell location (should be 108): %i\n", (int)ftell(hxMeshFile));
	fread(&hxMeshData.transform.constraint, 4, 1, hxMeshFile);
	printf("%i\n", hxMeshData.transform.constraint);
	if (hxMeshData.transform.constraint) { // i'm just lazy
		printf("fak 2\n"); 
		goto EXIT_FAILED;
	}
	printf("\nftell location (should be 112): %i\n", (int)ftell(hxMeshFile));
	fread(&hxMeshData.transform.preserveScale, 1, 1, hxMeshFile); 
	printf("%i\n", hxMeshData.transform.preserveScale); // irrelevant for single files
	printf("ftell location (should be 113): %i\n", (int)ftell(hxMeshFile));
	fseek(hxMeshFile, 4, SEEK_CUR);
	hxMeshData.transform.parent = extref_from_file(hxMeshFile);
	printf("%i %s\n", hxMeshData.transform.parent.strLen, hxMeshData.transform.parent.refName);
	printf("ftell location (should be 113 + strLen): %i\n", (int)ftell(hxMeshFile));
	fread(&hxMeshData.bounding, sizeof(HX_SPHERE), 1, hxMeshFile);
	printf("xyzr %f %f %f %f\n", hxMeshData.bounding.x, hxMeshData.bounding.y, hxMeshData.bounding.z, hxMeshData.bounding.r);
	/*
	for (int i = 0; i < hxMeshData.vertCount; i++) {
		printf("vert index %i: x %f y %f z %f", i, hxMeshData.vertTable[i].X, hxMeshData.vertTable[i].Y, hxMeshData.vertTable[i].Z);
	}
	*/

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
