#include <stdint-gcc.h>
#include "strings.h"

uint32_t strlen(char *string) {
	int i = 0;
	for (; string[i]; i++);
	return i;
}
