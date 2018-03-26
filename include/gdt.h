/*
 * Created by zxh on 2018/02/21 . All rights reserved.
 * 
 * Segmentation data structures and constants, reference XV6.
 */

#ifndef YEQU_INCLUDE_SYS_GDT_H
#define YEQU_INCLUDE_SYS_GDT_H

#include <types.h>

struct gdt_desc {
        uint32_t        limit_low       : 16;   /* low bits of segment limit */
        uint32_t        base_low        : 16;   /* low bits of segment base address */
        uint32_t        base_mid        : 8;    /* middle bits of segment base address */
        
        uint32_t        type            : 4;    /* segment type */
        uint32_t        s               : 1;    /* 0 = system, 1 = application */
        uint32_t        dpl             : 2;    /* descriptor privilige level */
        uint32_t        present         : 1;    /* present */

        uint32_t        limit_high      : 4;    /* high bits of segment limit */
        uint32_t        avl             : 1;    /* unused (available for software use) */
        uint32_t        r               : 1;    /* reserved */
        uint32_t        db              : 1;    /* 0 = 16-bit segment, 1 = 32-bit segment */
        uint32_t        g               : 1;    /* granularity: limit scaled by 4K when set */
        uint32_t        base_high       : 8;    /* high bits of segment base address */
} __attribute__((packed));

struct gdt_ptr {
        uint16_t        limit;
        uint32_t        base;
} __attribute__((packed));


/* application segment type bits */
#define STA_X           0x8     /* executable segment */
#define STA_E           0x4     /* expand down (non-executable segment) */
#define STA_C           0x4     /* conforming code segment (executable only) */
#define STA_W           0x2     /* writeable (non-executable segment) */
#define STA_R           0x2     /* readable (executable segment) */
#define STA_A           0x1     /* accessed */

/* system segment type bits */
#define STS_LDT         0x2     /* local descriptor table */
#define STS_TG          0x5     /* task gate / coum transmitions */
#define STS_TA          0x9     /* available 32-bit TSS */
#define STS_TB          0xB     /* busy 32-bit TSS */
#define STS_CG          0xC     /* 32-bit call gate */
#define STS_IS          0xE     /* 32-bit interrupt gate */
#define STS_TRG         0xF     /* 32-bit trap gate */

#define RING0           0
#define RING3           3

#define KERN_CS         (1 << 3)
#define KERN_DS         (2 << 3)
#define USER_CS         ((3 << 3) | 3)
#define USER_DS         ((4 << 3) | 3)


void gdt_init(void);

extern void gdt_flush(uint32_t);

#endif /* YEQU_INCLUDE_SYS_GDT_H */
