# Toolchain (Homebrew LLVM). `brew --prefix llvm` finds where brew installed it.
LLVM    := $(shell brew --prefix llvm)/bin
CC      := $(LLVM)/clang
LD      := $(shell brew --prefix lld)/bin/ld.lld

TARGET  := riscv64-unknown-elf
CFLAGS  := --target=$(TARGET) -march=rv64g -mabi=lp64 \
           -mcmodel=medany -ffreestanding -nostdlib \
           -fno-builtin -Wall -Wextra -O0 -g

LDFLAGS := -T kernel.ld

OBJS := boot.o kernelvec.o uart.o trap.o main.o

kernel.elf: $(OBJS) kernel.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

boot.o: boot.s
	$(CC) $(CFLAGS) -c boot.s -o boot.o

kernelvec.o: kernelvec.s
	$(CC) $(CFLAGS) -c kernelvec.s -o kernelvec.o

uart.o: uart.c uart.h
	$(CC) $(CFLAGS) -c uart.c -o uart.o

trap.o: trap.c riscv.h uart.h
	$(CC) $(CFLAGS) -c trap.c -o trap.o

main.o: main.c riscv.h uart.h
	$(CC) $(CFLAGS) -c main.c -o main.o

run: kernel.elf
	qemu-system-riscv64 -machine virt -bios default -kernel kernel.elf -nographic

clean:
	rm -f *.o kernel.elf

.PHONY: run clean