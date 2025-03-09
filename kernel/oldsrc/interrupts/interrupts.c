#include "interrupts.h"

#include "memory.h"
#include "utils/convert.h"

static struct idt_entry g_idt[256];

static struct idt_ptr g_p_idt;

void idt_set_gate(uint8_t num, uintptr_t base, uint16_t selector, uint8_t flags) {
	g_idt[num].base_low = (base & 0xFFFF);
	g_idt[num].base_high = (base >> 16) & 0xFFFF;
	g_idt[num].selector = selector;
	g_idt[num].always0 = 0;
	g_idt[num].flags = flags;
}

void install_idt() {
	g_p_idt.limit = (sizeof(struct idt_entry) * 256) - 1;
	g_p_idt.base = (uintptr_t)&g_idt;

	memset(&g_idt, 0, sizeof(struct idt_entry) * 256);

	for (int i = 0; i < 256; ++i) {
		idt_set_gate(i, (uintptr_t) generic_handler, 0x08, 0x8E);
	}

	idt_set_gate(0, (uintptr_t) zero_division_handler, 0x08, 0x8E);
	idt_set_gate(1, (uintptr_t) debug_handler, 0x08, 0x8E);
	idt_set_gate(2, (uintptr_t) non_maskable_interrupt_handler, 0x08, 0x8E);
	idt_set_gate(3, (uintptr_t) breakpoint_handler, 0x08, 0x8E);
	idt_set_gate(4, (uintptr_t) overflow_handler, 0x08, 0x8E);
	idt_set_gate(24, (uintptr_t) critical_handler, 0x08, 0x8E);

	load_idt(&g_p_idt);
	//asm volatile("lidt %0" : : "m"(idtp));
}

__attribute__((interrupt)) void zero_division_handler(void *frame) {
	kernel_panic("Zero Division Error");
}

__attribute__((interrupt)) void debug_handler(void *frame) {
	kernel_panic("Debug Handler");
}

__attribute__((interrupt)) void non_maskable_interrupt_handler(void *frame) {
	kernel_panic("Non Maskable Interrupt Handler");
}

__attribute__((interrupt)) void breakpoint_handler(void *frame) {
	kernel_panic("Breakpoint Handler");
}

__attribute__((interrupt)) void overflow_handler(void *frame) {
	kernel_panic("Overflow Handler");
}

__attribute__((interrupt)) void critical_handler(void *frame) {
	kernel_panic("Critical Handler");
}

__attribute__((interrupt)) void generic_handler(void *frame) {
	char str[60] = "A generic error has occurred with error code: 0x";
	itoa(((struct interrupt_frame*) frame)->err_code, str + 45, 16);
	kernel_panic("A generic error occurred");
}

