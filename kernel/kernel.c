#include<uart.h>

void kernel_main(void){
    /*while(UART_LSR_ADDRESS & (1<<5)){

    }*/

    char s[] = "Hello";

    uart_puts(s);

    while(1){

    };
}