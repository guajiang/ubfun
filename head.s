extern init
[bits 32]
	mov	esp,	stack_top
	mov	ax,	0x10
	mov	ds,	ax
	mov	cl,	'2'
	mov	[0xb8000],	cl
	mov	cl,	0x04
	mov	[0xb8001],	cl

	xor	eax,	eax
check_A20:
	inc	eax
	mov	[0x000000],	eax
	cmp	[0x100000],	eax
	je	check_A20

	push	esp
	call	init

section .bss
	resb	8192
stack_top:
