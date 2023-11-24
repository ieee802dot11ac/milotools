// hmxampark.h: .ark files, as seen in Amplitude; still not compressed
#ifndef HMXAMPARK_H
#define HMXAMPARK_H
#ifdef __cplusplus
extern "C" {
#endif
#include "hmxcommon.h"
#include "hmxstring.h"

typedef struct {
    u32 offset; // note: if version == 1, the offset is right before the size
    u32 fileNameIdx;
    u32 folderNameIdx;
    u32 size;
    u32 inflatedSize; // 0 = uncompressed
} FileEntry;

typedef struct {
    u32 version; // 1 == OPM, 2 == retail
    u32 entryCount;
    FileEntry* entries;

    u32 stringTableSize;
    HX_STRING* stringTable; // NOTE!!! use read_cstring_to_hmxstring for v2... i *think*

    u32 stringIdxCount;
    u32* stringIdxEntries;
} HX_AMPARK;

FileEntry* hmx_fileentry_load(FILE*, u32);

HX_AMPARK* hmx_ampark_load(FILE*);
void hmx_ampark_cleanup(HX_AMPARK*);
void hmx_ampark_print(HX_AMPARK*);

#ifdef __cplusplus
}
#endif
#endif
