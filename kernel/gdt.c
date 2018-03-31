/*
 * Created by zxh on 2018/02/22 . All rights reserved.
 */

#include <gdt.h>
#include <string.h>
#include <istr.h>

#define GDT_LENGTH      5

struct seg_desc gdt[GDT_LENGTH];
struct gdt_ptr gdtptr;

//struct tss_desc tss;


void set_seg(struct seg_desc *seg, uint32_t base, uint32_t limit, uint32_t dpl, uint32_t type)
{
	seg->limit_low  = ((limit) >> 12) && 0xffff;
	seg->base_low   = (base) & 0xffff;
	seg->base_mid   = ((base) >> 16) & 0xff;
	seg->type       = type;
	seg->s          = 1;
	seg->dpl        = dpl;
	seg->present    = 1;
	seg->limit_high = (uint32_t)((limit) >> 28);
	seg->avl        = 0;
	seg->r          = 0;
	seg->db         = 1;
	seg->g          = 1;
	seg->base_high  = (uint32_t)((base) >> 24);
}

void set_ldt(struct seg_desc *seg, uint32_t base)
{
	set_seg(seg, base, 0, 0, STS_LDT);
	seg->limit_low = 0x3;
	seg->s = 0;
}

void set_tss(struct seg_desc *seg, uint32_t base)
{
	set_seg(seg, base, 0, 0, STS_TA);
	seg->limit_low = 0x68;
	seg->s = 0;
}

void gdt_init(void)
{
	memset(gdt, 0, sizeof(gdt));
	/* gdt limit start at 0, so length -1 */
	gdtptr.limit = (sizeof(struct seg_desc) * GDT_LENGTH) - 1;
	gdtptr.base = (uint32_t)&gdt;

	set_seg(&gdt[0], 0, 0, 0, 0);
	set_seg(&gdt[1], 0, 0xffffffff, RING0, STA_X | STA_R);     /* code segment */
	set_seg(&gdt[2], 0, 0xffffffff, RING0, STA_W);             /* data segment */
	set_seg(&gdt[3], 0, 0xffffffff, RING3, STA_X | STA_R);     /* user mode code segment */
	set_seg(&gdt[4], 0, 0xffffffff, RING3, STA_W);             /* user mode data segment */

//	set_seg(&gdt[TSS0], (uint32_t)&tss);
	gdt_flush((uint32_t)&gdtptr);                           /* load gdt address to GDTR */
//	ltr(_TSS);
}
