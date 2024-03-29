// hmxcamera.h - Harmonix cameras
#ifndef HMXCAMERA_H
#define HMXCAMERA_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "hmxmetadata.h"
#include "hmxtransform.h"
#include "hmxdraw.h"
#include "hmxstring.h"

typedef struct {
	u32 version; // 9 (GH1), 12 (GH2/GH2 360/TBRB)
	HX_METADATA *meta;
	HX_TRANSFORM transform;
	HX_DRAW draw; // <v10

	// The distance in world coordinates to the far clipping
	// plane. The near/far ratio is limited to 1:1000 to preserve
	// Z-buffer resolution. Note that on the PS2, object polys are
	// culled rather than clipped to the far plane.
	f32 near_plane;
	f32 far_plane;
	f32 y_fov;

	// The area of the screen in normalized coordinates
	// (0 to 1) to draw into.
	HX_RECT screen_rect;

	// The part of the Z-buffer to use, in normalized
	// coordinates. It can be useful to draw a scene where the near
	// and far planes must exceed the 1:1000 ratio (so multiple
	// cameras are used to draw farthest to nearest objects, each
	// using a closer range of the z-buffer) or to leave some
	// z-buffer for HUD overlay objects.
	Vector2f z_range;

	HX_STRING target_tex; // RndTex (not sure of exact field name)
} HX_CAMERA;


extern HX_CAMERA hmx_camera_load(FILE *file, bool isBigEndian);
extern void hmx_camera_cleanup(HX_CAMERA camera);
extern void hmx_camera_print(HX_CAMERA camera);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif
