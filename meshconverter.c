#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hmxstuff.h"

FILE* workingmesh;
FILE* objtowriteto;
HX_MESH_FILE_GH meshFile;

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
    workingmesh = fopen(argv[1], "r");
    if (workingmesh == NULL) {
        printf("couldn't open file, so sad\n"); 
        fcloseall();
        return -1;
    }
    fread(&meshFile, 1, fsize(workingmesh), workingmesh);
    if (meshFile.version != 25) {
        printf("bad file, so sad\n"); 
        fcloseall();
        return -1;
    }
    printf("mesh ver: (GH1 is 25) %i", meshFile.version);
    fread(&meshFile.location.localTransMtx, sizeof(float), 24, workingmesh);
    for (int i = 0; i < 12; i++) {
        if (i % 4 == 0) printf("\n");
        printf("%f ", meshFile.location.localTransMtx[i]);
    }
    for (int i = 0; i < 12; i++) {
        if (i % 4 == 0) printf("\n");
        printf("%f ", meshFile.location.worldTransMtx[i]);
    }
    printf("\n");
    for (int i = 0; i < meshFile.vertCount; i++) {
        printf("vert index %i: x %f y %f z %f", i, meshFile.vertTable[i].X, meshFile.vertTable[i].Y, meshFile.vertTable[i].Z);
    }
    fcloseall();
    return 0;
}