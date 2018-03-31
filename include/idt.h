/*
 * Created by zxh on 2018/02/21 . All rights reserved.
 *
 * Interrupt Service Routine, and Interrupt Request routine
 */
#ifndef YEQU_INCLUDE_IDT_H
#define YEQU_INCLUDE_IDT_H

#include <types.h>


void idt_init();

/* Gate descriptor */
struct gate_desc {
	uint16_t base_low;
	uint16_t sel;
	uint8_t  always0;
	uint8_t  flags; 
	uint16_t base_high;
}__attribute__((packed));

// IDTR
struct idt_ptr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

/* protected registers */
struct pt_regs {
	uint32_t ds;			/* save user ds segment */
	uint32_t edi; 		/* instruction pusha, push sequence */
	uint32_t esi; 
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	uint32_t intr_no; 		/* interrupt code */
	uint32_t err_code;  		/* error code */
	uint32_t eip;			/* the fllowing is done by cpu */
	uint32_t cs; 		
	uint32_t eflags;
	uint32_t useresp;
	uint32_t ss;
};

/* interrupt handler pointer */
typedef void (*interrupt_handler_t)(struct pt_regs *);

/* register interrupt handler */
void register_interrupt_handler(uint8_t n, interrupt_handler_t h);

/* interrupt handler */
void isr_handler(struct pt_regs *regs);


/* interrupt handler 0 - 19 is part of CPU exception interrupt */
/* ISR: interrupt service routine */
				/* Exception Class. Description */
void isr0(); 			/* Fault. Divide Error Exception (#DE) */ 
void isr1(); 			/* Trap or Fault. Debug Exception (#DB) */ 
void isr2(); 			/* None. NMI Interrupt */ 
void isr3(); 			/* Trap. Breakpoint Exception (#BP) */ 
void isr4(); 			/* Trap. Overflow Exception (#OF) */ 
void isr5(); 			/* Fault. BOUND Range Exceeded Exception (#BR) */
void isr6(); 			/* Fault. Invalid Opcode Exception (#UD) */ 
void isr7(); 			/* Fault. Device Not Available Exception (#NM) */
void isr8(); 			/* Abort. Double Fault Exception (#DF) */
void isr9(); 			/* Abort. Coprocessor Segment Overrun */
void isr10(); 		/* Fault. Invalid TSS Exception (#TS) */
void isr11(); 		/* Fault. Segment Not Present (#NP) */
void isr12(); 		/* Fault. Stack Fault Exception (#SS) */
void isr13(); 		/* Fault. General Protection Exception (#GP) */
void isr14(); 		/* Fault. Page-Fault Exception (#PF) */
void isr15(); 		/* reserve */
void isr16(); 		/* Fault. FPU Floating-Point Error (#MF) */
void isr17(); 		/* Fault. Alignment Check Exception (#AC) */
void isr18(); 		/* Abort. Machine-Check Exception (#MC) */
void isr19(); 		/* Fault. SIMD Floating-Point Exception (#XM) */
void isr20(); 		/* Fault. Virtualization Exception (#VE) */

void isr21();			/* 21-31 Intel reserve */
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

void isr255();		/* 32-255 cUser Defined Interrupts */

/* IRQ Handler */
void irq_handler(struct pt_regs *regs);

/* IRQ, Intel 8259A */
#define  IRQ0     32 	// timer
#define  IRQ1     33 	// 键盘
#define  IRQ2     34 	// 与 IRQ9 相接，MPU-401 MD 使用
#define  IRQ3     35 	// 串口设备
#define  IRQ4     36 	// 串口设备
#define  IRQ5     37 	// 建议声卡使用
#define  IRQ6     38 	// 软驱传输控制使用
#define  IRQ7     39 	// 打印机传输控制使用
#define  IRQ8     40 	// 即时时钟
#define  IRQ9     41 	// 与 IRQ2 相接，可设定给其他硬件
#define  IRQ10    42 	// 建议网卡使用
#define  IRQ11    43 	// 建议 AGP 显卡使用
#define  IRQ12    44 	// 接 PS/2 鼠标，也可设定给其他硬件
#define  IRQ13    45 	// 协处理器使用
#define  IRQ14    46 	// IDE0 传输控制使用
#define  IRQ15    47 	// IDE1 传输控制使用

// 声明 IRQ 函数
// IRQ:中断请求(Interrupt Request)
void irq0();			// 电脑系统计时器
void irq1(); 			// 键盘
void irq2(); 			// 与 IRQ9 相接，MPU-401 MD 使用
void irq3(); 			// 串口设备
void irq4(); 			// 串口设备
void irq5(); 			// 建议声卡使用
void irq6(); 			// 软驱传输控制使用
void irq7(); 			// 打印机传输控制使用
void irq8(); 			// 即时时钟
void irq9(); 			// 与 IRQ2 相接，可设定给其他硬件
void irq10(); 		// 建议网卡使用
void irq11(); 		// 建议 AGP 显卡使用
void irq12(); 		// 接 PS/2 鼠标，也可设定给其他硬件
void irq13(); 		// 协处理器使用
void irq14(); 		// IDE0 传输控制使用
void irq15(); 		// IDE1 传输控制使用


#endif 	/* YEQU_INCLUDE_IDT_H */
