// hmxmilo.h - Harmonix milo "scene"s
#ifndef HMXMILO_H
#define HMXMILO_H
#include "hmxenviron.h"
#include "hmxtexture.h"
#include "hmxtransform.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "hmx.h"

typedef struct {
	char* class_name;
	char* name;
	union {
		HX_CAMERA camera;
		HX_ENVIRON environment;
		HX_MATERIAL material;
		HX_MESH mesh;
		HX_TEXTURE texture;
		HX_TRANSFORM transform;
	}; // if you run into more, god help you
} HX_MILOOBJECT;

typedef struct {
	HX_STRING type;
	HX_STRING name;

	u32 offset;
	u32 size;
} HX_MILOENTRY;

typedef struct {
	i32 entry_count;
	HX_MILOENTRY* entries;
} HX_MILOENTRIES;

typedef struct {
	i32 ext_count;
	HX_STRING* ext_paths;
} HX_EXTERNALRESOURCES;

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
