// hmxtexture.c - Harmonix texture information
#ifndef HMXTEXTURE_C
#define HMXTEXTURE_C
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "hmxcommon.h"
#include "hmxbitmap.h"
#include "hmxstring.h"

typedef struct {
	u32 version;
	u32 width;
	u32 height;
	u32 bpp;
	HX_STRING bmpName;
	float index_f;
	u32 index;
	bool useExtPath;
	HX_BITMAP bmp;
} HX_TEXTURE;

HX_TEXTURE hmx_texture_load(FILE *file);
void hmx_texture_print(HX_TEXTURE tex);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
