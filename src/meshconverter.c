#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hmxstuff.h"

FILE* hxMeshFile;
FILE* objtowriteto;
HX_MESH_FILE_GH hxMeshData;

uint64_t fsize(FILE* file) {
	uint64_t curr = ftell(file);
	fseek(file, 0, SEEK_END);
	uint64_t len = (uint64_t)ftell(file);
	fseek(file, curr, 0);
	return len;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("no file, so sad\nusage: %s <mesh_file>\n", argv[0]); 
		return -1;
	}
	hxMeshFile = fopen(argv[1], "r");
	if (hxMeshFile == NULL) {
		printf("couldn't open file, so sad\n"); 
		fcloseall();
		return -1;
	}
	fread(&hxMeshData, 4, 2, hxMeshFile);
	if (hxMeshData.version != 25) {
		printf("bad file, so sad\n"); 
		fcloseall();
		return -1;
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
	printf("\n");
	fread(&hxMeshData.transform.transCount, 4, 1, hxMeshFile);
	printf("%i\n", hxMeshData.transform.transCount);
	if (hxMeshData.transform.transCount) { // i *do not* want to have to deal with these right now
		printf("fak\n"); 
		return -1;
	}
	fread(&hxMeshData.transform.constraint, 4, 1, hxMeshFile);
	printf("%i\n", hxMeshData.transform.constraint);
	if (hxMeshData.transform.constraint) { // i'm just lazy
		printf("fak 2\n"); 
		return -1;
	}
	fread(&hxMeshData.transform.preserveScale, 1, 1, hxMeshFile); 
	printf("%i\n", hxMeshData.transform.preserveScale); // irrelevant for single files
	hxMeshData.transform.parent = getRefFromFile(hxMeshFile);
	printf("%i %s\n", hxMeshData.transform.parent.strLen, hxMeshData.transform.parent.refName);
	/*
	for (int i = 0; i < hxMeshData.vertCount; i++) {
		printf("vert index %i: x %f y %f z %f", i, hxMeshData.vertTable[i].X, hxMeshData.vertTable[i].Y, hxMeshData.vertTable[i].Z);
	}
	*/
	fcloseall();
	return 0;
}
