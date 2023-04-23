#include "milo_common.h"
#include "milo_string.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

MILO_STRING milo_string_load(FILE *file)
{
	u32 len;
	MILO_STRING ret;
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

void milo_string_print(MILO_STRING ref)
{
	putchar('"');
	for (u32 i = 0; i < ref.strLen; ++i)
		putchar(ref.refName[i]);
	putchar('"');
}
