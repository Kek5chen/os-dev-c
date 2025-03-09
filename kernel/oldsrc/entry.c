#include "io/io.h"
#include "utils/virtprint.h"
#include "utils/strings.h"
#include "interrupts/interrupts.h"

__attribute__((section(".text.kernel_entry")))
int	_start(void)
{
	clear_screen();
	char *str = "Welcome to KXOS";
	print_string(str, 0x0A, MAKE_XY(40 - strlen(str) / 2, 12));

	print_string("Scancode: ", 0x0A, MAKE_XY(34, 14));
	print_string("Keycode: ", 0x0A, MAKE_XY(34, 15));
	print_string("Character:", 0x0A, MAKE_XY(34, 16));
	print_number(0, 0x0A, MAKE_XY(45, 14));
	print_number(0, 0x0A, MAKE_XY(45, 15));
	print_character(' ', 0x0A, MAKE_XY(45, 16));
	print_string("a: load custom IDT", 0x0A, MAKE_XY(5, 3));
	print_string("b: trigger interrupt", 0x0A, MAKE_XY(5, 4));
	while (1) {
		uint8_t read = read_character_async();
		if (read == 0)
			continue;

		if (read >= 128)
			continue;

		char keycode = scancode_to_keycode(read);
		if (keycode == 'a') {
			install_idt();
			print_string("Interrupt Table loaded!", 0x0A, MAKE_XY(4, 22));
		}
		if (keycode == 'b') {
			asm volatile("int $0x0");
		}
		print_string("   ", 0x0A, MAKE_XY(45, 14));
		print_string("   ", 0x0A, MAKE_XY(45, 15));
		print_character(' ', 0x0A, MAKE_XY(45, 16));
		print_number(read, 0x0A, MAKE_XY(45, 14));
		print_number(keycode, 0x0A, MAKE_XY(45, 15));
		print_character(keycode, 0x0A, MAKE_XY(45, 16));
	}
	return 0xABC;
}