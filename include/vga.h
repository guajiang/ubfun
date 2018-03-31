/*
 * Created by zxh on 2018/02/24 . All rights reserved.
 */

#ifndef INCLUDE_VGA_H
#define INCLUDE_VGA_H

#include <types.h>

/* color */
typedef
enum vga_color {
	VC_BLACK = 0,
	VC_BLUE = 1,
	VC_GREEN = 2,
	VC_RED = 4,
	VC_WHITE = 15
} vga_color_t;

/* clear screen */
void vga_init();

/* screen put a character */
void vga_putc(char c);

/* screen put a character with color */
void vga_putc_color(char c, vga_color_t back, vga_color_t fore);

/* screen put a string with terminated '\0' */
void vga_puts(char *cstr);

/* screen put a string with terminated '\0' and color */
void vga_puts_color(char *cstr, vga_color_t back, vga_color_t fore);

#endif /* YEQU_INCLUDE_VGA_H */
