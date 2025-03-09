OUTDIR := build
BOOTLOADER_DIR := boot
KERNEL_DIR := kernel
TARGET_NAME := "x86_64-unknown-none"
KERNEL_BUILD_OUT := target/$(TARGET_NAME)/release/kernel

NAME := osdev.bin

all: $(NAME)

$(NAME): bootloader kern
	# @cat $(OUTDIR)/boot.bin $(OUTDIR)/kernel.bin > $(OUTDIR)/os.bin
	ld -T linker.ld -o $(OUTDIR)/os.elf $(OUTDIR)/boot.o $(OUTDIR)/kernel.elf
	@objcopy -O binary $(OUTDIR)/os.elf $(OUTDIR)/os.bin




bootloader:
	@mkdir -p $(OUTDIR)
	nasm -f elf64 $(BOOTLOADER_DIR)/boot.asm -o $(OUTDIR)/boot.o
	@echo "Compiled boot.asm"
	@echo "Bootloader compiled successfully!"

kern:
	@cargo build -Z build-std=core --release --target x86_64-unknown-none
	@echo "Kernel compiled successfully"
	@rm -f $(OUTDIR)/kernel.elf
	@mv $(KERNEL_BUILD_OUT) $(OUTDIR)/kernel.elf

run:
	qemu-system-x86_64 -drive file=$(OUTDIR)/os.bin,format=raw

nix-run: $(NAME)
	nix-shell --run "make run"



clean:
	rm -rf target
	rm -rf $(KERNEL_DIR)/target
	rm -rf build



PHONY: bootloader kernel
NONPARELLEL: clean all
