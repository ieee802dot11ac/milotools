#include "hmxcolor.h"
#include "spngwrapper.h"
#include "hmxcommon.h"
#include <assert.h>
#include <spng.h>
#include <stdlib.h>
#include "iohelper.h"
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <errno.h>


bool export_png(char const *const expPath, u32 const width, u32 const height, HX_COLOR_8888 const *const pixels)
{
	FILE *outFile = fopen(expPath, "w");
	if (outFile == NULL) {
		warn("Could not open file %s", expPath);
		return true;
	}

	spng_ctx *ctx = spng_ctx_new(SPNG_CTX_ENCODER);
	spng_set_option(ctx, SPNG_ENCODE_TO_BUFFER, 1);

	struct spng_ihdr ihdr = {0};
	ihdr.width = width;
	ihdr.height = height;
	ihdr.bit_depth = 8;
	ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;
	spng_set_ihdr(ctx, &ihdr);

	int ret = spng_encode_image(ctx, pixels,
				    width * height * sizeof(HX_COLOR_8888),
				    SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
	if (ret) {
		printf("spng_encode_image() error: %s\n", spng_strerror(ret));
		goto CLEANUP;
	}

	us pngSize;
	void *pngBuf = NULL;

	pngBuf = spng_get_png_buffer(ctx, &pngSize, &ret);
	if (ret) {
		printf("spng_get_png_buffer() error: %s\n", spng_strerror(ret));
		goto CLEANUP;
	}

	fwrite(pngBuf, 1, pngSize, outFile);

	free(pngBuf);
CLEANUP:
	spng_ctx_free(ctx);
	fclose(outFile);
	return true;
}
