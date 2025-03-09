#include <stdint.h>
#include "virtprint.h"

__attribute__((no_caller_saved_registers))
void clear_screen()
{
	telechar_t *p = (telechar_t *)PTR_VMB;
	for(int i = 0; i < MAKE_XY(80, 24); i++) {
		p[i].c = 0;
		p[i].a = 0;
	}
}

__attribute__((no_caller_saved_registers))
void print_character(char c, uint8_t color, telepostype_t pos)
{
	telechar_t *p = (telechar_t *)PTR_VMB + pos;
	p->c = c;
	p->a = color;
}

__attribute__((no_caller_saved_registers))
void print_string(const char *s, uint8_t color, telepostype_t pos)
{
	while (*s)
	{
		print_character(*s, color, pos);
		s++;
		pos++;
	}
}

// Function to recursively print the digits
__attribute__((no_caller_saved_registers))
static telepostype_t print_number_recursive(int num, uint8_t color, telepostype_t pos) {
	if (num == 0) return pos;

	pos = print_number_recursive(num / 10, color, pos);
	print_character((num % 10) + '0', color, pos);
	return pos + 1;
}

__attribute__((no_caller_saved_registers))
void print_number(int n, uint8_t color, telepostype_t pos)
{
	if (n < 0) {
		print_character('-', color, pos);
		n = -n;
		pos++;
	}
	if (n == 0) {
		print_character('0', color, pos);
		return;
	}

	print_number_recursive(n, color, pos);
}