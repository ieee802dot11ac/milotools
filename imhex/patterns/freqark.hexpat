struct HX_FREQARK_HEADER {
    // 40 bytes
    char magic[4]; // "ARK "
    u32 version; // Always 2
    u32 file_entry_offset; // Always 256
    u32 file_entry_count;
    u32 folder_entry_offset;
    u32 folder_entry_count;
    u32 string_table_offset;
    u32 string_count;
    u32 total_hdr_size; // Size of header + string offsets + string table
    u32 block_size; // Used for padding, always 2048?
};

struct HX_FREQARK_FILEENTRY {
    // 24 bytes
    u32 unknown; // Path name hash?
    u32 file_name_offset;
    u16 folder_name_index;
    u16 block_offset;
    u32 block; // Use block * block_size + block_offset to get file position
    u32 file_size;
    u32 inflated_size; // Same as file size if not compressed
    u32 file_offset = (block * 2048) + block_offset;
};
HX_FREQARK_HEADER hdr @ 0;
HX_FREQARK_FILEENTRY entries[hdr.file_entry_count] @ hdr.file_entry_offset;
for (s32 i = 0, i < hdr.file_entry_count, i=i+1) {
    u8 data[hdr.file_entry_count]/*;[entries[i].file_size]*/ @ entries[i].file_offset;
}