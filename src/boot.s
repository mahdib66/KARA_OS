; boot.s - Multiboot Header and Entry Point
MBOOT_PAGE_ALIGN    equ 1<<0
MBOOT_MEM_INFO      equ 1<<1
MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

section .multiboot
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_HEADER_FLAGS
    dd MBOOT_CHECKSUM

section .text
global _start
extern kernel_main

_start:
    ; Set up a stack for C code
    mov esp, stack_space
    
    ; Push nothing for now, just jump to C
    call kernel_main
    
    ; If kernel returns, halt the CPU
    cli
.halt:
    hlt
    jmp .halt

section .bss
resb 8192 ; 8KB for the stack
stack_space:
