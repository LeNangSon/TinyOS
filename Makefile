CFLAGS := -mcmodel=medany -ffreestanding

kernel.elf: linker.ld entry.o kernel.o uart.o
	riscv64-elf-ld -T linker.ld entry.o kernel.o uart.o -o kernel.elf
entry.o: kernel/entry.S
	riscv64-elf-gcc $(CFLAGS) -c kernel/entry.S -o entry.o
uart.o: kernel/uart/uart.c 
	riscv64-elf-gcc $(CFLAGS) -c kernel/uart/uart.c -o uart.o
kernel.o: kernel/kernel.c kernel/uart/uart.h
	riscv64-elf-gcc $(CFLAGS) -c kernel/kernel.c -Ikernel/uart -o kernel.o
run: kernel.elf
	qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf -nographic
