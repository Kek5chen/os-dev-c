#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

fn __kernel_entry(boot_info: &'static mut bootloader_api::BootInfo) -> ! {
    let wew: &str = "meow this is some real bs because that's how it be uwu :3";
    let uwu: u64 = wew.as_ptr() as u64;
    unsafe {
        *(0x1000 as *mut u64) = uwu;
    }

    loop {}
}

bootloader_api::entry_point!(__kernel_entry);
