ODIR = obj
BDIR = bin
NAME = $(BDIR)/kxos.iso

WD = $(shell pwd)
REMOTE_SERVER_IP =

KERNEL_DIR = kernel
KERNEL_SRC = $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_OBJ = $(patsubst %.c, $(ODIR)/%.o, $(KERNEL_SRC))

all: $(NAME)

$(NAME): kernel boot/boot.asm boot/mode_switch.asm boot/gdt.asm
# SETUP
	mkdir -p $(BDIR)
	mkdir -p $(ODIR)
# ASSEMBLE
	nasm -f bin boot/boot.asm -o $(ODIR)/boot.bin
# APPEND
	cat $(ODIR)/kernel.bin >> $(ODIR)/boot.bin
# COPY TO ISO FILE
	truncate $(ODIR)/boot.bin -s 1200k
	genisoimage -o $(NAME) -input-charset iso8859-1 -b $(ODIR)/boot.bin .

kernel: $(KERNEL_OBJ)

$(ODIR)/$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	mkdir -p $(ODIR)/$(KERNEL_DIR)
	gcc -ffreestanding -c $< -o $@ -m32 -fno-pie
# LINK
	ld -o $(ODIR)/kernel.bin -Ttext 0x7e00 $(KERNEL_OBJ) --oformat binary -m elf_i386

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(BDIR)

run: $(NAME)
	qemu-system-x86_64.exe -hda $(ODIR)/boot.bin

upload:
	rsync -avz -e 'ssh' $(WD) $(REMOTE_SERVER_IP):/tmp
	ssh $(REMOTE_SERVER_IP) "cd /tmp/KXOS && make fclean && make"
	rsync -avz -e 'ssh' $(REMOTE_SERVER_IP):/tmp/KXOS/obj $(WD)
	rsync -avz -e 'ssh' $(REMOTE_SERVER_IP):/tmp/KXOS/bin $(WD)

.PHONY: all clean run kernel