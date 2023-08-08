#include "hmxcamera.h"
#include "hmxdraw.h"
#include "hmxprimitive.h"
#include "hmxstring.h"
#include "hmxtransform.h"
#include "hmxvector.h"
#include "iohelper.h"
#include <stdio.h>

HX_CAMERA hmx_camera_load(FILE *file, bool isBigEndian) {
    HX_CAMERA camera;
    camera.version = iohelper_read_u32_ve(file, isBigEndian);
    camera.transform = hmx_transform_load(file, isBigEndian);
    camera.draw = hmx_draw_load(file, isBigEndian);
    camera.near_plane = iohelper_read_f32_ve(file, isBigEndian);
    camera.far_plane = iohelper_read_f32_ve(file, isBigEndian);
    camera.y_fov = iohelper_read_f32_ve(file, isBigEndian);
    camera.screen_rect = hmx_primitive_rect_load(file, isBigEndian);
    camera.z_range = hmx_vec2f_load(file, isBigEndian);
    camera.target_tex = hmx_string_load(file, isBigEndian);
    return camera;
}

void hmx_camera_cleanup(HX_CAMERA camera)
{
	hmx_transform_cleanup(camera.transform);
	hmx_draw_cleanup(camera.draw);
	hmx_string_cleanup(camera.target_tex);
}

void hmx_camera_print(HX_CAMERA camera)
{
    printf("VERSION: %i\n", camera.version);
    printf("BEGIN TRANSFORM\n"); hmx_transform_print(camera.transform); printf("END TRANSFORM\n");
    printf("BEGIN DRAW\n"); hmx_draw_print(camera.draw); printf("\nEND DRAW\n");
    printf("NEAR PLANE: %f\n", camera.near_plane);
    printf("FAR PLANE: %f\n", camera.far_plane);
    printf("Y FOV: %f\n", camera.y_fov);
    printf("SCREEN RECT: "); hmx_primitive_rect_print(camera.screen_rect);
    printf("\nZ RANGE: %f %f\n", camera.z_range.x, camera.z_range.y);
    printf("TARGET TEX: "); hmx_string_print(camera.target_tex);
    printf("\n");
}
