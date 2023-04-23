// milo_vertex.h - Harmonix vertex struct
#ifndef MILO_VERTEX_H
#define MILO_VERTEX_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>


typedef struct {
    float x; // standard coord system
    float y; // standard coord system
    float z; // standard coord system
    float normX; // normal map coords
    float normY; // normal map coords
    float normZ; // normal map coords
    float r; // 0-1
    float g; // 0-1
    float b; // 0-1
    float a; // 0-1, usually like half cause milo_
    float u; // texture space stuff
    float v; // texture space stuff
} MILO_VERTEX;


MILO_VERTEX milo_vertex_load(FILE *file);
void milo_vertex_print(MILO_VERTEX vertex);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
