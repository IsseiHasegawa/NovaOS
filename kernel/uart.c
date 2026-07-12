#include "uart.h"

#define UARTO 0x10000000L
#define UART_THR (UARTO + 0x00) /* transmit holding register */

void uart_putc(char c) {
    volatile uint8_t *thr = (volatile uint8_t *)UART_THR;
    *thr = (uint8_t)c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_puts(*s++);
    }
}

void uart_puthex(uint64_t v) {
    uart_puts("0x");
    for (int i = 60; i >= 0; i -= 4) {
        int d = (v >> i) & 0xf;
        uart_putc(d < 10 ? '0' + d : 'a' + (d - 10));
    }
}