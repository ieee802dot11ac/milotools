#include "hmxmilo.h"
#include "hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

HX_MILOFILE* hmx_milo_load(FILE* file, const char *outfilename, bool flatten) {
	HX_MILOFILE* milo = malloc(sizeof(HX_MILOFILE));
	HX_MILOHEADER* header = malloc(sizeof(HX_MILOHEADER));
	header->version[0] = iohelper_read_u8(file); header->version[1] = iohelper_read_u8(file); header->version[2] = iohelper_read_u8(file); header->version[3] = iohelper_read_u8(file);
	printf("0x%X%X%X%X\n", header->version[3], header->version[2], header->version[1], header->version[0]);

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
	size_t total = 0;
	for (int i = 0; i < header->blockCount; i++) total += header->sizes[i];
	u8 *memMilo = malloc(total);
	void *memtemp = memMilo;
	for (int i = 0; i < header->blockCount; i++) {
		u8 *decompressed = malloc(2*header->sizes[i]);
		if (header->version[3] == 0xCB) {
			decompressed = decompress(compressed_data[i],header->sizes[i], false, false, NULL);
		} else if (header->version[3] == 0xCC) {
			printf("no gzipped milo support!\n");
			return NULL;
			// decompress(compressed_data[i],header->sizes[i], true, false, file);
		} else if (header->version[3] == 0xCD) {
			decompressed = decompress(compressed_data[i],header->sizes[i], false, true, NULL);
		} // we can ignore freq for now, mostly because archiveexplorer keeps crashing on me so i couldn't test it if i wanted to
		else decompressed = compressed_data[i];
		memtemp = memcpy(memtemp, decompressed, header->sizes[i]);
	}
	if (flatten) {
		FILE *out = fopen(outfilename, "w");
		fwrite(memMilo, 1, total, out);
		return NULL;
	}
	free(header->sizes);
	free(header);
	return milo;
}

void hmx_milo_cleanup(HX_MILOFILE* milo) {
	if (milo == NULL) return;
	free(milo);
	return;
}

void hmx_milo_print(HX_MILOFILE* milo) {
	printf("version: %d\n", milo->version);
	printf("begin miloentries\n");
	if (milo->version > 10) {
		printf("dir type:"); hmx_string_print(milo->meta.dir_type);
		printf("\ndir name:\n"); hmx_string_print(milo->meta.dir_name);
	}
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
