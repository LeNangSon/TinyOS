CFLAGS := -mcmodel=medany -ffreestanding
OBJS := entry.o kernel.o uart.o trap.o trap_entry.o

kernel.elf: linker.ld $(OBJS)
	riscv64-elf-ld -T linker.ld $(OBJS) -o kernel.elf
entry.o: kernel/entry.S
	riscv64-elf-gcc $(CFLAGS) -c kernel/entry.S -o entry.o
uart.o: kernel/uart/uart.c kernel/uart/uart.h
	riscv64-elf-gcc $(CFLAGS) -Ikernel/uart -c kernel/uart/uart.c -o uart.o
trap.o: kernel/uart/trap.c kernel/uart/trap.h kernel/uart/uart.h
	riscv64-elf-gcc $(CFLAGS) -Ikernel/uart -c kernel/uart/trap.c -o trap.o
trap_entry.o: kernel/uart/trap_entry.S
	riscv64-elf-gcc $(CFLAGS) -c kernel/uart/trap_entry.S -o trap_entry.o
kernel.o: kernel/kernel.c kernel/uart/uart.h kernel/uart/trap.h
	riscv64-elf-gcc $(CFLAGS) -c kernel/kernel.c -Ikernel/uart -o kernel.o
run: kernel.elf
	qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf -nographic
