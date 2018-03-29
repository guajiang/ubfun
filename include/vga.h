/*
 * Created by zxh on 2018/02/24 . All rights reserved.
 */

#ifndef YRQU_INCLUDE_VGA_H
#define YEQU_INCLUDE_VGA_H

/* the video memory address */
#define VIDEO 0xB8000

//* The attribute of an character. */
#define ATTRIBUTE 7

/* color */
typedef enum color {
	C_BLACK = 0,
	C_BLUE = 1,
	C_GREEN = 2,
	C_CYAN = 3,
	C_RED = 4,
	C_MAGENTA = 5,
	C_BROWN = 6,
	C_LIGHT_GREY = 7,
	C_DARK_GREY = 8,
	C_LIGHT_BLUE = 9,
	C_LIGHT_GREEN = 10,
	C_LIGHT_CYAN = 11,
	C_LIGHT_RED = 12,
	C_LIGHT_MAGENTA = 13,
	C_LIGHt_BROWN = 14,
	C_WHITE = 15
} color_t;

void cls();
void putc(int c);

#endif /* YEQU_INCLUDE_VGA_H */
