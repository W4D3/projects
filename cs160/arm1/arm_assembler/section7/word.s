/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * word.s
 *
 * Example of performing word-block copies of memory.
 * [GNU ARM Assembler Workbook, Section 7]
 *
 * ================================================================== */
   
        .text
        .global _start

        .equ    num, 20         @ Number of words to copy

_start:
        ldr     r0, =src        @ Pointer to source block
        ldr     r1, =dst        @ Pointer to destination block
        mov     r2, #num        @ Number of words to copy

wordcopy:
        ldr     r3,[r0],#4      @ Load a word into R3 and update R0
                                @   (post-indexed: R0 := R0 + 4)
        str     r3,[r1],#4      @ Store the word and update R1
        subs    r2,r2,#1        @ Decrement the word counter
        bne     wordcopy        @   and repeat loop if not finished

exit:   swi     0x11


        .data                   @ Read/write data follows
        .align                  @ Make sure data is aligned on 32-bit 
                                @   boundaries

src:    .word     1,  2,  3,  4,  5,  6,  7,  8,  9, 10
        .word    11, 12, 13, 14, 15, 16, 17, 18, 19, 20

dst:    .word     0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        .word     0,  0,  0,  0,  0,  0,  0,  0,  0,  0

        .end
