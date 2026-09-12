#define UART_BASE_ADDRESS ((volatile char *)0x10000000)
#define UART_LSR_ADDRESS ((volatile char*) 0x10000005)

void uart_putc(char c){
    while(!((*UART_LSR_ADDRESS) >> 5 & 1)){

    }
    *UART_BASE_ADDRESS = c;
}

void uart_puts(char *c){
    while(*c != '\0'){
        uart_putc(*c);
        c += 1;
    }
}

