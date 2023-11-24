#include "hmxampark.h"
#include "include/hmxstring.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>

FileEntry* hmx_fileentry_load(FILE* file, u32 ver) {
    FileEntry* fentry = malloc(sizeof(FileEntry));
    if (ver != 1) fentry->offset = iohelper_read_u32(file);
    fentry->fileNameIdx = iohelper_read_u32(file);
    fentry->folderNameIdx = iohelper_read_u32(file);
    if (ver == 1) fentry->offset = iohelper_read_u32(file);
    fentry->size = iohelper_read_u32(file);
    fentry->inflatedSize = iohelper_read_u32(file);
    return fentry;
}

HX_AMPARK* hmx_ampark_load(FILE* file) {
    HX_AMPARK* ark = malloc(sizeof(HX_AMPARK));
    ark->version = iohelper_read_u32(file);
    ark->entryCount = iohelper_read_u32(file);
    ark->entries = malloc(sizeof(FileEntry) * ark->entryCount);
    for (u32 i = 0; i < ark->entryCount; i++) {
        ark->entries[i] = *hmx_fileentry_load(file, ark->version);
    }

    ark->stringTableSize = iohelper_read_u32(file);

    if (ark->version == 2) { // why would you abandon the nice strings...?
        ark->stringTable = malloc(sizeof(HX_STRING) * ark->stringTableSize);
        for (u32 i = 0; i < ark->stringTableSize; i++) {
            ark->stringTable[i] = iohelper_read_cstring_to_hxstring(file);
        }
        ark->stringIdxCount = iohelper_read_u32(file);
        ark->stringIdxEntries = malloc(4*ark->stringIdxCount);
        for (u32 i = 0; i < ark->stringIdxCount; i++) {
            ark->stringIdxEntries[i] = iohelper_read_u32(file);
        }
    } else { // v1 // hopefully
        for (u32 i = 0; i < ark->stringTableSize; i++) {
            ark->stringTable[i] = hmx_string_load(file, false); // amp only released on ps2
        }
    }
    return ark;
}

void hmx_ampark_print(HX_AMPARK * ark) {
    printf("VERSION: %d\n", ark->version);
    printf("FILE ENTRY COUNT: %d\n", ark->entryCount);

    printf("BEGIN FILE ENTRY LISTINGS\nMAKE REGRETTABLE DECISION? (y/n)\n");
    u32 dingus = fgetc(stdin);
    if ((dingus | 0x20) == 'n') goto noprint; // should be right... hopefully? 0x41 vs 0x61

    for (u32 i = 0; i < ark->entryCount; i++) {
        printf("ENTRY %d OFFSET: %d\n", i, ark->entries[i].offset);
        printf("ENTRY %d FILE NAME INDEX: %d\n", i, ark->entries[i].fileNameIdx);
        printf("ENTRY %d FOLDER NAME INDEX: %d\n", i, ark->entries[i].folderNameIdx);
        printf("ENTRY %d SIZE: %d\n", i, ark->entries[i].size);
        printf("ENTRY %d INFLATED SIZE: %d\n", i, ark->entries[i].inflatedSize);
    }

noprint:
    printf("STRING TABLE SIZE: %d\n", ark->stringTableSize);

    if (ark->version == 2) {
        for (u32 i = 0; i < ark->stringTableSize; i++) {
            printf("STRING %d: %s", i, hmx_string_cstring(ark->stringTable[i]));
        }
        printf("STRING INDEX SIZE: %d", ark->stringIdxCount);
        for (u32 i = 0; i < ark->stringIdxCount; i++) {
            printf("STRING INDEX %d", ark->stringIdxEntries[i]);
        }
    }
}

void hmx_ampark_cleanup(HX_AMPARK * ark) {
    free(ark); // bad!! don't do!! temporary hack!!
}

