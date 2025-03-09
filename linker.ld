ENTRY(_start)

SECTIONS
{
    . = 0x7C00; /* Bootloader starts at 0x7C00 */

    .boot :
    {
        *(.boot)
    }

    . = 0x7e00; /* Kernel starts at 0x7e00 */

    .text :
    {
        *(.text.__kernel_entry)
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    /DISCARD/ :
    {
        *(.comment)
    }
}
