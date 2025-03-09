#pragma once

#define	PTR_VMB	0xB8000									// Video Memory Base
#define MAKE_XY(x, y) ((uint32_t)((y) * 80 + (x)))		// Make XY coordinate

typedef struct __attribute__((packed)) telechar_s
{
	char c;
	unsigned char a;
} telechar_t;

typedef uint32_t telepostype_t;

__attribute__((no_caller_saved_registers))
void clear_screen();
__attribute__((no_caller_saved_registers))
void print_character(char c, uint8_t color, telepostype_t pos);
__attribute__((no_caller_saved_registers))
void print_string(const char *s, uint8_t color, telepostype_t pos);
__attribute__((no_caller_saved_registers))
void print_number(int n, uint8_t color, telepostype_t pos);
