// hxconv.h - Harmonix converter (main) header file
#ifndef HXCONV_H
#define HXCONV_H
#ifdef __cplusplus
extern "C" {
#endif


#define _GNU_SOURCE // For fcloseall()
#include <stdio.h>
#undef _GNU_SOURCE
#include <string.h>
#include "converters.h"


int main(int const argc, char const *const *const argv);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
