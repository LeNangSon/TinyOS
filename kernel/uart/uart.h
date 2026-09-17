#ifndef UART_H
#define UART_H

#include<stdint.h>

#define UART0_IRQ 10U
#define PLIC_BASE ((uintptr_t)0x0C000000UL)

#define UART_THR_ADDRESS ((volatile uint8_t*)0x10000000)
#define UART_RHR_ADDRESS ((volatile uint8_t*) 0x10000000)
#define UART_LSR_ADDRESS ((volatile uint8_t*) 0x10000005)
#define UART_ISR_ADDRESS ((volatile uint8_t*) 0x10000002)
#define UART_IER_ADDRESS ((volatile uint8_t*) 0x10000001)

#define PLIC_PRIORITY(irq)  ((volatile uint32_t *)(PLIC_BASE + (irq) * 4U))
#define PLIC_ENABLE(irq)    ((volatile uint32_t *)(PLIC_BASE + 0x2000UL + ((irq) / 32U) * 4U))
#define PLIC_THRESHOLD      ((volatile uint32_t *)(PLIC_BASE + 0x200000UL))
#define PLIC_CLAIM          ((volatile uint32_t *)(PLIC_BASE + 0x200004UL))

void uart_putc(char c);
void uart_puts(char *c);
void uart_interrupt_handler(void);
void uart_interrupt_init(void);

#endif
