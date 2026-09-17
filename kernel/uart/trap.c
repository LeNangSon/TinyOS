#include<uart.h>
#include<trap.h>
#include<stdint.h>

extern void trap_entry(void);

void trap_init(void){
    const unsigned long meie = 1UL << 11;

    // enable mie.MEIE (bit 11)
    // enable mstatus.mie (bit 3)
    // order matters
    asm volatile(
        "csrw mtvec, %0"
        :
        : "r"(trap_entry)
    );

    uart_interrupt_init();

    asm volatile("csrs mie, %0" : : "r"(meie) : "memory");
    asm volatile("csrsi mstatus, 8" : : : "memory");
}

static inline unsigned long read_mcause(void){
    unsigned long value;

    asm volatile(
        "csrr %[value], mcause"
        : [value] "=r"(value)
        : 
        :
    );
    return value;
}

void machine_software_interrupt_handler(void){
    uart_puts("Machine Software Interrupt");
    // do something
    *CLINT_BASE = 0;
}

void machine_timer_interrupt_handler(void){
    uart_puts("Machine Timer Interrupt");
    // do something
    *CLINT_MTIMECMP = *CLINT_MTIME + INTERVAL;
}

void machine_external_interrupt_handler(void)
{
    uint32_t irq = *PLIC_CLAIM;

    if (irq == 0)
        return;

    switch (irq) {
        case UART0_IRQ:
            uart_interrupt_handler();
            break;
        default:
            break;
    }

    *PLIC_CLAIM = irq;
}

void trap_handler(void){
     unsigned long mcause;
     unsigned long exception_code;
     mcause = read_mcause();
     exception_code = (mcause << 1) >> 1;
     // interrupt
     if (mcause >> 63){
        switch(exception_code){
            case 3:                // Machine (mode) Software Interrupt
                machine_software_interrupt_handler();
                break;
            case 7:                // Machine (mode) Timer Interrupt
                machine_timer_interrupt_handler();
                break;
            case 11:               // Machine (mode) External Interrupt
                machine_external_interrupt_handler();
                break;   
            default:
                uart_puts("Unknown interrupt");
                break;

        }
     }
     // exception
     else {
        // implement sau ở Ver_1 chỉ in ra thông tin về exception
        uart_puts("Exception");
     }
}
