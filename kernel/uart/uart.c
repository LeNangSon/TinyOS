#include<uart.h>

void uart_interrupt_init(void){
    *UART_IER_ADDRESS |= 1;
    *PLIC_PRIORITY(UART0_IRQ) = 1;
    *PLIC_ENABLE(UART0_IRQ) |= (1U << (UART0_IRQ % 32U));
    *PLIC_THRESHOLD = 0;
}

void uart_putc(char c){
    while(!((*UART_LSR_ADDRESS) >> 5 & 1)){

    }
    *UART_THR_ADDRESS = c;
}

void uart_puts(char *c){
    while(*c != '\0'){
        uart_putc(*c);
        c += 1;
    }
}

void uart_interrupt_handler(void){
    int interrupt_code = (*UART_ISR_ADDRESS >> 1) & 0b111;
    switch (interrupt_code)
    {
    case 0b010:
        
        // handle interrupt
        uint8_t character_received = *UART_RHR_ADDRESS;

        // export to stdout (terminal)
        int THR_READY = (*UART_LSR_ADDRESS) >> 5 & 1;
        if (THR_READY){
            *UART_THR_ADDRESS = character_received;
        }
        break;

    default:
        break;
    }
}
