#ifndef RISCV_H
#define RISCV_H

#include <stdint.h>

/*
 * CSR access helpers.
 *  csrr rd, CSR    :read a CSR into a register
 *  csrw CSR, rs    :write a register into a CSR
 * The inline asm below wraps these so C code can call them
 * like ordinary functions
 */

 /*
 * Read the scause register.
 *
 * scause describes why the CPU entered the trap handler.
 * It indicates whether the trap was caused by an interrupt or an exception,
 * and contains a code identifying the specific cause.
 */
static inline uint64_t r_scause(void) {
    uint64_t x;
    asm volatile("csrr %0, scause" : "=r"(x));
    return x;
}

/*
 * Read the sepc register.
 *
 * sepc contains the address of the instruction that was executing
 * when the trap occurred.
 */
static inline uint64_t r_sepc(void) {
    uint64_t x;
    asm volatile("csrr %0, sepc" : "=r"(x));
    return x;
}

/*
 * Read the stval register.
 *
 * stval contains additional information about a trap.
 * For example, it may contain the invalid memory address that caused
 * a page fault or an access fault.
 */
static inline uint64_t r_stval(void) {
    uint64_t x;
    asm volatile("csrr %0, stval" : "=r"(x));
    return x;
}

/*
 * Write a value to the stvec register.
 *
 * stvec specifies the address of the S-mode trap handler.
 * The CPU jumps to this address when an S-mode trap occurs.
 */
static inline void w_stvec(uint64_t x) {
    asm volatile("csrw stvec, %0" :: "r"(x));
}

/*
 * Read the sstatus register.
 *
 * sstatus contains status information and control bits for S-mode,
 * including the global S-mode interrupt-enable bit.
 */
static inline uint64_t r_sstatus(void) {
    uint64_t x;
    asm volatile("csrr %0, sstatus" : "=r"(x));
    return x;
}

/*
 * Write a value to the sstatus register.
 *
 * This function is used to change S-mode status settings,
 * such as globally enabling or disabling interrupts.
 */
static inline void w_sstatus(uint64_t x) {
    asm volatile("csrw sstatus, %0" :: "r"(x));
}

/*
 * Read the sie register.
 *
 * sie controls which types of S-mode interrupts are enabled,
 * such as timer, software, and external interrupts.
 */
static inline uint64_t r_sie(void) {
    uint64_t x;
    asm volatile("csrr %0, sie" : "=r"(x));
    return x;
}

/*
 * Write a value to the sie register.
 *
 * This function enables or disables individual types of S-mode interrupts.
 */
static inline void w_sie(uint64_t x) {
    asm volatile("csrw sie, %0" :: "r"(x));
}

/*
 * Read the current hardware timer value.
 *
 * The time register is an always-increasing counter provided by
 * the platform's hardware timer.
 */
static inline uint64_t r_time(void) {
    uint64_t x;
    asm volatile("csrr %0, time" : "=r"(x));
    return x;
}

/*
 * Set the next S-mode timer interrupt deadline.
 *
 * A timer interrupt becomes pending when the value of time reaches
 * or exceeds the value stored in stimecmp.
 *
 * This register is available when the RISC-V Sstc extension is supported.
 */
static inline void w_stimecmp(uint64_t x) {
    asm volatile("csrw stimecmp, %0" :: "r"(x));
}

/* ---- bit constants ---- */
#define SSTATUS_SIE (1UL << 1)
#define SIE_STIE    (1UL << 5)

/* scause: top bit set - interrupt, low bits = code */
#define SCAUSE_INTERRUPT (1UL << 63)
#define IRQ_S_TIMER 5

#endif
