global load_idt
load_idt:
    lidt [esi]
    ret