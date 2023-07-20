#include "zlibwrapper.h"
#include "hmxcommon.h"
#include <zlib.h>
#include <stdlib.h>
u8 *decompress(u8 *in_data, size_t len, bool method, bool post2010, FILE* gzfd) { // method: 0=zlib 1=gzip post2010: 0=no_offset 1=4offset
	u8 *out_data = malloc(len);
	if (method) {
		gzdopen(fileno(gzfd), "r");
		int status = gzread(NULL, in_data, len);
		if (status != Z_OK) {
			perror("gzread died!\n");
			return NULL;
		}
		return out_data;
	} else {
		struct z_stream_s stream;
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;
		stream.opaque = Z_NULL;
		stream.avail_in = 0;
		stream.next_in = Z_NULL;
		int status = inflateInit2(&stream, -15);
		if (status != Z_OK) {
			perror("inflateinit2 died!\n");
			return NULL;
		}
		stream.avail_in = len;
		stream.next_in = (post2010 ? in_data+4 : in_data);
		stream.avail_out = len;
		stream.next_out = out_data;
		status = inflate(&stream, Z_NO_FLUSH);
		inflateEnd(&stream);
		return out_data;
	}
}

u8 *recompress(u8 *in_data, size_t len, bool method, bool post2010, size_t chunk) {
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
		status = inflate(&stream, Z_NO_FLUSH);
		inflateEnd(&stream);
		return out_data;
	}
}
