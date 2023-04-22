#include "hmxref.h"
#include <stdio.h>

HX_EXTERNAL_REFERENCE extref_from_file(FILE *file)
{
	uint32_t len;
	HX_EXTERNAL_REFERENCE ret;
	fread(&len, 4, 1, file);
	ret.strLen = len;
	if (len == 0) {
		ret.refName = (char*)"\0";
	} else {
		for (uint32_t i = 0; i < len; i++)
			ret.refName[i] = fgetc(file);
	}
	return ret;
}
