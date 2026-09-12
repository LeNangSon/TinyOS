#include <uart.h>
#include<trap.h>

void kernel_main(void){
    trap_init();

    char s[] = "TinyOS booting...\nHello TinyOS!";

    uart_puts(s);

    while(1){
        
    };
}