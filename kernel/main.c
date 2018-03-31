/*
 * Created by zxh on 2018/03/29 . All rights reserved.
 */

#include <types.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <timer.h>
#include <debug.h>

void init()
{	
	int a = 10;
	char *buf = "printk\n";
	gdt_init();
	idt_init();
	vga_init();
	vga_puts("zxh\n");
	vga_puts("zsq\n");
	asm volatile ("int $0x13");
	vga_putc('a');
	printk("zxh is sb\n");
	printk_color(VC_WHITE, VC_RED,"a: %d, buf: %s", a, buf);
	asm volatile ("int $0x3");

	timer_init(200);
	while (1);
}
