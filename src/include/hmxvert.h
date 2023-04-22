// hmxvert.h - Harmonix vertex struct
#ifndef HMXVERT_H
#define HMXVERT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float X; // standard coord system
    float Y; // standard coord system
    float Z; // standard coord system
    float NormX; // normal map coords
    float NormY; // normal map coords
    float NormZ; // normal map coords
    float R; // 0-1
    float G; // 0-1
    float B; // 0-1
    float A; // 0-1, usually like half cause hmx
    float U; // texture space stuff
    float V; // texture space stuff
} HX_VERT_GH;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
