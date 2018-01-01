/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * copy.s
 *
 * Example of creating and using jump tables.
 * [GNU ARM Assembler Workbook, Section 6]
 *
 * ================================================================== */
        .text
        .global _start
        
        .equ    num_func, 3            @ Number of entries in the jump table

_start:
         mov    r0, #0                 @ Function number (index) to use
         mov    r1, #3                 @ First parameter
         mov    r2, #2                 @ Second parameter
         bl     arithfunc              @ Call the function

         swi    0x11                   @ Terminate

arithfunc:                           
         cmp    r0, #num_func
         bhs    DoAdd                  @ If code is >=2, do operation 0
         adr    r3, JumpTable          @ Get the address of the jump table
         ldr    pc, [r3,r0,lsl #2]     @ Jump to the routine (PC = R3 + R0*4)


JumpTable:                             @ Table of function addresses
         .word  DoAdd
         .word  DoSub

DoAdd:
         add    r0, r1, r2             @ Operation 0 (R0 = R1 + R2)
         mov    pc, lr                 @ Return

DoSub:
         sub    r0, r1, r2             @ Operation 1 (R0 = R1 - R2)
         mov    pc,lr                  @ Return

         
         .end
