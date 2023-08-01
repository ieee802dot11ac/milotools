#include "hmxcamera.h"
#include "hmxdraw.h"
#include "hmxprimitive.h"
#include "hmxstring.h"
#include "hmxtransform.h"
#include "iohelper.h"
#include <stdio.h>

HX_CAMERA hmx_camera_load(FILE *file) {
    HX_CAMERA camera;
    camera.version = iohelper_read_u32(file);
    camera.transform = hmx_transform_load(file);
    camera.draw = hmx_draw_load(file);
    camera.near_plane = iohelper_read_f32(file);
    camera.far_plane = iohelper_read_f32(file);
    camera.y_fov = iohelper_read_f32(file);
    camera.screen_rect = hmx_primitive_rect_load(file);
    fread(&camera.z_range, sizeof(Vector2f), 1, file);
    camera.target_tex = hmx_string_load(file);
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
