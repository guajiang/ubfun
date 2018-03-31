; Load GDTR
[global gdt_flush]
gdt_flush:
	mov	eax,	[esp + 4]	; parameter -> eax
	lgdt	[eax]

	mov	ax,	0x10
	mov	ds,	ax
	mov	es,	ax
	mov	fs,	ax
	mov	gs,	ax
	mov	ss,	ax
	jmp	0x08:_flush
_flush:
	ret


; Load IDTR
[global idt_flush]
idt_flush:
	mov	eax,	[esp + 4]	; parameter -> eax
	lidt	[eax]
	ret

; Interrupt without error code
%macro ISR_NOERRCODE 1
[global isr%1]
isr%1:
	cli
	push	0
	push	%1
	jmp	isr_common_stub
%endmacro

; Interrupt with error code
%macro ISR_ERRCODE 1
[global isr%1]
isr%1:
	cli
	push	%1
	jmp	isr_common_stub
%endmacro

; Interrupt error code
ISR_NOERRCODE	0
ISR_NOERRCODE	1
ISR_NOERRCODE	2
ISR_NOERRCODE	3
ISR_NOERRCODE	4
ISR_NOERRCODE	5
ISR_NOERRCODE	6
ISR_NOERRCODE	7
ISR_ERRCODE	8
ISR_NOERRCODE	9
ISR_ERRCODE	10
ISR_ERRCODE	11
ISR_ERRCODE	12
ISR_ERRCODE	13
ISR_ERRCODE	14
ISR_NOERRCODE	15
ISR_NOERRCODE	16
ISR_ERRCODE	17
ISR_NOERRCODE	18
ISR_NOERRCODE	19
ISR_NOERRCODE	20

ISR_NOERRCODE	21
ISR_NOERRCODE	22
ISR_NOERRCODE	23
ISR_NOERRCODE	24
ISR_NOERRCODE	25
ISR_NOERRCODE	26
ISR_NOERRCODE	27
ISR_NOERRCODE	28
ISR_NOERRCODE	29
ISR_NOERRCODE	30
ISR_NOERRCODE	31

ISR_NOERRCODE	255

[global isr_common_stub]
[extern isr_handler]
isr_common_stub:
	pusha	; edi, esi, ebp, esp, ebx, edx, ecx, eax
	mov	ax,	ds
	push	eax		; sava ds

	mov	ax,	0x10	; load system data segment
	mov	ds,	ax
	mov	es,	ax
	mov	fs,	ax
	mov	gs,	ax
	mov	ss,	ax

	push	esp		; pt_regs pointer
	call	isr_handler
	add	esp,	4

	pop	ebx		; recover data segment
	mov	ds,	bx
	mov	es,	bx
	mov	fs,	bx
	mov	gs,	bx
	mov	ss,	bx

	popa
	add	esp,	8	; clean error code and isr
	iret


; IRQ macro
%macro IRQ 2
[GLOBAL irq%1]
irq%1:
	cli
	push 0
	push %2
	jmp irq_common_stub
%endmacro

IRQ   0,    32 	; 电脑系统计时器
IRQ   1,    33 	; 键盘
IRQ   2,    34 	; 与 IRQ9 相接，MPU-401 MD 使用
IRQ   3,    35 	; 串口设备
IRQ   4,    36 	; 串口设备
IRQ   5,    37 	; 建议声卡使用
IRQ   6,    38 	; 软驱传输控制使用
IRQ   7,    39 	; 打印机传输控制使用
IRQ   8,    40 	; 即时时钟
IRQ   9,    41 	; 与 IRQ2 相接，可设定给其他硬件
IRQ  10,    42 	; 建议网卡使用
IRQ  11,    43 	; 建议 AGP 显卡使用
IRQ  12,    44 	; 接 PS/2 鼠标，也可设定给其他硬件
IRQ  13,    45 	; 协处理器使用
IRQ  14,    46 	; IDE0 传输控制使用
IRQ  15,    47 	; IDE1 传输控制使用

[GLOBAL irq_common_stub]
[EXTERN irq_handler]
irq_common_stub:
	pusha				; pushes edi, esi, ebp, esp, ebx, edx, ecx, eax
	
	mov ax, ds
	push eax			; sava user data segment
	
	mov ax, 0x10			; load system data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	push esp
	call irq_handler
	add esp, 4
	
	pop ebx			; recover data segment
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx
	mov ss, bx
	
	popa				; Pops edi,esi,ebp...
	add esp, 8			; clean up error code and ISR code
	iret				; pop CS, EIP, EFLAGS, SS, ESP
