ENTRY(_start)
SECTIONS {
    . = 1M; /* Put the OS at the 1 Megabyte mark in RAM */
    .text : { *(.multiboot) *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}
