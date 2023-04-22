// hmxtrans.h - Harmonix Transform structure and functions
#ifndef HMXTRANS_H
#define HMXTRANS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "hmxref.h"
#include "hmxenums.h"

typedef struct {
	u32 version; // should be 8
	float localTransMtx[12]; // local transformation matrix
	float worldTransMtx[12]; // world transformation matrix

	// i don't even know but trans so based
	u32 transCount;
	HX_EXTERNAL_REFERENCE* transObjects; // ????? completely optional but if it's there i don't want this thing choking and dying

	// parent mesh stuff
	CONSTRAINT_ENUM constraint;
	HX_EXTERNAL_REFERENCE target;
	bool preserveScale;
	HX_EXTERNAL_REFERENCE parent;
} HX_TRANS;


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
