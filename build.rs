use std::path::Path;

fn main() {
    let kernel_exec = std::env::var_os("CARGO_BIN_FILE_MY_KERNEL_osdev-kernel").;

    bootloader::BiosBoot::new(Path::new(&kernel_exec))
        .create_disk_image(Path::new("build/os.bin"))
        .unwrap();
}
