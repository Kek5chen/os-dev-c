#pragma once
#include <stdint.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);

uint32_t inl(uint16_t port);
void outl(uint16_t port, uint32_t value);

uint8_t	read_character();
uint8_t	read_character_async();
uint8_t	to_scancode(char c);
char	scancode_to_keycode(uint8_t scancode);
