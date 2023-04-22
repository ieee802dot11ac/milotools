#include "hmxcommon.h"
#include "hmxreference.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

HX_REFERENCE hmx_reference_load(FILE *file)
{
	u32 len;
	HX_REFERENCE ret;
	fread(&len, 4, 1, file);

	ret.strLen = len;
	ret.refName = malloc(ret.strLen);
	assert (ret.refName != NULL);

	if (len != 0) {
		for (u32 i = 0; i < len; i++)
			ret.refName[i] = fgetc(file);
	} else {
		ret.refName = (char*)"\0";
	}
	return ret;
}

void hmx_reference_print(HX_REFERENCE ref)
{
	putchar('"');
	for (u32 i = 0; i < ref.strLen; ++i)
		putchar(ref.refName[i]);
	putchar('"');
}
