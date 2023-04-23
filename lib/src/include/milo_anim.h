// hmxanim.h - Harmonix animatable base class
#ifndef HMXANIM_H
#define HMXANIM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"
#include "hmxstring.h"

typedef struct {
    HX_STRING name;
    float f1;
    float f2;
} AnimEntry;

typedef struct {
    u32 version; // should be 0 (?!?!?!)
    u32 anim_entry_count;
    AnimEntry* anim_entries;
    u32 anim_count;
    HX_STRING* anim_objects;
} HX_ANIM;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
