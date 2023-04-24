// spngwrapper.h - Because libPNG sucks and spng is epic.
#ifndef SPNGWRAPPER_H
#define SPNGWRAPPER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcolor.h"
#include "hmxcommon.h"

// Export a 32bpp RGBA PNG sized `width` x `height` to `expPath`
// `pixels` should be encoded x-first (horizontal scanlines from top left to right, then down)
// Returns true on failure!
bool export_png(char const *const expPath,
	        unsigned int const width, unsigned int const height,
	        HX_COLOR_8888 const *const pixels);

#endif
