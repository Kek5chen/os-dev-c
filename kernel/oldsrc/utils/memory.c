#include "memory.h"

void memset(void *ptr, uint8_t value, int num) {
	uint8_t *p = (uint8_t *)ptr;
	for (int i = 0; i < num; i++) {
		p[i] = value;
	}
}