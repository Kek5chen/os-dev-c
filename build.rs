use std::path::Path;

fn main() {
    let kernel_exec = std::env::var_os("CARGO_BIN_FILE_OSDEV_KERNEL_osdev-kernel")
        .unwrap()
        .into_string().
        unwrap();

    const out_path: &str = "build/os.bin";

    let bios_path = bootloader::BiosBoot::new(Path::new(&kernel_exec))
        .create_disk_image(Path::new(out_path))
        .unwrap();

    println!("cargo:rustc-env=BIOS_PATH={out_path}");
}
