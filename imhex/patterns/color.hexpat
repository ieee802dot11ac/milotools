#include <std/io.pat>

bitfield HX_PALCOLOR_BPP4_RGBA {
	colorEvenX : 4;
	colorOddX : 4;
};

bitfield HX_PALCOLOR_BPP8_RGBA {
	color : 8;
};

struct HX_COLOR_8888 {
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} [[color(std::format("{:02X}{:02X}{:02X}", r, g, b))]];
