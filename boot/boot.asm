;============================================================
; KXOS BOOTLOADER - 0.1
; Mainly made for the KXOS project by KX
;============================================================

[bits 16]								; boot into 16 bit real-mode.
[org 0x7c00]

jmp start								; jump to start

;============================================================
; VALUE STORAGE
;============================================================
; PRESET VALUES
bytesPerSector	equ	512		 			; bytes per sector

; RUNTIME VALUES
bDriveNum		db	0xFF	  			; drive number

;===========================================================



;============================================================
; FUNCTION: setup
; 16 bit real mode only - only run right after startup
;============================================================
setup:
	pusha
	mov [bDriveNum], dl						; store drive number in bDriveNum
											; Set background and foreground colour
	mov ah, 0x06							; Clear / scroll screen up function
	xor al, al								; Number of lines by which to scroll up (00h = clear entire window)
	mov bh, 0x30							; Background/foreground colour. (https://en.wikipedia.org/wiki/BIOS_color_attributes)
	xor cx, cx								; Row,column of window's upper left corner
	mov dx, 0x184f							; Row,column of window's lower right corner
	int 0x10								; Issue BIOS video services interrupt with function 0x06
											; Set cursor position to 0,0
	mov ah, 0x02							; Set cursor position function
	mov bh, 0x00							; Page number (00h = active page)
	mov dh, 0x00							; Row number (00h = top row)
	mov dl, 0x00							; Column number (00h = leftmost column)
	int 0x10								; Issue BIOS video services interrupt with function 0x02
	popa
	ret
;============================================================



;============================================================
; FUNCTION: print_char
; Prints a string to the screen.
; 16 bit real mode only.
; al: character to print
;============================================================
print_char:
	push ax									; save ah
	mov	ah, 0x0e							; set ah to 0x0e
	int	0x10								; print al to screen
	pop ax									; restore ah
	ret										; return
;============================================================



;============================================================
; FUNCTION: print_string
; Prints a string to the screen.
; 16 bit real mode only.
; si: string to print
;============================================================
print_string:
	push si									; save si
	push ax
	mov	ah, 0x0e							; set ah to 0x0e
	print_string_loop:
		lodsb								; load byte from si into al
		cmp	al, 0							; check if al is 0
		je	print_string_end				; if al is 0, jump to printStringEnd
		int	0x10							; print al to screen
		jmp	print_string_loop				; loop
	print_string_end:
		pop ax
		pop	si								; restore si
		ret									; return
;============================================================



;============================================================
; FUNCTION: read_sector
; 16 bit real-mode only
; al: sectors to read
; ch: from cylinder
; cl: from sector
; dh: from head
; dl: from drive
; es:bx: to buffer address pointer
;============================================================
read_sector:
	mov ah, 0x02
	int 0x13
	ret
;============================================================



;============================================================
; FUNCTION: load_kernel
; 16 bit real-mode only
;============================================================
load_kernel:
	pusha
	mov al, 1							; one sector
	mov ch, 0							; first cylinder
	mov cl, 2							; second sector
	mov dh, 0							; head to start reading from
	mov dl, [bDriveNum]					; drive to start reading from
	mov bx, 0x200						; buffer = 0x7c0 * 0x10 + 0x200 = right after boot sector
	call read_sector
	jnc no_error
	mov si, msg_load_failure
	call print_string
	no_error:
		popa
		ret
;============================================================



;============================================================
; FUNCTION: start
; 16 bit real-mode only.
;============================================================
start:
	cli									; disable interrupts
										; set up registers
	xor ax, ax							; set ax to 0x7c0
	mov ds, ax							; set default data segment to ax
	mov es, ax							; set extra segment to ax
	mov fs, ax							; set extra segment to ax
	mov gs, ax							; set stack segment to ax
	mov ss, ax							; set stack segment to 0x0000
	mov	bp, 0xFFFF						; set stack pointer to 0xFFFF
	mov sp, bp
	sti									; enable interrupts since we're done with setup
	call setup
	mov si, msg_booting					; set si to msg_setup
	call print_string					; print "Booting KXOS..."
	mov si, msg_kernel					; set si to msg_kernel
	call print_string					; print "Loading kernel..."
	call load_kernel
	mov si, load_success
	call print_string
	mov si, msg_politics
	call print_string
	call switch_to_64bit
	jmp $
;============================================================


;============================================================
; FUNCTION: BEGIN_PM
[bits 64]
;============================================================
BEGIN_PM:
	mov rax, 0x4100000000000000
	shr rax, 54
	mov byte [0xb8000], al
	jmp $								; infinite loop ( jump to current location )

;============================================================
[bits 16]
;===========================================================
%include "boot/mode_switch.asm"
;===========================================================

;============================================================
; MESSAGES
;============================================================
msg_booting:
	db "Booting KXOS...", 0x0D, 0x0A, 0x00
msg_setup:
	db "Setting up registers...", 0x0D, 0x0A, 0x00
msg_kernel:
	db "Loading kernel...", 0x0D, 0x0A, 0x00
msg_politics:
	db "Making computers great again!!!!!", 0x0D, 0x0A, 0x00
msg_load_failure:
	db "Error: Loading Sector failed.", 0x0D, 0x0A, 0x00

;============================================================
; END OF CODE
;============================================================

times 510-($-$$) db 0
dw 0xAA55
load_success:
	db "Loaded successfully!", 0x0D, 0x0A, 0x00
times 512*2-($-$$) db 0