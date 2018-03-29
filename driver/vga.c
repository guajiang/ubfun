/*
 * Created by zxh on 2018/02/24 . All rights reserved.
 */

#include <vga.h>
#include <types.h>
#include <istr.h>

static int xpos = 0;                            /* save the X position */
static int ypos = 0;                            /* save the Y position */
static uint16_t *video = (uint16_t *)VIDEO;    /* point to the video memory */

/* move cursor position */
static void move_cursor()
{
	uint16_t pos = ypos * 80 + xpos;        /* 80 x 25 */

	outb(0x3D4, 14);
	outb(0x3D5, pos >> 8);                  /* send high 8-bits to port */
	outb(0x3D4, 15);
	outb(0x3D5, pos);                       /* low 8-bits */
}

/* screen scrolling */
static void scroll()
{
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);	// 0x20 is space

	if (ypos >= 25) {
		int i;
		for (i = 0 * 80; i < 24 * 80; i++)
			video[i] = video[i + 80];
		for (i = 24 * 80; i < 25 * 80; i++)
			video[i] = blank;
		ypos = 24;
	}
}

void cls()
{
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);

	int i;
	for (i = 0; i < 80 * 25; i++)
		video[i] = blank;

	xpos = 0;
	ypos = 0;
	move_cursor();
}

void putc_color(char c, color_t back, color_t fore)
{
	uint8_t back_color = (uint8_t)back;
	uint8_t fore_color = (uint8_t)fore;
	uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
	uint8_t attribute = attribute_byte << 8;

	if (c == 0x08 && xpos) {
		xpos--;
	} else if (c == 0x09) {
		xpos = (xpos + 8) & ~(8 - 1);
	} else if (c == '\r') {
		xpos = 0;
	} else if (c >= ' ') {
		video[ypos * 80 + xpos] = c | attribute;
		xpos++;
	}

	if (xpos >= 80) {
		xpos = 0;
		ypos++;
	}

	scroll();
}

void putc(int c)
{
	char ch = c & 0x0F;
	putc_color(ch, C_BLACK, C_WHITE);
}
