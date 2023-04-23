#include "hmxcolor.h"


void hmx_color_8888_print(HX_COLOR_8888 color)
{
	color = hmx_color_8888_fix_alpha(color);
	printf("HXColor8888(%u, %u, %u, %u)", color.r,
					      color.g,
					      color.b,
					      color.a);
}
