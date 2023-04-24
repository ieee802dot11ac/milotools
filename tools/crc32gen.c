#include <stdint.h>
#include <stdio.h>

typedef uint32_t u32;

int main(void)
{
	fputs("u32 simplepngCRCTable[256] = {\n\t", stdout);
	for (u32 i = 0; i < 256; ++i) {
		u32 crcValue = i;
		for (u32 iter = 0; iter < 8; ++iter) {
			crcValue = (crcValue >> 1) ^ (crcValue & 1 ? 0xedb88320 : 0);
		}
		printf("0x%08x, ", crcValue);
		if ((i + 1) % 8 == 0) {
			putchar('\n');
			if (i != 255)
				putchar('\t');
		}
	}
	puts("};");
}
