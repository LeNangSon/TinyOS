#include<uart.h>

void kernel_main(void){
    char s[] = "TinyOS booting...\nHello TinyOS!";

    uart_puts(s);

    while(1){
        
    };
}