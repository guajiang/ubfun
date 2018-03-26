OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS {
    .text 0x00 : 
    {
        code = .; _code = .; __code = .;
        *(.text);
        . = ALIGN(0x1000);	
    }
    .data : 
    {
        data = .; _data = .; __data = .;
        *(.rodata);
        *(.data);
        . = ALIGN(0x1000);	
    }

    .bss :
    {
        __bss__ = .;
        *(.bss);
        . = ALIGN(0x1000);
    }

    __kimg_end__ = .;
}
