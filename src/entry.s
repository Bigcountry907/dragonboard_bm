    .text
    .global bm_start
bm_start:

    bl   get_cpu_id
    bl   setup_boot_stack
    bl   c_entry



    // X0 contains cpu_id
setup_boot_stack:
    LDR     X1, =tmp_stack_size
    LDR     X1, [X1, #0]
    MUL     X1, X0, X1
    LDR     X2, =tmp_stack
    MOV     SP, X2
    SUB     SP, SP, X1              // get to the correct stack for the cpu
    RET


get_cpu_id:
    mov     x0, #0
    ldr     x1, =cpu_id_word

cpuid_ex_loop:
    ldxr   w0, [x1]
    add    w0, w0,#1
    stxr   w2, w0, [x1]
    cbnz   w2, cpuid_ex_loop

    RET


    .data

.balign 8

cpu_id_word:
    .word 0xFFFFFFFF
    .word 0xFFFFFFFF

    .balign 0x1000
tmp_stack_top:
    .global tmp_stack_top
    # space for stack
    #
    .rept 4
    .space 4096
    .endr
tmp_stack:
    .global tmp_stack
tmp_stack_size:
    .global tmp_stack_size
    .word 0x1000
    .end

