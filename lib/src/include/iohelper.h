// iohelper.h - Helpers for FILE IO!
#ifndef IOHELPER_H
#define IOHELPER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include <stdio.h>

#define BASIC_READ(type) \
	type ret; \
	fread(&ret, sizeof(type), 1, fp); \
	return ret;

INLINE u32 iohelper_readu32(FILE *fp)
{
	BASIC_READ(u32);
}

INLINE u16 iohelper_readu16(FILE *fp)
{
	BASIC_READ(u16);
}

INLINE u8 iohelper_readu8(FILE *fp)
{
	BASIC_READ(u8);
}

INLINE float iohelper_readf(FILE *fp)
{
	BASIC_READ(float);
}


#undef BASIC_READ

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
