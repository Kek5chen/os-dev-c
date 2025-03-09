#include "convert.h"
__attribute__((no_caller_saved_registers))
char *itoa(int n, char *str, int base) {
	char *digits = "0123456789ABCDEF";
	char *p = str;
	char *p1, *p2;
	int negative = 0;
	unsigned int n1 = n;
	if (n == 0) {
		str[0] = '0';
		str[1] = '\0';
		return str;
	}
	if (base == 10 && n < 0) {
		negative = 1;
		n1 = -n;
	}
	while (n1 > 0) {
		*p++ = digits[n1 % base];
		n1 /= base;
	}
	if (negative)
		*p++ = '-';
	*p = '\0';
	p1 = str;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
	return str;
}