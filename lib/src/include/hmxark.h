// hmxark.h: Harmonix .ark archives (used to work around iso-9660 limits)
#ifndef HMXARK_H
#define HMXARK_H
#ifdef __cplusplus
extern C {
#endif

#include "hmxcommon.h"

typedef struct {
    // 40 bytes
    char magic[4]; // "ARK\x00"
    u32 version; // Always 2
    u32 file_entry_offset; // Always 256
    u32 file_entry_count;
    u32 folder_entry_offset;
    u32 folder_entry_count;
    u32 string_table_offset;
    u32 string_count;
    u32 total_hdr_size; // Size of header + string offsets + string table
    u32 block_size; // Used for padding, always 2048?
} HX_FREQARK_HEADER;

typedef struct
{
    // 24 bytes
    u32 unknown; // Path name hash?
    u32 file_name_offset;
    u16 folder_name_index;
    u16 block_offset;
    u32 block; // Use block * block_size + block_offset to get file position
    u32 file_size;
    u32 inflated_size; // Same as file size if not compressed

    u32 FAKEfile_offset;// = (block * parentof(this).header.block_size) + block_offset;
    char *FAKEfile_name; // = ReadString(file_name_offset);

    u32 FAKEfolder_name_offset;// = ReadUInt(parentof(this).header.folder_entry_offset + (folder_name_index * 8) + 4);
    char *FAKEfolder_name;// = ReadString(folder_name_offset);
} HX_FREQARK_FILEENTRY;

typedef struct
{
    // 8 bytes
    u32 unknown; // Name hash?
    u32 folder_name_index;

    char *FAKEfolder_name;// = ReadString(folder_name_index);
} HX_FREQARK_FOLDERENTRY;

typedef struct {
    HX_FREQARK_HEADER header;
    HX_FREQARK_FILEENTRY *entries;
    HX_FREQARK_FOLDERENTRY *folders;
    char *string_table[]; // cisco doesn't seem to implement it as an array but to be fair 010 is a stupid language
} HX_FREQARK;

HX_FREQARK *hmx_freq_ark_load(FILE *file, char const *outdir, bool isBigEndian);
void hmx_freq_ark_cleanup(HX_FREQARK *ark);
void hmx_freq_ark_print(HX_FREQARK *ark);

#ifdef __cplusplus
}
#endif
#endif
