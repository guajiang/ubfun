SETUPSEG	= 0x9000
SETUPOFF	= 0x0100
SETUPLEN	= 1

.code16
.global start
start:
	movw	$MSG,	%si
	call	print

load_setup:
	movw	$0x0000,	%dx
	movw	$0x0002,	%cx
	movw	$SETUPSEG,	%ax
	movw	%ax,		%es
	movw	$0x0200,	%bx
	movb	$2,		%ah
	movb	$1,		%al
	int	$13
	jc	load_setup


	ljmp	$SETUPSEG, $SETUPOFF

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
	.ascii	"Load setup"

driver:
	.word	0

	.org	510
	.word	0xAA55
