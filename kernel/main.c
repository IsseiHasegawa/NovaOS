#include <stdint.h>
#include "riscv.h"
#include "uart.h"

extern void kernelvec(void);
void timer_init(void);

void kmain(void) {
    uart_puts("Hello from my kernel!\n");

    /* 1. register the emergency cantact: every trap jumps to kernelvec */
    w_stvec((uint64_t)kernelvec);

    /* 2. arm the first timer deadline (1 second from now) */
    timer_init();

    /* 3. switches NO: pre-source (timer), then the master switch */
    w_sie(r_sie() | SIE_STIE); /* enable timer interrupts */
    w_sstatus(r_sstatus() | SSTATUS_SIE); /* enable interrupts */


    for (;;) {
        asm volatile("wfi"); /* wait for interrupt */
    }
}