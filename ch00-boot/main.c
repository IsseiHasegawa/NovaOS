#include <stdint.h>

#define UART0 0x10000000L
#define UART_THR (UART0 + 0x00) /* transmit holding register */

static void uart_putc(char c) {
    volatile uint8_t *thr = (volatile uint8_t *)UART_THR;
    *thr = (uint8_t)c;
}

static void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

void kmain(void) {
    uart_puts("Hello from my kernel!\n");
    for (;;) {
        /* nothing yet */
    }
}