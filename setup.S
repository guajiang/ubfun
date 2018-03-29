SETUPSEG	= 0x9010
SETUPLEN	= 512
SYSSEG		= 0x0000
SYSSIZE		= 1024 * 36

.code16
setup:
	ljmp	$SETUPSEG, $go
go:
	movw	%cs,	%ax
	movw	%ax,	%ds
	movw	%ax,	%es
	movw	%ax,	%ss
	movw	$0xff00,%sp

	movw	$MSG,	%si
	call	print

read_system:
	movw	$0x9000,%ax
	movw	%ax,	%ds
	movb	$0x88,	%ah
	int	$0x15
	movw	%ax,	memret

	movw	%cs,	%ax
	movw	%ax,	%ds
	movw	%ax,	%es
	movw	%ax,	%ss
	movw	$0xff00,%sp

	movw	$SETUPSEG,	%ax
	movw	%ax,	%es
	movw	$SETUPLEN,	%bx
	movb	$2,	%ah
	movb	$0,	%dl
	movb	$0,	%ch
	movb	$3,	%cl
	movb	$SYSSIZE/512,	%al
read_system:
	int	$0x13
	dec	al
	jnz	read_system

	cld
	movw	$SETUPLEN,%si
	movw	$SYSSEG,%ax
	movw	%ax,	%es
	subw	%di,	%di
	movw	$SYSSIZE,	%cx
	rep	movsd

	clid
	lgdt	gdt_addr

	call	empty_8042
	movb	$0xd1,	%al
	outb	%al,	$0x64
	call	empty_8042
	movb	$0xdf,	%al
	outb	$al,	$0x60
	call	empty_8042

	movl	%cr0,	%eax
	orl	$1,	%eax
	movl	%eax,	%cr0

	ljmp	$0x08,	$0

empty_8042:
	inb	$0x64,	5al
	testb	$0x2,	%al
	jnz	empty_8042
	ret

print:
	movb	$0x0E,	%ah
.next:
	lodsb
	orb	%al,	%al
	jz	.done
	int	$0x10
	jmp	.next
.done:
	ret

MSG:
	.ascii	"setup..."

gdt_addr:
gdt_null:
	.word	0x0000
	.word	0x0000
	.word	0x0000
	.word	0x0000
gdt_code:
	.word	0x3fff
	.word	0x0000
	.word	0x9a00
	.word	0x00c0
gdt_data:
	.word	0x3fff
	.word	0x0000
	.word	0x9200
	.word	0x00c0

	.org	512
