// mconv.h - Mesh converter (main) header file
#ifndef MCONV_H
#define MCONV_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#define _GNU_SOURCE // For fcloseall()
#include <stdio.h>
#undef _GNU_SOURCE
#include <string.h>
#include "hmxcommon.h"

size_t fsize(FILE *file);
void print_entire_file(FILE *file);
void print_help(char const *const fileName, FILE *const writeTo);
bool convert_hmx_to_obj(char const *const hxFilePath, char const *const objFilePath);

INLINE bool streq(char const *const lhs, char const *const rhs)
{
	return (strcmp(lhs, rhs) == 0);
}

int main(int const argc, char const *const *const argv);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
