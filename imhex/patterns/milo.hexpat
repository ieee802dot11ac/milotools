struct MiloFile {
    u32 magic;
    u32 offset;
    s32 blockCount;
    s32 maxBlockSize;
    u32 sizes[blockCount];
    u8 block[sizes[0]] @ offset;
};

MiloFile file @ 0;
