#include "hmxmilo.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define ZLIB_MAGIC 0x789C // deflated, max compression; assumedly chosen because milo isn't being ran on a z80

HX_MILOFILE* hmx_milo_load(FILE* file) {
	HX_MILOFILE* milo = malloc(sizeof(HX_MILOFILE));
	HX_MILOHEADER* header = malloc(sizeof(HX_MILOHEADER));
	header->version[0] = iohelper_read_u8(file); header->version[1] = iohelper_read_u8(file); header->version[2] = iohelper_read_u8(file); header->version[3] = iohelper_read_u8(file);
	printf("0x%X\n", header->version[3]);
	header->offset = iohelper_read_u32(file);
	header->blockCount = iohelper_read_u32(file);
	header->maxBlockSize = iohelper_read_u32(file); // sets max length. if we exceed this, oh shit
	header->sizes = malloc(4*header->blockCount);
	for (int i = 0; i < header->blockCount; i++) {
		header->sizes[i] = iohelper_read_u32(file);
	}
	fseek(file, header->offset, SEEK_SET);
	u8 *compressed_data[header->blockCount];
	for (int i = 0; i < header->blockCount; i++) {
		compressed_data[i] = malloc(header->sizes[i]);
		bool successful = header->sizes[i] == fread(compressed_data[i], 1, header->sizes[i], file);
		if (!successful) {
			perror("bad read!\n");
		}
	}
	if (header->version[3] == 0xCB) {
		FILE* out = fopen("alterna_dumped.bin", "w");
		for (int i = 0; i < header->blockCount; i++) {
			u8 *decompressed = decompress(compressed_data[i],header->sizes[i], false, false, NULL);
			(void)fwrite(decompressed, 1, header->sizes[i], out);
		}
	}
	return milo;
}

void hmx_milo_cleanup(HX_MILOFILE* milo) {
	free(milo);
	return;
}

void hmx_milo_print(HX_MILOFILE* milo) {
	milo->version = 3;
	return;
}

u8 *decompress(u8 *in_data, size_t len, bool method, bool post2010, FILE* fd) { // method: 0=zlib 1=gzip post2010: 0=no_offset 1=4offset
	u8 *out_data = malloc(len);
	if (method) {
		gzdopen(fileno(fd), "r");
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
