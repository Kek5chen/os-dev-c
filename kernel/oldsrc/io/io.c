#include "io.h"

static char kbd_US[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', /* <-- Tab */
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, /* <-- control key */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
	'*',
	0,  /* Alt */
	' ',  /* Space bar */
	0,  /* Caps lock */
	0,  /* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,  /* < ... F10 */
	0,  /* 69 - Num lock*/
	0,  /* Scroll Lock */
	0,  /* Home key */
	0,  /* Up Arrow */
	0,  /* Page Up */
	'-',
	0,  /* Left Arrow */
	0,
	0,  /* Right Arrow */
	'+',
	0,  /* 79 - End key*/
	0,  /* Down Arrow */
	0,  /* Page Down */
	0,  /* Insert Key */
	0,  /* Delete Key */
	0,   0,   0,
	0,  /* F11 Key */
	0,  /* F12 Key */
	0,  /* All other keys are undefined */
};

uint8_t to_scancode(char c)
{
	for (int i = 0; i < 128; i++)
		if (kbd_US[i] == c)
			return i;
	return 0;
}

char scancode_to_keycode(unsigned char scancode)
{
	if (scancode >= 128)
		return 0;
	return kbd_US[scancode];
}

uint8_t read_character() {
	// Check if the keyboard has sent data (by checking bit 0 of port 0x64)
	while ((inl(0x64) & 0x1) == 0);

	// Read scan code from keyboard data port (0x60)
	return inl(0x60);
}

uint8_t read_character_async() {
	if ((inb(0x64) & 0x1) == 0) return 0;
	return inb(0x60);
}