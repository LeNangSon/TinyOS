#ifndef TRAP_H
#define TRAP_H

#define CLINT_BASE (volatile uint64_t*)0x02000000
#define CLINT_MTIMECMP  (volatile uint64_t*)(CLINT_BASE+0x4000)
#define CLINT_MTIME (volatile uint64_t*)(CLINT_BASE+0xBFF8)
#define INTERVAL 10000

void trap_init(void);
void trap_handler(void);


#endif