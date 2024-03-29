// hmxdtx.h: a super rough and super lazy implementation of Harmonix's Data Array language and its serialized form
#ifndef HMXDTX_H
#define HMXDTX_H
#include "hmxstring.h"
#ifdef __cplusplus
extern "C" {
#endif

struct DtxNode;

typedef enum {
	kDataInt,
	kDataFloat,
	kDataVariable,
	kDataFunc,
	kDataObject,
	kDataSymbol,
	kDataUnhandled,
	kDataIfDef,
	kDataElse,
	kDataEndIf,
	kDataArray = 0x10,
	kDataCommand,
	kDataString,
	kDataProperty,
	kDataGlob,
	kDataDefine = 0x20,
	kDataInclude,
	kDataMerge,
	kDataIfNDef,
	kDataAutorun,
	kDataUndef
} DtxNodeType;

typedef struct {
	u16 size;
	u8* data;
} GLOB_DATA; // globs feel like a remnant of txt.bin

typedef struct
{
    u16 childCount;
    u32 id;
    struct DtxNode *children;
} DtxParent;

typedef struct DtxNode {
	DtxNodeType type;
	union {
		u32 value_int;
		float value_float;
		HX_STRING *value_str;
		DtxParent *value_parent;
		GLOB_DATA *value_glob;
	};
} DtxNode;

typedef struct {
	bool hasTree;
	DtxParent *root;
} HX_DTX; // if this is a .dtb, hasTree should *always* be true, for what should be an obvious reason

HX_DTX *hmx_dtx_load(FILE *file);
void hmx_dtx_print(HX_DTX *dtx);
void hmx_dtx_cleanup(HX_DTX *dtx);


#ifdef __cplusplus
}
#endif
#endif
