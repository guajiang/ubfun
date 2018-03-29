SETUPSEG	equ	0x9000
SETUPOFF	equ	0x0100
SETUPSIZE	equ	512
SYSSEG		equ	0x0000
SYSOFF		equ	0x0000
SYSSIZE		equ	1024 * 36

align 4
[bits 16]
[global setup]
setup:
	mov	ax,	SETUPSEG
	mov	ds,	ax
	mov	es,	ax
	mov	ss,	ax
	mov	sp,	0xffff
	
	mov	si,	SETUPMSG
	call	print

read_info:
	mov	ax,	0x9000
	mov	ds,	ax
	; geet memory size and save in 0x90002
	mov	ah,	0x88
	int	0x15
	mov	[2],	ax


load_system:
	mov	ax,	SETUPSEG
	mov	es,	ax
	mov	bx, 	SETUPOFF+SETUPSIZE	; kernel load address
	mov	ah,	2
	mov	dl,	0
	mov	ch,	0
	mov	cl,	3	; sector start at 1, boot(1),setup(2),kernel(3..)
	mov	al,	SYSSIZE/512
rp_load:
	int	0x13
	dec	al
	jnz	rp_load

move_system:
	cld
	mov	si,	SETUPOFF+SETUPSIZE
	mov	ax,	SYSSEG
	mov	es,	ax
	mov	di,	SYSOFF
	mov	cx,	SYSSIZE
	rep
	movsd

	cli
	lgdt	[gdt_addr]
	call	empty_8042
	mov	al,	0xd1
	out	0x64,	al
	call	empty_8042
	mov	al,	0xdf
	out	0x60,	al
	call	empty_8042

	; enter protectd-mode
	mov	eax,	cr0
	or	eax,	eax
	mov	cr0,	eax

	jmp	dword	0x8:0x0

empty_8042:
	in	al,	0x64
	test	al,	0x2
	jnz	empty_8042
	ret

print:
	mov	ah,	0x0E
.next:
	lodsb
	or	al,	al
	jnz	.done
	int	0x10
	jmp	.next
.done:
	ret

SETUPMSG:	db "setup..."
		db 13, 0, 0
	
gdt_addr:
	dw	0x7fff
	dw	gdt,	0x9
gdt:
gdt_null:
	dw	0x0000
	dw	0x0000
	dw	0x0000
	dw	0x0000
gdt_code:
	dw	0x3fff
	dw	0x0000
	dw	0x9a00
	dw	0x00c0
gdt_data:
	dw	0x3fff
	dw	0x0000
	dw	0x9200
	dw	0x00c0

	times	512-($-$$) db 0
