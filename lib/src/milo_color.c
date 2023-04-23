#include "milo_color.h"


void milo_color_8888_print(MILO_COLOR_8888 color)
{
	color = milo_color_8888_fix_alpha(color);
	printf("MILOColor8888(%u, %u, %u, %u)", color.r,
					      color.g,
					      color.b,
					      color.a);
}
