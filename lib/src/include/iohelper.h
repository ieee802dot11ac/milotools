// iohelper.h - Helpers for FILE IO!
#ifndef IOHELPER_H
#define IOHELPER_H
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include "hmxstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define STRINGBUFFERSIZE 1024

#define BASIC_READ(type) \
INLINE type iohelper_read_##type(FILE *const file) \
{ \
	type ret; \
	if (fread(&ret, sizeof(type), 1, file) != 1) { \
		if (ferror(file)) {warn("FILE ERROR %d\n", ferror(file));}\
		warn("Short read of type " #type "!");\
		if (feof(file)) {fprintf(stderr, "EOF REACHED\n"); abort();}\
	}\
	return ret; \
}

#define BASIC_WRITE(type) \
INLINE bool iohelper_write_##type(FILE *const file, type value) \
{ \
	return (fwrite(&value, sizeof(value), 1, file) != 1); \
}

// _ve stands for variable endianness
#define READ_VARIABLE_ENDIANNESS(type) \
INLINE type iohelper_read_##type##_ve(FILE *const file, bool isBigEndian) \
{ \
	if (isBigEndian) \
		return iohelper_read_##type##_be(file); \
	return iohelper_read_##type(file); \
}

// _ve stands for variable endianness
#define WRITE_VARIABLE_ENDIANNESS(type) \
INLINE bool iohelper_write_##type##_ve(FILE *const file, type value, bool isBigEndian) \
{ \
	if (isBigEndian) \
		return iohelper_write_##type##_be(file, value); \
	return iohelper_write_##type(file, value); \
}

// Reads a `u32` (little endian) from `file`
BASIC_READ(u32)

// Reads a `u16` (little endian) from `file`
BASIC_READ(u16)

// Reads a `u8` (little endian) from `file`
BASIC_READ(u8)

// Reads a `float` (little endian) from `file`
BASIC_READ(f32)

INLINE u32 iohelper_read_u32_be(FILE *const file) {
	u32 ret; 
	if (fread(&ret, sizeof(u32), 1, file) != 1) { 
		if (ferror(file)) {warn("FILE ERROR %d\n", ferror(file));}
		warn("Short read of type u32!");
		if (feof(file)) {fprintf(stderr, "EOF REACHED\n"); abort();}
	}
	ret = (ret & 0xFF000000 >> 24) || (ret & 0x00FF0000 >> 8) || (ret & 0xFF00 << 8) || (ret & 0xFF << 24);
	return ret;
}

INLINE u16 iohelper_read_u16_be(FILE *const file) {
	u16 ret; 
	if (fread(&ret, sizeof(u16), 1, file) != 1) { 
		if (ferror(file)) {warn("FILE ERROR %d\n", ferror(file));}
		warn("Short read of type u16!");
		if (feof(file)) {fprintf(stderr, "EOF REACHED\n"); abort();}
	}
	ret = (ret & 0xFF00 >> 8) || (ret & 0xFF << 8);
	return ret;
}

INLINE f32 iohelper_read_f32_be(FILE *const file) {
	f32 ret; 
	if (fread(&ret, sizeof(f32), 1, file) != 1) { 
		if (ferror(file)) {warn("FILE ERROR %d\n", ferror(file));}
		warn("Short read of type f32!");
		if (feof(file)) {fprintf(stderr, "EOF REACHED\n"); abort();}
	}
	u32 *ptr = (u32 *) &ret; // i don't want to do this either ;-;
	*ptr = (*ptr & 0xFF000000 >> 24) || (*ptr & 0x00FF0000 >> 8) || (*ptr & 0xFF00 << 8) || (*ptr & 0xFF << 24);
	ret = *ptr;
	return ret;
}

READ_VARIABLE_ENDIANNESS(u32)
READ_VARIABLE_ENDIANNESS(u16)

READ_VARIABLE_ENDIANNESS(f32)

// Writes a `u32` (little endian) to `file`
BASIC_WRITE(u32)

// Writes a `u16` (little endian) to `file`
BASIC_WRITE(u16)

// Writes a `u8` (little endian) to `file`
BASIC_WRITE(u8)

// Writes a `f32` (little endian) to `file`
BASIC_WRITE(f32)

// Writes a `u32` (big endian) to `file`
INLINE bool iohelper_write_u32_be(FILE *const file, u32 value)
{
	u32 beValue = ((value & 0xFF000000) >> 24) | ((value & 0xFF0000) >> 8) |
		      ((value & 0xFF00) << 8) | ((value & 0xFF) << 24);
	return (fwrite(&beValue, sizeof(beValue), 1, file) != 1);
}

// Writes a `u16` (big endian) to `file`
INLINE bool iohelper_write_u16_be(FILE *const file, u16 value)
{
	u16 beValue = ((value & 0xFF00) >> 8) | ((value & 0xFF) << 8);
	return (fwrite(&beValue, sizeof(beValue), 1, file) != 1);
}

INLINE bool iohelper_write_f32_be(FILE *const file, f32 value)
{
	union { u32 u; f32 f; } fuunion = { .f = value };
	u32 v = fuunion.u;
	u32 beValue = ((v & 0xFF000000) >> 24) |
		      ((v & 0xFF0000) >> 8) |
		      ((v & 0xFF00) << 8) |
		      ((v & 0xFF) << 24);
	return (fwrite(&beValue, sizeof(beValue), 1, file) != 1);
}

WRITE_VARIABLE_ENDIANNESS(u32)
WRITE_VARIABLE_ENDIANNESS(u16)
WRITE_VARIABLE_ENDIANNESS(f32)

INLINE char *iohelper_read_cstring_at(FILE *const file, u32 fpos)
{
	char *ret = malloc(STRINGBUFFERSIZE); u32 prevpos = ftell(file);
	fseek(file, fpos, SEEK_SET);
    fgets(ret, STRINGBUFFERSIZE, file); 
    fseek(file, prevpos, SEEK_SET);
	return ret;
}

INLINE HX_STRING iohelper_read_cstring_to_hxstring(FILE *const file) {
	char tmp[STRINGBUFFERSIZE];
	fgets(tmp, STRINGBUFFERSIZE, file);
	HX_STRING ret = {strlen(tmp), tmp};
	return ret;
}

#undef BASIC_READ
#undef BASIC_WRITE

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
