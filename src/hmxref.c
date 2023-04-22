#include "common.h"
#include "hmxref.h"
#include <stdio.h>
#include <stdlib.h>

HX_EXTERNAL_REFERENCE extref_from_file(FILE *file)
{
	u32 len;
	HX_EXTERNAL_REFERENCE ret;
	ret.refName = malloc(69);
	fread(&len, 4, 1, file);
	ret.strLen = len;
	if (len != 0) {
		for (u32 i = 0; i < len; i++)
			ret.refName[i] = fgetc(file);
	} else {
		ret.refName = (char*)"\0";
	}
	return ret;
}
