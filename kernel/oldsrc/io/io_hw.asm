section .text

; Input from port (32-bit)
; int inl(uint16_t port)
global inl
inl:
    push edx
    mov dx, word [esp+8] ; port is passed in stack
    in eax, dx           ; Read 4 bytes from port into EAX
    pop edx
    ret

; Output to port (32-bit)
; void outl(uint16_t port, uint32_t value)
global outl
outl:
    push edx
    push eax

    mov dx, word [esp+12] ; port is passed in stack
    mov eax, dword [esp+16] ; value is passed in stack

    out dx, eax           ; Write 4 bytes to port from EAX

    pop eax
    pop edx
    ret

; Input from port (8-bit)
; uint8_t inl(uint16_t port)
global inb
inb:
    push edx
    mov dx, word [esp+8] ; port is passed in stack

    xor eax, eax        ; Clear EAX
    in al, dx           ; Read 1 byte from port into AL
    pop edx
    ret

; Output to port (8-bit)
; void outl(uint16_t port, uint8_t value)
global outb
outb:
    push edx
    push eax

    xor eax, eax         ; Clear EAX
    mov dx, word [esp+12] ; port is passed in stack
    mov eax, dword [esp+16] ; value is passed in stack

    out dx, al           ; Write 1 byte to port from AL

    pop eax
    pop edx
    ret
