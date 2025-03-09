#![no_std]
#![no_main]

use core::panic::PanicInfo;

bootloader_api::entry_point!(__kernel_entry);

fn __kernel_entry(_boot_info: &'static mut bootloader_api::BootInfo) -> ! {
    loop {}
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

