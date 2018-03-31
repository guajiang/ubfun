/*
 * Created by zxh on 2018/02/24 . All rights reserved.
 * 
 * Some x86 instructions with C implementation.
 */

#ifndef YEQU_INCLUDE_ISTR_H
#define YEQU_INCLUDE_ISTR_H

#include <types.h>


static inline uint8_t inb(uint16_t port)
{
        uint8_t data;
        
        asm volatile("in %1, %0" : "=a" (data) : "d" (port));
        return data;
}

static inline void insl(int port, void *addr, int cnt)
{
        asm volatile("cld; rep insl" :
                        "=D" (addr), "=c" (cnt) :
                        "d" (port), "0" (addr), "1" (cnt) :
                        "memort", "cc");
}

static inline void outb(uint16_t port, uint8_t data)
{
        asm volatile("out %0, %1" : : "a" (data), "d" (port));
}

static inline void outw(uint16_t port, uint16_t data)
{
        asm volatile("out %0, %1" : : "a" (data), "d" (port));
}

static inline void outsl(int port, const void *addr, int cnt)
{
        asm volatile("cld; rep stosb" :
                        "=D" (addr), "=c" (cnt) :
                        "d" (port), "0" (addr), "1" (cnt) :
                        "cc");
}

static inline void stosb(void *addr, int data, int cnt)
{
        asm volatile("cld; rep stosb" :
                        "=D" (addr), "=c" (cnt) :
                        "0" (addr), "1" (cnt), "a" (data) :
                        "memory", "cc");
}

static inline void ltr(uint32_t n)
{
	asm volatile("ltr %%ax"::"a"(n));
}
#endif /* YEQU_INCLUDE_ISTR_H */
