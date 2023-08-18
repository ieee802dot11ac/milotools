// hmxchar.h: Harmonix's Character animation stuff
// https://github.com/PikminGuts92/re-notes/blob/master/templates/milo/char_bone.bt
#ifndef HMXCHAR_H
#define HMXCHAR_H
#ifdef __cplusplus
extern "C" {
#endif
#include "hmxtransform.h"
#include "hmxmetadata.h"
typedef enum {
    kRotNone = 9,
    kRotFull = 2,
    kRotX = 3,
    kRotY = 4,
    kRotZ = 5,
} ROTATION_ENUM;
typedef enum {
    kCompressNone = 0,
    kCompressRots = 1,
    kCompressVects = 2,
    kCompressQuats = 3
} CLIP_COMPRESSION; // CompressionType
typedef enum {
    kLODPerFrame = -1,
    kLOD0,
    kLOD1,
    kLOD2
} FORCE_LOD_ENUM;

typedef struct {
    
    u32 version; // 2 (GH2), 3 (GH2 360), 8 (TBRB)
    HX_METADATA *meta;
    HX_TRANSFORM *trans;
    

    // if (version < 7) {
        bool position; // Animate position or not
        bool scale;    // Animate scale or not
    // } else {
        u32 position_context;
        u32 scale_context;
    // }

    ROTATION_ENUM rotation; // What axis or axes to animate
    /*if (version < 5)*/ ROTATION_ENUM rotation2; // Not sure... ignored in later games

    /*if (version >= 3)*/ f32 unknown; // 1.0
} HX_CHARBONE;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
