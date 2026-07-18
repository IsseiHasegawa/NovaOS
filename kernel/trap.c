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

