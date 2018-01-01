/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * value.s
 *
 * Example of loading values into registers.
 * [GNU ARM Assembler Workbook, Section 2]
 *
 * ================================================================== */
        .text                          @ Executable code below 
       
_start: .global _start                 @ "_start" is required by the linker 
        .global main                   @ "main" is the main program
        
        b       main                   @ Start the main program 
        
main:                                  @ Entry to function "main" 
        mov     r0, #0x1               @ 1 
        mov     r1, #0xFFFFFFFF        @ -1 (signed) 
        mov     r2, #0xFF              @ 255
        mov     r3, #257               @ 257 
        mov     r4, #0x400             @ 1024

        swi     0x11                   @ Software interrupt to terminate 
        
        .end
