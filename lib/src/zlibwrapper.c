#include "zlibwrapper.h"
#include "hmxcommon.h"
#include "puff.h" // to alleviate decompression woes
#include <zlib.h>
#include <stdlib.h>
u8 *decompress(u8 *in_data, size_t len, bool method, bool post2010, FILE* gzfd) { // method: f=zlib t=gzip post2010: f=no_offset t=4offset
	u8 *out_data = malloc(len); // temp, didn't wanna leave it init'd to null cause i'm an idiot
	if (method) {
		gzdopen(fileno(gzfd), "r");
		int status = gzread(NULL, in_data, len);
		if (status != Z_OK) {
			perror("gzread died!\n");
			return NULL;
		}
		return out_data;
	} else {
		unsigned long outlen = 0;
		puff(NIL, &outlen, in_data, &len); // gets size of outdata, NIL is provided by puff
		out_data = realloc(out_data, outlen);
		puff(out_data, &outlen, in_data, &len);
		return out_data;
	}
}

/*u8 *recompress(u8 *in_data, size_t len, bool method, bool post2010, size_t chunk) { // TODO make this work properly cause i fuckin hate zlib
	u8 *out_data = malloc(len);
	if (method) {
		return out_data;
	} else {
		struct z_stream_s stream;
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;
		stream.opaque = Z_NULL;
		stream.avail_in = 0;
		stream.next_in = Z_NULL;
		int status = deflateInit(&stream, -15);
		if (status != Z_OK) {
			perror("deflateInit died!\n");
			return NULL;
		}
		stream.avail_in = len;
		stream.next_in = (post2010 ? in_data+4 : in_data);
		stream.avail_out = len;
		stream.next_out = out_data;
		status = deflate(&stream, Z_NO_FLUSH);
		deflateEnd(&stream);
		return out_data;
	}
}*/
