# 🌌 Kara OS (v0.1)

Kara OS is a custom x86 operating system built from scratch. It currently features a basic kernel, a VGA text-mode driver, and a functional AZERTY keyboard driver with a built-in shell.

## 🚀 Features
* **Custom Bootloader**: Uses GRUB to boot via Multiboot.
* **Kernel**: Written in C and Assembly.
* **VGA Driver**: Support for 80x25 text mode display.
* **Keyboard Driver**: Fully mapped for **AZERTY** layout.
* **Shell**: Basic command-line interface.

## 🛠️ Prerequisites
To build and run Kara OS, you need the following tools:
* `gcc` (Cross-compiler recommended)
* `nasm`
* `make`
* `grub-mkrescue`
* `xorriso` (for ISO creation)
* `qemu-system-i386` (to run the OS)

## 🏗️ How to Build
Clone the repo and run the Makefile:

```bash
# Clone the repository
git clone [https://github.com/mahdib66/KARA_OS.git](https://github.com/mahdib66/KARA_OS.git)
cd KARA_OS

# Build the ISO
make
