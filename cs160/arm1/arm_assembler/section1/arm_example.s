/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * arm_example.s
 *
 * Simple example of ARM assembly language structure.
 * [GNU ARM Assembler Workbook, Section 1]
 *
 * ================================================================== */
        .text                          @ Executable code below
       
_start: .global _start                 @ "_start" is required by the linker
        .global main                   @ "main" is the main program 
        
        b       main                   @ Start the main program
        
main:                                  @ Entry to function "main"

        mov     r0, #10         
        mov     r1, #3
        mul     r1, r0, r1             @ r0 = r0 * r1 

        swi     0x11                   @ Software interrupt to terminate
        
        .end
        
