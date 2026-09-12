#include <stdint.h>

extern void trap_entry(void);

void trap_init(void){
    __asm__ volatile(
        "la t0, %[trap_entry_addr]\n\t"
        "csrrs zero, mtvec, t0"
        : 
        : [trap_entry_addr] "r" (trap_entry)
        :
    );
}

void trap_handle(void){
    
}
