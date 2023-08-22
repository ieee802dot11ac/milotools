#include "hmxmilo.h"
#include "hmxstring.h"
#include "iohelper.h"
#include "zlibwrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CUSTOM_MILO_BLOCKSIZE 2048

int hmx_milo_decompress(FILE* file, char const *outfilename, bool isBigEndian) {
	HX_MILOHEADER* header = malloc(sizeof(HX_MILOHEADER));

	header->version[0] = iohelper_read_u8(file);
	header->version[1] = iohelper_read_u8(file);
	header->version[2] = iohelper_read_u8(file);
	header->version[3] = iohelper_read_u8(file);

	printf("0x%X%X%X%X\n", header->version[3], header->version[2], header->version[1], header->version[0]); // trust issues

	header->offset = iohelper_read_u32_ve(file, isBigEndian);
	header->blockCount = iohelper_read_u32_ve(file, isBigEndian);
	header->maxBlockSize = iohelper_read_u32_ve(file, isBigEndian); // sets max length. if we exceed this, oh shit
	header->sizes = malloc(4*header->blockCount);

	for (int i = 0; i < header->blockCount; i++) {
		header->sizes[i] = iohelper_read_u32_ve(file, isBigEndian);
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
	us outlen = strlen(outfilename) + 1;
	char outCopy[outlen + 16];
	for (int i = 0; i < header->blockCount; i++) {
		u8 *decompressed = malloc(2*header->sizes[i]);
		if (header->version[3] == 0xCB) {
			decompressed = decompress(compressed_data[i],header->sizes[i], false, false, NULL);
		} else if (header->version[3] == 0xCC) {
			printf("we can't auto-gunzip this, so you'll have to do it manually, sorry\n");
			decompressed = compressed_data[i];
			// copy outfilename first, so we don't end up destroying the stack with a strcat
			
			strcpy(outCopy, outfilename);
			strcat(outCopy, ".gz");
			// decompress(compressed_data[i],header->sizes[i], true, false, file);
		} else if (header->version[3] == 0xCD) {
			decompressed = decompress(compressed_data[i],header->sizes[i], false, true, NULL);
		} // gunzip freq your damn self
		else decompressed = compressed_data[i];
		memtemp = memcpy(memtemp, decompressed, header->sizes[i]);
	}
	FILE *out;
	if (header->version[3] == 0xCC) {
		out = fopen(outCopy, "w");
	} else {out = fopen(outfilename, "w");}
	fwrite(memMilo, 1, total, out);
	free(header->sizes);
	free(header);
	return 0;
}

int hmx_milo_compress(FILE* file, char const *outfilename, BlockStructure mode, bool isBigEndian) {
	return 0; // this would take effort. just. just no.
}

HX_MILOFILE *hmx_milo_load (FILE *file, bool isBigEndian) {
	HX_MILOFILE *milo = malloc(sizeof(HX_MILOFILE));
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
