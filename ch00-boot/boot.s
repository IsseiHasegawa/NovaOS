.section .text.boot
.global _start
_start:
    # Open hands control here in S-mode.
    #Set up a stack, then jump to C.
    la   sp, stack_top
    call kmain

    # if kmain ever returns, park the core.
hang:
    wfi
    j hang

.section .bss
.align 16
stack_bottom:
    .space 16384   #16 KiB stack
stack-top: