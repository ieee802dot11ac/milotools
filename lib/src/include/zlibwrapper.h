// zlibwrapper.h: wrapper for zlib
#ifndef ZLIBWRAPPER
#define ZLIBWRAPPER
#ifdef __cplusplus
extern "C" {
#endif
#include "hmxcommon.h"

u8 *decompress(u8 *in_data, size_t len, bool method, bool post2010, FILE* fd);

#ifdef __cplusplus
}
#endif
#endif
