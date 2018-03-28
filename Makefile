CC      = gcc
AS      = nasm
LD      = ld
V       = @
OBJDUMP = objdump
OBJCOPY = objcopy

CFLAGS  = -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -c -Wall -Werror -I./inc
SFLAGS  = -f elf32 -g -F stabs
LDFLAGS = -m elf_i386 -N

QEMU    = qemu-system-i386
IMG     = yequ.img

OBJDIR  := obj

# find .c .s file to get .o file
KERN_C_SRCS     = $(wildcard core/*.c lib/*c driver/*c)
KERN_S_SRCS     = $(wildcard core/*.s)
KERN_OBJS       = $(patsubst %.s, $(OBJDIR)/%.o, $(KERN_S_SRCS))
KERN_OBJS       += $(patsubst %.c, $(OBJDIR)/%.o, $(KERN_C_SRCS))

all: $(OBJDIR)/bootblock $(OBJDIR)/coreblock

$(OBJDIR)/bootblock: $(OBJDIR)/boot/boot.o $(OBJDIR)/boot/setup.o
	$(V) echo - ld $^
	$(V) $(LD) $(LDFLAGS) -T tool/boot.ld -o $(OBJDIR)/boot/boot.elf $(OBJDIR)/boot/boot.o
	$(V) $(LD) $(LDFLAGS) -T tool/setup.ld -o $(OBJDIR)/boot/setup.elf $(OBJDIR)/boot/setup.o
# $(V) $(OBJDUMP) -S $(OBJDIR)/boot/boot.elf >$(OBJDIR)/bootblock.asm
# $(V) $(OBJCOPY) -S -O binary $^ $(OBJDIR)/bootblock
	$(V) cat $(OBJDIR)/boot/boot.elf $(OBJDIR)/boot/boot.elf >$(OBJDIR)/bootblock

$(OBJDIR)/coreblock: $(KERN_OBJS) tool/kernel.ld
	$(V) echo - ld $^
	$(V) $(LD) $(LDFLAGS) -T tool/kernel.ld -o $(OBJDIR)/core/core.o $(KERN_OBJS)
	$(V) $(OBJDUMP) -S $(OBJDIR)/core/core.o >$(OBJDIR)/core.asm
	$(V) $(OBJCOPY) -S -O binary $(OBJDIR)/core/core.o $(OBJDIR)/coreblock

$(OBJDIR)/boot/%.o: boot/%.s
	@mkdir -p $(OBJDIR)/boot
	$(V) @echo - as $^
	$(V) $(AS) $(SFLAGS) -o $@ $<

$(OBJDIR)/core/%.o:core/%.c
	@mkdir -p $(OBJDIR)/core
	$(V) echo - cc $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/core/%.o:core/%.s
	@mkdir -p $(OBJDIR)/core
	$(V) echo - as $^
	$(V) $(AS) $(SFLAGS) -o $@ $<

$(OBJDIR)/lib/%.o:lib/%.c
	@mkdir -p $(OBJDIR)/lib
	$(V) echo - cc $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/driver/%.o:driver/%.c
	@mkdir -p $(OBJDIR)/driver
	$(V) echo - cc $^
	$(V) $(CC) $(CFLAGS) -o $@ $<

$(IMG): $(OBJDIR)/bootblock $(OBJDIR)/coreblock
	dd if=/dev/zero of=$(IMG) count=1000
	dd if=$(OBJDIR)/boot/boot.elf of=$(IMG) conv=notrunc
	dd if=$(OBJDIR)/boot/setup.elf of=$(IMG) seek=1 conv=notrunc
	dd if=$(OBJDIR)/coreblock of=$(IMG) seek=2 conv=notrunc


qemu: $(IMG)
	$(QEMU) -fda $< -serial mon:stdio

clean:
	rm -rf $(OBJDIR) os.img
