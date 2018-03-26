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
//static void scroll()
//{
//        if (ypos >= 25) {
//                int i;
//                /* first row will disappear */
//                for (i = 0 * 80; i < 24 * 80; i++)
//                        video[i] = video[i + 80];
//                /*last row fill SPACE */
//                for (i = 24 * 80; i < 25 * 80; i++)
//                       video[i] = 0x00;
 //       }
//}

/* clear screen */
void cls()
{
        int i;

        for (i = 0; i < 80 * 25; i++)
                video[i] = 0;

        xpos = 0;
        ypos = 0;
        move_cursor();
}

void putc(int c)
{
        int pos;

       if (c == '\n' || c == '\r') {
newline:
               xpos = 0;
               ypos = 0;
               if (ypos >= 24)
                       ypos = 0;
               return ;
       }

       pos = xpos + ypos * 80;
       *(video + pos * 2) = c & 0xFF;
       *(video + pos * 2 + 1) = ATTRIBUTE;
        
       xpos++;
       if (xpos >= 80)
               goto newline;
}
