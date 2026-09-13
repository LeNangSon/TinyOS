#include<uart.h>
#include<trap.h>
#include<stdint.h>

extern void trap_entry(void);

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
    // do something
    uart_puts("Machine Software Interrupt");
    *CLINT_BASE = 0;
}

void machine_timer_interrupt_handler(void){
    // do something
    uart_puts("Machine Timer Interrupt");
    *CLINT_MTIMECMP = *CLINT_MTIME + INTERVAL;
}

void machine_external_interrupt_handler(void){
    // do something
    uart_puts("Machine External Interrupt");
}

void trap_init(void){
    asm volatile(
        "csrw mtvec, %0"
        :
        : "r"(trap_entry)
    );
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
