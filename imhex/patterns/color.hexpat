#pragma once
#include <std/io.pat>

bitfield HX_PALCOLOR_BPP4_RGBA {
	colorEvenX : 4;
	colorOddX : 4;
} [[static]];

bitfield HX_PALCOLOR_BPP8_RGBA {
	color : 8;
} [[static]];

struct HX_COLOR_8888 {
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} [[static, color(std::format("{:02X}{:02X}{:02X}", r, g, b))]];

struct HX_COLOR_3F {
	float r,g,b;
} [[static, color(std::format("{:02X}{:02X}{:02X}", r, g, b))]];

struct HX_COLOR_4F {
	float r,g,b,a;
	u32 cr = r * 255;
	u32 cg = g * 255;
	u32 cb = b * 255;
} [[static, color(std::format("{:02X}{:02X}{:02X}", cr, cg, cb))]];
