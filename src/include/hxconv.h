// hxconv.h - Harmonix converter (main) header file
#ifndef HXCONV_H
#define HXCONV_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#define _GNU_SOURCE // For fcloseall()
#include <stdio.h>
#undef _GNU_SOURCE
#include <string.h>
#include "hmxcommon.h"

#define BIT(n) (1 << n)
#define BITMASK(length, shift)	((BIT(length) - 1) << shift)

#define FORMAT_SHIFT 0
#define FORMAT_BIT_COUNT 4
#define FORMAT_MASK	BITMASK(FORMAT_BIT_COUNT, FORMAT_SHIFT)
#define FORMAT(n)	((n & FORMAT_MASK) << FORMAT_SHIFT)

#define TYPE_SHIFT	FORMAT_BIT_COUNT
#define TYPE_BIT_COUNT	4
#define TYPE_MASK	BITMASK(TYPE_BIT_COUNT, TYPE_SHIFT)
#define TYPE(n)		((n & TYPE_MASK) << TYPE_SHIFT)

#define TYPE_MESH	TYPE(0)
#define TYPE_TEX	TYPE(1)
#define TYPE_MAT	TYPE(2)
#define TYPE_SCENE	TYPE(3)

typedef enum {
	IFILETYPE_UNKNOWN = -1,
	IFILETYPE_HX_MESH = TYPE_MESH | FORMAT(0),
} SUPPORTED_INPUT_FILETYPE;

typedef enum {
	OFILETYPE_UNKNOWN = -1,
	OFILETYPE_WAVEFRONT_OBJ = TYPE_MESH | FORMAT(0),
} SUPPORTED_OUTPUT_FILETYPE;

size_t fsize(FILE *file);
void print_entire_file(FILE *file);
void print_help(char const *const fileName, FILE *const writeTo);
bool conv_hxmesh_to_obj(char const *const hxFilePath, char const *const objFilePath);

SUPPORTED_INPUT_FILETYPE get_input_filetype_arg(char const *const arg);
SUPPORTED_OUTPUT_FILETYPE get_output_filetype_arg(char const *const arg);

SUPPORTED_INPUT_FILETYPE get_input_filetype_ext(char const *const arg);
SUPPORTED_OUTPUT_FILETYPE get_output_filetype_ext(char const *const arg);

INLINE bool streq(char const *const lhs, char const *const rhs)
{
	return (strcmp(lhs, rhs) == 0);
}

int main(int const argc, char const *const *const argv);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
