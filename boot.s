SETUPSEG	equ	0x9000
SETUPOFF	equ	0x0100
SETUPSIZE	equ	512
[bits 16]
[global start]
start:
	mov	si,	BOOTMSG
	call	print

load_setup:
	mov	ax,	SETUPSEG
	mov	es,	ax
	mov	bx,	SETUPOFF
	mov	ah,	2
	mov	dl,	0
	mov	ch,	0
	mov	cl,	2
	mov	al,	1
	int	0x13
	jc	load_setup
	jnc	ok_load_setup

ok_load_setup:
	mov	si,	OKLOAD
	call	print

	jmp	SETUPSEG: SETUPOFF

print:
	mov	ah,	0x0E
.next:
	lodsb
	or	al,	al
	jz	.done
	int	0x10
	jmp	.next
.done:
	ret

BOOTMSG:	db "boot..."
		db 13, 10, 0
OKLOAD:		db "  load setup ok"
		db 13, 10, 0


times	510-($-$$) db 0
	dw 0xAA55
