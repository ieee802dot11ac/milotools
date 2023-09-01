// hmxaudio.h - Harmonix's stuff for VAG (laugh) audio, e.g. .vgs and .nse
#ifndef HMXAUDIO_H
#define HMXAUDIO_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"

#define MAX_CHANNELS 15
#define VAG_BYTES_PER_BLOCK 16
#define VAG_SAMPLES_PER_BLOCK 28

typedef struct {
    u32 data[VAG_BYTES_PER_BLOCK];
} Block;

typedef struct {
    float pos; // pos = calculate_position_vag(sample_rate, i);
    Block* blocks; // as many blocks as there are channels, so usually like 4
} InterleavedBlock;

typedef struct {
    u32 sample_rate;
    u32 block_count;
} StreamInfo;

typedef struct {
    u32 sample_rate; // always 48k
    float len;
} VAGStream;

typedef struct {
    char magic[4]; // VgS!
    int version; // 2 (GH1/GH2), 4 (RB1)
    
    StreamInfo channel_info[MAX_CHANNELS];

    VAGStream stream;
} VgsFile;

INLINE float calculate_position_vag(u32 sample_rate, u32 i)
{
    return (float)(i * VAG_SAMPLES_PER_BLOCK) / (float)sample_rate;
}
// todo: implement this https://github.com/nothings/stb/blob/master/stb_vorbis.c

#ifdef __cplusplus
}
#endif
#endif
