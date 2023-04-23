// milo_texture.c - Milo texture information
#ifndef MILO_TEXTURE_C
#define MILO_TEXTURE_C
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "milo_common.h"
#include "milo_bitmap.h"
#include "milo_string.h"

typedef struct {
	u32 version;
	u32 width;
	u32 height;
	u32 bpp;
	MILO_STRING bmpName;
	float index_f;
	u32 index;
	bool useExtPath;
	MILO_BITMAP bmp;
} MILO_TEXTURE;

MILO_TEXTURE milo_texture_load(FILE *file);
void milo_texture_print(MILO_TEXTURE tex);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
