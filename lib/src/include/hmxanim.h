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

typedef enum {
    k30_fps,
    k480_fpb,
    k30_fps_ui,
    k1_fpb,
    k30_fps_tutorial
} RATE_ENUM; // what's an fpb? who knows, who cares

typedef struct {
	u32 version; // 0 (Amp/AntiGrav/GH1), 4 (GH2 4-song/GH2/GH2 360/RB1/TBRB/GDRB/DC2)
	u32 anim_entry_count;
	AnimEntry* anim_entries;
	u32 anim_count;
	HX_STRING* anim_objects;
} HX_ANIM;

extern HX_ANIM *hmx_anim_load(FILE *file);
extern void hmx_anim_cleanup(HX_ANIM *anim);
extern void hmx_anim_print(HX_ANIM *anim);


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
