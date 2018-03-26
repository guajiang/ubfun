.global gdt_flush
gdt_flush:
        movl    4(%esp),%eax    # get first argument, gdtptr (see driver/gdt.c)
        lgdt    (%eax)          # load gdt descriptor

        movw    $0x10,  %ax     # 0x10 is offset in the GDT
        mov     %ax,    %ds
        mov     %ax,    %es
        mov     %ax,    %fs
        mov     %ax,    %gs
        mov     %ax,    %ss
        #ljmp    $0x08,  $_flush  # set %cs to 0x08

_flush:
        ret
