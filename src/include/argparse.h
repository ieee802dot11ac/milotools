// argparse.h - Parsing the args!
#ifndef ARGPARSE_H
#define ARGPARSE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include "filetypes.h"
#include <string.h>

typedef struct {
	char const *inputPath;
	char const *outputPath;
	char const *recursePath;
	SUPPORTED_INPUT_FILETYPE inputFileType;
	SUPPORTED_OUTPUT_FILETYPE outputFileType;
} HXConverterArgs;

us fsize(FILE *file);
void print_help(char const *const fileName, FILE *const writeTo);

int parse_args(int const argc, char const *const *const argv, HXConverterArgs *result);
int guess_filetypes_if_unknown(HXConverterArgs *result);

SUPPORTED_INPUT_FILETYPE get_input_filetype_arg(char const *const arg);
SUPPORTED_OUTPUT_FILETYPE get_output_filetype_arg(char const *const arg);

SUPPORTED_INPUT_FILETYPE get_input_filetype_ext(char const *const arg);
SUPPORTED_OUTPUT_FILETYPE get_output_filetype_ext(char const *const arg);

INLINE bool streq(char const *const lhs, char const *const rhs)
{
	return (strcmp(lhs, rhs) == 0);
}



#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
