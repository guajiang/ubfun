/*
 * Created by zxh on 2018/03/30 . All rights reserved.
 * 
 * Interrupt handle 
 */

#include <types.h>
#include <string.h>
#include <debug.h>
#include <idt.h>
#include <istr.h>

struct gate_desc idt[256];	/* idt */
struct idt_ptr idtptr;	/* idtr */

/* interrupt handler pointer array */
interrupt_handler_t interrupt_handlers[256];

/* set idt gate */
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

/* load idtr */
extern void idt_flush(uint32_t);

const char *exception_msg[32] = {
	"Divide Error Exception",
	"Debug Exception"
};


/* initialize idt */
void idt_init()
{	
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	// 设置主片 IRQ 从 0x20(32) 号中断开始
	outb(0x21, 0x20);

	// 设置从片 IRQ 从 0x28(40) 号中断开始
	outb(0xA1, 0x28);
	
	// 设置主片 IR2 引脚连接从片
	outb(0x21, 0x04);

	// 告诉从片输出引脚和主片 IR2 号相连
	outb(0xA1, 0x02);
	
	// 设置主片和从片按照 8086 的方式工作
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	
	// 设置主从片允许中断
	outb(0x21, 0x0);
	outb(0xA1, 0x0);


	memset((uint8_t *)&interrupt_handlers, 0, sizeof(interrupt_handler_t) * 256);	
	idtptr.limit = sizeof(struct gate_desc) * 256 - 1;
	idtptr.base  = (uint32_t)&idt;
	memset((uint8_t *)&idt, 0, sizeof(struct gate_desc) * 256);

	/* CPU interrupt 0 - 31 */
	idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

	/* 255 will implement system call */
	idt_set_gate(255, (uint32_t)isr255, 0x08, 0x8E);

	/* load idt */
	idt_flush((uint32_t)&idtptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt[num].base_low = base & 0xFFFF;
	idt[num].base_high = (base >> 16) & 0xFFFF;
	idt[num].sel     = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}

/* register interrupt handler */
void register_interrupt_handler(uint8_t n, interrupt_handler_t h)
{
	interrupt_handlers[n] = h;
}

/* call interrupt handle function */
void isr_handler(struct pt_regs *regs)
{
	if (interrupt_handlers[regs->intr_no]) {
		printk_color(VC_BLACK, VC_BLUE, "Interrup: %d, %s\n", regs->intr_no, exception_msg[regs->intr_no]);
		interrupt_handlers[regs->intr_no](regs);
	} else {
		printk_color(VC_BLACK, VC_RED, "Unhandled interrupt: %d\n", regs->intr_no);
	}
}

void irq_handler(struct pt_regs *regs)
{
	if (regs->intr_no >= 40)
		outb(0xA0, 0xA0);
	outb(0x20, 0x20);

	if (interrupt_handlers[regs->intr_no])
		interrupt_handlers[regs->intr_no](regs);
}