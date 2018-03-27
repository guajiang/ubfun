
// @Name   : main.c
//
// @Author : Yukang Chen (moorekang@gmail.com)
// @Date   : 2012-01-03 17:33:50
//
// @Brief  : The kernel main entry point

#include <asm.h>
#include <screen.h>
#include <string.h>
#include <mm.h>
#include <hd.h>
#include <task.h>
#include <time.h>
#include <file.h>
#include <sysfile.h>
#include <exec.h>
#include <syscall.h>

u32 init_esp_start;
s32 init = 0;


void kmain(u32 init_stack) {
    //init_esp_start = init_stack;
    init_video();
    //puts_color_str("Booting Panda OS ...\n hello world", 0x0B);

    cli();

    //gdt_init();
    //idt_init();

        puts_color_str("hello world ...\n", 0x0B);


}


