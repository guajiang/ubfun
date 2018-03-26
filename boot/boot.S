.set    BOOTSEG,        0x07C0          # boot sector will be load to 0x7c00 by BIOS
.set    SYSSEG,         0x1000          # system loaded at 0x10000
.set    SYSLEN,         32              # kernel sectors

.code16
.text
        .global _start
_start:
        ljmp    $BOOTSEG,       $go     # canonicalize %cs:%ip
go:
        movw    %cs,            %ax     # load segment registers
        movw    %ax,            %ds
        movw    %ax,            %ss
        movw    $0x7C00,        %sp     # set the stack pointer

# enable A20
seta20.1:
        inb     $0x64,          %al     # wait for not busy
        testb   $0x02,          %al
        jnz     seta20.1

        movb    $0xd1,          %al
        outb    %al,            $0x64

seta20.2:
        inb     $0x64,          %al
        test    $0x02,          %al
        jnz     seta20.2

        movb    $0xdf,          %al
        outb    %al,            $0x60

# read sector to es:bx(0x10000) by BIOS 'int 0x13'
load_system:                            
        movw    $0x0000,        %dx     
        movw    $0x0002,        %cx
        movw    $SYSSEG,        %ax
        movw    %ax,            %es
        xorw    %bx,            %bx
        movw    $0x200 + SYSLEN,%ax
        int     $0x13
        jnc     load_next
1:
        jmp     1b

# move kernel to address 0x00
load_next:
        cli                             # clear interrupt
        movw    $SYSSEG,        %ax
        movw    %ax,            %ds
        xorw    %ax,            %ax
        movw    %ax,            %es
        movw    $0x1000,        %cx
        sub     %si,            %si
        sub     %di,            %di
        rep     movsw                   # repeat move ds:si to es:di

        movw    $BOOTSEG,       %ax
        movw    %ax,            %ds
        lidt    idt_48                  # load idtr: 2 bytes table, 4 bytes address
        lgdt    gdt_48                  # load gdtr

        # enter protected mode
        movl    %cr0,           %eax
        orl     $0x01,          %eax
        movl    %eax,           %cr0

        ljmp    $0x08,          $0x00   # load eip=0, cs=8


gdt:
gdt_null:
        .word   0, 0, 0, 0
gdt_code:
        .word   0x07FF
        .word   0x0000
        .word   0x9A00
        .word   0x00C0
gdt_data:
        .word   0x07FF
        .word   0x0000
        .word   0x9200
        .word   0x00C0

idt_48:
        .word   0                       # idt limit = 0
        .word   0, 0                    # idt base = 0
gdt_48:
        .word   0x07FF                  # gdt limit = 2048, 256 gdt entries
        .word   0x7C00 + gdt,   0       # gdt base = 0x7xxx

        .org    510
        .word   0xAA55                  # boot sector flags
