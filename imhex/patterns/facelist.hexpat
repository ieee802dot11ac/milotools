#pragma once

struct HX_FACE_LIST {
	u32 faceCount;
	u32 vertexCount;
	u32 faces[faceCount];		// list of offsets from this.vertices,
	u16 vertices[vertexCount];	// which represent *exclusive* end of
					// vertices in that face.
	// for example, faces = {3, 7, 10}
	// vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	// actual faces are:
	// faces[0] =  3 => {0, 1, 2} (length of 3, start is vertices[0])
	// faces[1] =  7 => {3, 4, 5, 6} (length of 7-3=4, start is vertices[3])
	// faces[2] = 10 => {7, 8, 9} (length of 10-7=3, start is vertices[7])
	// notice how the length of each actual face entry is:
	// realFace[i].length = faces[i] - (i == 0 ? 0 : faces[i - 1])
	// and how the start of each face entry is the previous value:
	// realFace[i].start = &vertices[i == 0 ? 0 : faces[i - 1]]
	// or simplified:
	// prevFaceValue = (i == 0 ? 0 : faces[i - 1])
	// realFace[i].length = faces[i] - prevFaceValue
	// realFace[i].start = &vertices[prevFaceValue];
}
