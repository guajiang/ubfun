/*
 * Created by zxh on 2018/03/30 . All rights reserved.
 */

#include <timer.h>
#include <idt.h>
#include <istr.h>
#include <debug.h>

void timer_callback(struct pt_regs *regs)
{
	static uint32_t tick = 0;
	printk_color(VC_BLACK, VC_RED, "Tick: %d\n", tick++);
}

void timer_init(uint32_t frequency)
{
	register_interrupt_handler(IRQ0, timer_callback);
	
	uint32_t divisor = 1193180 / frequency;
	outb(0x43, 0x36);

	uint8_t low = (int8_t)(divisor & 0xFF);
	uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);
	outb(0x40, low);
	outb(0x40, high);
}
