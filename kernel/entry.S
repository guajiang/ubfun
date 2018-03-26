.global _start
.text
_start:
        movl    $0x10,  %eax    # privilige level '0', select 'GDT'
        movw    %ax,    %ds
        movw    %ax,    %es
        movw    %ax,    %fs
        movw    %ax,    %gs
        movl    $0x1000,%esp

# check A20
        xorl    %eax,   %eax
1:      incl    %eax
        movl    %eax,   0x000000
        cmpl    %eax,   0x100000
        je      1b

# call C init()
        call    init

spin:
        jmp     spin
