#include "hmxcommon.h"
#include "hmxstring.h"
#include "iohelper.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HX_STRING hmx_string_load(FILE *file)
{
	u32 len;
	HX_STRING string;
	len = iohelper_read_u32(file);

	string.length = len;

	if (len != 0) {
		string.value = malloc(string.length);
		assert (string.value != NULL);
		assert(fread(string.value, 1, len, file) == len);
	} else {
		string.value = NULL;
	}

	return string;
}

char *hmx_string_cstring(HX_STRING string)
{
	char *const str = malloc(string.length + 1);
	str[string.length] = 0;
	memcpy(str, string.value, string.length);
	return str;
}

void hmx_string_cleanup(HX_STRING string)
{
	// if the length is 0, the value is NULL, so DO NOT FREE.
	if (string.length != 0)
		free(string.value);
}

void hmx_string_print(HX_STRING string)
{
	putchar('"');
	for (u32 i = 0; i < string.length; ++i)
		putchar(string.value[i]);
	putchar('"');
}
