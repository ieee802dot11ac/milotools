struct IPUFrame {
    u8 flag;
};

struct IPUFile {
    char magic[4];
    u32 file_size;
    u16 size_x;
    u16 size_y;
    u32 frame_count;
    IPUFrame frames[frame_count];
};
IPUFile file @ 0x0;