#include "hmxfreqark.h"
#include "iohelper.h"
#include <stdio.h>
#include <stdlib.h>

HX_FREQARK *hmx_freq_ark_load(FILE *file, char const *outdir, bool isBigEndian) {
    HX_FREQARK *ark = malloc(sizeof(HX_FREQARK));

    ark->header.magic[0] = iohelper_read_u8(file);
    ark->header.magic[1] = iohelper_read_u8(file);
    ark->header.magic[2] = iohelper_read_u8(file);
    ark->header.magic[3] = iohelper_read_u8(file);

    ark->header.version = iohelper_read_u32_ve(file, isBigEndian);

    ark->header.file_entry_offset = iohelper_read_u32_ve(file, isBigEndian);
    ark->header.file_entry_count = iohelper_read_u32_ve(file, isBigEndian);

    ark->header.folder_entry_offset = iohelper_read_u32_ve(file, isBigEndian);
    ark->header.folder_entry_count = iohelper_read_u32_ve(file, isBigEndian);

    ark->header.string_table_offset = iohelper_read_u32_ve(file, isBigEndian);
    ark->header.string_count = iohelper_read_u32_ve(file, isBigEndian);
    
    ark->header.total_hdr_size = iohelper_read_u32_ve(file, isBigEndian);
    ark->header.block_size = iohelper_read_u32_ve(file, isBigEndian);
    
    ark->entries = malloc(sizeof(HX_FREQARK_FILEENTRY) * ark->header.file_entry_count);
    fseek(file, ark->header.file_entry_offset, SEEK_SET);
    
    for (u32 i = 0; i < ark->header.file_entry_count; i++) {
        ark->entries[i].unknown = iohelper_read_u32_ve(file, isBigEndian);
        ark->entries[i].file_name_offset = iohelper_read_u32_ve(file, isBigEndian);
        ark->entries[i].folder_name_index = iohelper_read_u16_ve(file, isBigEndian);
        ark->entries[i].block_offset = iohelper_read_u16_ve(file, isBigEndian);
        ark->entries[i].block = iohelper_read_u32_ve(file, isBigEndian);
        ark->entries[i].file_size = iohelper_read_u32_ve(file, isBigEndian);
        ark->entries[i].inflated_size = iohelper_read_u32_ve(file, isBigEndian);

        u64 pos = ftell(file); // past this point: fakeland (not in the entry itself)
        ark->entries[i].FAKEfile_offset = ark->entries[i].block * ark->header.block_size + ark->entries[i].block_offset;
        ark->entries[i].FAKEfile_name = iohelper_read_cstring_at(file, ark->entries[i].file_name_offset);
        fseek(file, ark->header.folder_entry_offset + (ark->entries[i].folder_name_index * 8) + 4, SEEK_SET);

        ark->entries[i].FAKEfolder_name_offset = iohelper_read_u32_ve(file, isBigEndian); 
        ark->entries[i].FAKEfolder_name = iohelper_read_cstring_at(file, ark->entries[i].FAKEfolder_name_offset);

        fseek(file, pos, SEEK_SET);
        printf("file %i registered: %s (size: %d offset: %d)\n", i, ark->entries[i].FAKEfile_name, ark->entries[i].file_size, ark->entries[i].FAKEfile_offset);
    }
    fseek(file, ark->header.folder_entry_offset, SEEK_SET);
    ark->folders = malloc(sizeof(HX_FREQARK_FOLDERENTRY) * ark->header.folder_entry_count);
    for (u32 i = 0; i < ark->header.folder_entry_count; i++) {

        ark->folders[i].unknown = iohelper_read_u32_ve(file, isBigEndian);
        ark->folders[i].folder_name_index = iohelper_read_u32_ve(file, isBigEndian);
        ark->folders[i].FAKEfolder_name = iohelper_read_cstring_at(file, ark->folders[i].folder_name_index);

        printf("folder %i registered: %s\n", i, ark->entries[i].FAKEfolder_name);
    }
    fseek(file, ark->header.string_table_offset, SEEK_SET);
    ark->entries = malloc(sizeof(char) * (ark->header.total_hdr_size - ark->header.string_table_offset));
    ark->string_table[0] = iohelper_read_cstring_at(file, ftell(file));
    return ark;
}

void hmx_freq_ark_cleanup(HX_FREQARK *ark) {
    if (ark == NULL) return;
    free(ark);
    return;
}

void hmx_freq_ark_print(HX_FREQARK *ark) {
    printf("header magic: %s\n", ark->header.magic);
    printf("version: %d\n", ark->header.version);
    printf("file entry table offset: 0x%X, size: %d\n", ark->header.file_entry_offset, ark->header.file_entry_count);
    printf("folder entry table offset: 0x%X, size including root: %d\n", ark->header.folder_entry_offset, ark->header.folder_entry_count);
    printf("string table? offset: 0x%X, size: %d\n", ark->header.string_table_offset, ark->header.string_count);
    printf("total header size: %d\n", ark->header.total_hdr_size);
    printf("block size: %d\n", ark->header.block_size);
    return;
}
