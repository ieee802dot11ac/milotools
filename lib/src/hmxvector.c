#include "hmxvector.h"
#include "iohelper.h"

Vector2f hmx_vec2f_load(FILE *const file, bool isBigEndian)
{
	Vector2f vec;
	vec.x = iohelper_read_f32_ve(file, isBigEndian);
	vec.y = iohelper_read_f32_ve(file, isBigEndian);
	return vec;
}

Vector3f hmx_vec3f_load(FILE *const file, bool isBigEndian)
{
	Vector3f vec;
	vec.x = iohelper_read_f32_ve(file, isBigEndian);
	vec.y = iohelper_read_f32_ve(file, isBigEndian);
	vec.z = iohelper_read_f32_ve(file, isBigEndian);
	return vec;
}
Vector4f hmx_vec4f_load(FILE *const file, bool isBigEndian)
{
	Vector4f vec;
	vec.x = iohelper_read_f32_ve(file, isBigEndian);
	vec.y = iohelper_read_f32_ve(file, isBigEndian);
	vec.z = iohelper_read_f32_ve(file, isBigEndian);
	vec.w = iohelper_read_f32_ve(file, isBigEndian);
	return vec;
}
bool hmx_vec2f_write(FILE *const file, Vector2f vec, bool isBigEndian)
{
	iohelper_write_f32_ve(file, vec.x, isBigEndian);
	iohelper_write_f32_ve(file, vec.y, isBigEndian);
	return true; // oh no
}
bool hmx_vec3f_write(FILE *const file, Vector3f vec, bool isBigEndian)
{
	iohelper_write_f32_ve(file, vec.x, isBigEndian);
	iohelper_write_f32_ve(file, vec.y, isBigEndian);
	iohelper_write_f32_ve(file, vec.z, isBigEndian);
	return true; // oh no
}
bool hmx_vec4f_write(FILE *const file, Vector4f vec, bool isBigEndian)
{
	iohelper_write_f32_ve(file, vec.x, isBigEndian);
	iohelper_write_f32_ve(file, vec.y, isBigEndian);
	iohelper_write_f32_ve(file, vec.z, isBigEndian);
	iohelper_write_f32_ve(file, vec.w, isBigEndian);
	return true; // oh no
}
