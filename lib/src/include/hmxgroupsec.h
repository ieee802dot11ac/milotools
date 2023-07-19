// hmxgroupsec.h - List of faces (part?)
#ifndef HMXGROUPSEC_H
#define HMXGROUPSEC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "hmxcommon.h"

typedef struct {
	u32 faceCount;
	u32 vertexCount;
	u32 *faces;	// list of offsets from this.vertices,
	u16 *vertices;	// which represent *exclusive* end of
			// vertices in that face.
			// for example, faces = {3, 7, 10}
			// vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
			// actual faces are:
			// faces[0] =  3 => {0, 1, 2} (length of 3)
			// faces[1] =  7 => {3, 4, 5, 6} (length of 7-3=4)
			// faces[2] = 10 => {7, 8, 9} (length of 10-7=3)
			// notice how the length of each face entry
			// is the current value of faces[i], minus
			// the previous
} HX_GROUPSECTION;

void hmx_meshpart_print(HX_GROUPSECTION group);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
