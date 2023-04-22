// hmxvertex.h - Harmonix vertex struct
#ifndef HMXVERTEX_H
#define HMXVERTEX_H
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
    float a; // 0-1, usually like half cause hmx
    float u; // texture space stuff
    float v; // texture space stuff
} HX_VERTEX;


HX_VERTEX hmx_vertex_load(FILE *file);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
