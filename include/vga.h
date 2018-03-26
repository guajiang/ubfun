/*
 * Created by zxh on 2018/02/24 . All rights reserved.
 */

#ifndef YRQU_INCLUDE_VGA_H
#define YEQU_INCLUDE_VGA_H

/* the video memory address */
#define VIDEO 0xB8000

//* The attribute of an character. */
#define ATTRIBUTE 7

void cls();
void putc(int c);

#endif /* YEQU_INCLUDE_VGA_H */
