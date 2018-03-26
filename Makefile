CC      = gcc
AS      = nasm
LD      = ld
V       = @
OBJDUMP = objdump
OBJCOPY = objcopy

CFLAGS  = -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -c -Wall -Werror -I./include
SFLAGS  = -f elf32 -g -F stabs
LDFLAGS = -m elf_i386 -N

QEMU    = qemu-system-i386
IMG     = yequ.img

OBJDIR  := obj

# find .c .S file to get .o file
KERN_C_SRCS     = $(wildcard kernel/*.c lib/*c driver/*c)
KERN_S_SRCS     = $(wildcard kernel/*.S)
KERN_OBJS       = $(patsubst %.S, $(OBJDIR)/%.o, $(KERN_S_SRCS))
KERN_OBJS       += $(patsubst %.c, $(OBJDIR)/%.o, $(KERN_C_SRCS))

$(IMG): bootblock kernelblock
	dd if=/dev/zero of=$(IMG) count=1000
	dd if=$(OBJDIR)/bootblock of=$(IMG) conv=notrunc
	dd if=$(OBJDIR)/kernelblock of=$(IMG) seek=1 conv=notrunc

bootblock: $(OBJDIR)/boot/boot.o
	$(V) $(OBJDUMP) -S $^ >$(OBJDIR)/bootblock.asm
	$(V) $(OBJCOPY) -S -O binary $^ $(OBJDIR)/bootblock

kernelblock: $(KERN_OBJS) tools/kernel.ld
	$(V) echo - ld $^
	$(V) $(LD) $(LDFLAGS) -e _start -Ttext 0x00 -o $(OBJDIR)/kernel/kernel.o $(KERN_OBJS)
	$(V) $(OBJDUMP) -S $(OBJDIR)/kernel/kernel.o >$(OBJDIR)/kernel.asm
	$(V) $(OBJCOPY) -S -O binary $(OBJDIR)/kernel/kernel.o $(OBJDIR)/kernelblock

$(OBJDIR)/boot/%.o: boot/%.S
	@mkdir -p $(OBJDIR)/boot
	$(V) @echo - as $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/kernel/%.o:kernel/%.c
	@mkdir -p $(OBJDIR)/kernel
	$(V) echo - cc $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/kernel/%.o:kernel/%.S
	@mkdir -p $(OBJDIR)/kernel
	$(V) echo - as $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/lib/%.o:lib/%.c
	@mkdir -p $(OBJDIR)/lib
	$(V) echo - cc $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/driver/%.o:driver/%.c
	@mkdir -p $(OBJDIR)/driver
	$(V) echo - cc $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

qemu: $(IMG)
	$(QEMU) -fda $< -serial mon:stdio

clean:
	rm -rf $(OBJDIR) os.img
