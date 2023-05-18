// converters.h - Conversion functions
#ifndef CONVERTERS_H
#define CONVERTERS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "argparse.h"
#include <stdbool.h>
#include "hmx.h"


int convert(HXConverterArgs args);

bool conv_hxbmp_to_png(HX_BITMAP hxBmp, char const *const pngFilePath);
bool conv_hxtex_to_png(char const *const hxFilePath, char const *const pngFilePath);

bool conv_hxbmp_to_pam(HX_BITMAP *hxBmp, char const *const pamFilePath);
bool conv_hxtex_to_pam(char const *const hxFilePath, char const *const pamFilePath);

bool conv_hxmesh_to_obj(char const *const hxFilePath, char const *const objFilePath, char const *const recursePath);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
