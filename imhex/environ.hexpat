using Byte = u8;
struct LengthString {
    u32 length;
    char s[length];
};

struct Draw {
    u32 version;
    bool showing;
    u32 draw_count;
    LengthString draw_objects[draw_count];
    float bounding[4];
};

struct Lights {
    u32 lights_count;
    LengthString lights[lights_count];
};

struct EnvironmentData {
    u32 version;
    Draw draw;
    Lights lights;
    u8 ambient_color[4]; // could make it a struct but i'm lazy
    float ambient_alpha;
    float fog_start;
    float fog_end;
    // u32 ignore_num;
    u8 fog_color[4];
    float fog_alpha; // Guessing field name...
    bool fog_enable;
};

EnvironmentData envData @ 0x00;