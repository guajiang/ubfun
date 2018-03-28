[bits 16]

;;; [0x7c00] will be seted in boot.ld
[global start]
start:
	;; puts loading
	mov si, msg
	call print

	;; read the setup code from floppy
	;; begin with second, read setup to 0x90100
.readfloppy:
	mov ax, setupseg
	mov es, ax
	mov bx, setupoffset
	mov ah, 2
	mov dl, [bootdriver]
	mov ch, 0
	mov cl, 2
	mov al, setupsize/512
	int 0x13		;interupt to read
	jc  .readfloppy

	;; ok, let finish boot and jump to setup
	;; jmp setupseg:setupoffset

read_info:
	mov ax, 0x9000
	mov ds, ax

	;; Now get memory size and save at 0x90002
	;; This may just report up to 64M.
	;; It only reports contiguous (usable) RAM.
	mov ah, 0x88
	int 0x15
	mov [2], ax

	mov ax, setupseg
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0xffff

	mov ax, setupseg
	mov es, ax
	mov bx, setupoffset+setupsize ; put kernel at here now
	mov ah, 2
	mov dl, [0]
	mov ch, 0
	;0,1 is for boot, setupsize/512 for setup.bin
	mov cl, 3
	mov al, systemsize/512
.readfloppy1:
	int 0x13
    dec al
	jnz .readfloppy1

jmp setupseg:setupoffset

print:
	mov ah, 0x0E
.next:
	lodsb
	or al, al
	jz .done
	int 0x10 		;interupt to print
	jmp .next
.done:
	ret

msg	db "Loading Panda OS"	;
	db 13, 10, 0  		;

;;; some constants

setupseg 	equ 0x9000    	;setup address
setupoffset     equ 0x0100	;
setupsize 	equ 512
systemseg       equ     0x0000
systemoffset	equ 	0x0000
systemsize      equ 	1024*36
bootdriver 	db  0
; Magic number for sector
times 510-($-$$) db 0
dw 0xAA55
