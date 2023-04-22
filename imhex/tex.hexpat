struct ExternalRef {
    u32 StrLen;
    char RefName[StrLen];
};

struct TexHeader {
    u32 eight [[name("ID Byte")]];
    u32 width [[name("Width")]];
    u32 height [[name("Height")]];
    u32 bpp [[name("Bits per pixel")]];
    ExternalRef texpath [[name("Filename")]];

    float huh;
    u32 always1;
    bool externalTex [[name("Is External Ref")]];
};

struct BmpHeader {
    u8 always1;
    u8 bpp2;
    u32 imgfmt [[comment("should be 3")]];
    padding[1];
    u16 width;
    u16 height;
    u16 bytesperline;
    padding[19];
};

struct TexFile {
    TexHeader header;
    if (header.externalTex == false) {
        BmpHeader bitmapHdr;
    }
};
TexFile texfile @ 0x00;
