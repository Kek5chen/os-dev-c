#pragma once

#include <stdint.h>

struct idt_entry {
	unsigned short base_low;
	unsigned short selector;
	unsigned char always0;
	unsigned char flags;
	unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

void load_idt(struct idt_ptr *idt);

void idt_set_gate(uint8_t num, uintptr_t base, uint16_t selector, uint8_t flags);
void install_idt();

_Noreturn __attribute__((no_caller_saved_registers))
void system_halt();
__attribute__((no_caller_saved_registers))
void kernel_panic(const char *message);

struct interrupt_frame {
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Pushed by pusha.
	uint32_t ds, es, fs, gs;                          // Pushed the segs last.
	uint32_t int_no, err_code;                        // Our 'push byte #' and ecodes do this.
	uint32_t eip, cs, eflags, useresp, ss;            // Pushed by the processor automatically.
} __attribute__((packed));

typedef void (__attribute__((interrupt)) irq_handler_func_t) (void *frame);

irq_handler_func_t zero_division_handler;
irq_handler_func_t debug_handler;
irq_handler_func_t non_maskable_interrupt_handler;
irq_handler_func_t breakpoint_handler;
irq_handler_func_t overflow_handler;
irq_handler_func_t critical_handler;
irq_handler_func_t generic_handler;
