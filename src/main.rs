use std::process::Command;

fn main() {
    let bios_path = env!("BIOS_PATH");

    let mut cmd = Command::new("qemu-system-x86_64");
    cmd.arg("-drive").arg(format!("format=raw,file={bios_path}"));

    let mut proc = cmd.spawn().unwrap();
    proc.wait().unwrap();
}
