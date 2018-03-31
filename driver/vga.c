#include <vga.h>
#include <istr.h>
#include <string.h>

/* VGA start at 0xB8000 */
static uint16_t *video = (uint16_t *)0xB8000;

/* cursor position */
static uint8_t pos_x = 0;
static uint8_t pos_y = 0;

/* move cursor */
static void move_cursor()
{
	uint16_t pos = pos_y * 80 + pos_x;	/* screen width is 80 */
	
	outb(0x3D4, 14);
	outb(0x3D5, pos >> 8);		/* send high 8 bits to port */
	outb(0x3D4, 15);
	outb(0x3D5, pos);			/* send low 8 bits to port */
}

/* roll screen */
static void scroll()
{

	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);	/* attribute_byte background BLACK foreground WHITE */
	uint16_t blank = 0x20 | (attribute_byte << 8);	/* 0x20 is space */

	/* 
	 * while cursor y postion equal 25, than should get new line,
	 * copy all the data to previous, so clear the first row,
	 * and the last row fill space
	 */
	if (pos_y >= 25) {
		int i;
		for (i = 0 * 80; i < 24 * 80; i++) {
		      video[i] = video[i+80];
		}

		for (i = 24 * 80; i < 25 * 80; i++) {
		      video[i] = blank;
		}

		pos_y = 24;
	}
}

/* clear screen */
void vga_init()
{
	uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attribute_byte << 8);

	int i;
	for (i = 0; i < 80 * 25; i++) {
	      video[i] = blank;
	}

	pos_x = 0;
	pos_y = 0;
	move_cursor();
}

/* screen output a character C with backgroud BACK, foreground FORE */
void vga_putc_color(char c, vga_color_t back, vga_color_t fore)
{
	uint8_t back_color = (uint8_t)back;
	uint8_t fore_color = (uint8_t)fore;

	uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
	uint16_t attribute = attribute_byte << 8;

	if (c == 0x08 && pos_x) {	/* 0x08 is Backspace */
	      pos_x--;
	} else if (c == 0x09) {	/* 0x09 is Tab */
	      pos_x = (pos_x+8) & ~(8-1);
	} else if (c == '\r') {
	      pos_x = 0;
	} else if (c == '\n') {
		pos_x = 0;
		pos_y++;
	} else if (c >= ' ') {
		video[pos_y*80 + pos_x] = c | attribute;
		pos_x++;
	}

	if (pos_x >= 80) {		/* pos_x >= 80, should change the line */
		pos_x = 0;
		pos_y ++;
	}

	scroll();			/* screen roll */
	move_cursor();		/* move cursor */
}

void vga_putc(char c)
{
	vga_putc_color(c, VC_BLACK, VC_WHITE);
}

void vga_puts(char *cstr)
{
	while (*cstr)
	      vga_putc_color(*cstr++, VC_BLACK, VC_WHITE);
}


void vga_puts_color(char *cstr, vga_color_t back, vga_color_t fore)
{
	while (*cstr)
	      vga_putc_color(*cstr++, back, fore);
}
