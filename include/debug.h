/*
 * Created by zxh on 2018/03/30 . All rights reserved.
 */

#ifndef YEQU_INCLUDE_DEBUG_H
#define YEQU_INCLUDE_DEBUG_H

#include <args.h>
#include <vga.h>

/* kernel print function */
void printk(const char *format, ...);

void printk_color(vga_color_t back, vga_color_t fore, const char *format, ...);

#endif	/* YEQU_INCLUDE_DEBUG_H */
