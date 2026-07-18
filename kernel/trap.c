#include <stdint.h>
#include "riscv.h"
#include "uart.h"

/* the counter runs at 10,000,000 ticks/sec on QEMU virt -> 1 second */
#define TIMER_INTERVAL 10000000L

/* arm the first deadline ( called once from kmain)*/
void timer_init(void) {
    w_stimecmp(r_time() + TIMER_INTERVAL);
}

static void timer_tick(void) {
    uart_puts("tick\n");
    /* arm the next deadline == forget this and the heartbeat stops */
    w_stimecmp(r_time() + TIMER_INTERVAL);
}

/* called from kernelvec.s after all registers are saved */
void kerneltrap(void) {
    uint64_t cause = r_scause();

    if (cause == (SCAUSE_INTERRUPT | IRQ_S_TIMER)) {
        timer_tick();
    } else {
        /* unknown trap: print everything we know, then stop */
        uart_puts("PANIC: unexpected trap\n");
        uart_puts("  scause = "); uart_puthex(cause);    uart_putc('\n');
        uart_puts("  sepc   = "); uart_puthex(r_sepc()); uart_putc('\n');
        uart_puts("  stval  = "); uart_puthex(r_stval()); uart_putc('\n');
        for (;;) { }
    }
}

