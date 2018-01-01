/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * copy.s
 *
 * Example of calling ARM subroutines.
 * [GNU ARM Assembler Workbook, Section 4]
 *
 * ================================================================== */
        .text                          @ Executable code below
        .global strcopy
       
strcopy:
        ldrb    r2, [r1], #1           @ Load byte and update address
        strb    r2, [r0], #1           @ Store byte and update address
        cmp     r2, #0                 @ Check for \0 
        bne     strcopy                @ Keep looping if \0 not found 
        mov     pc, lr                 @ Return from the subroutine

        .end
