{ pkgs ? import <nixos> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    llvmPackages.bintools
    rustup
    qemu
    gnumake
  ];
}
