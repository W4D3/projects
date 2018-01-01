/* ==================================================================
 *
 * CS 160, Fall 2007 (Gregor)
 *
 * Lab 7 -- Introduction to ARM
 *
 * copy.s
 *
 * Example of calling ARM subroutines.
 * [GNU ARM Assembler Workbook, Section 4]
 *
 * ================================================================== */
        .text                          @ Executable code below
       
_start: .global _start                 @ "_start" is required by the linker 
        .global main                   @ "main" is the main program
        
        b       main                   @ Start the main program 
        
main:                                  @ Entry to function "main"
        ldr     r0,=dststr             @ Pointer to the first string 
        ldr     r1,=srcstr             @ Pointer to the second string 

strcopy:
        ldrb    r2, [r1], #1           @ Load byte and update address
        strb    r2, [r0], #1           @ Store byte and update address
        cmp     r2, #0                 @ Check for \0 
        bne     strcopy                @ Keep looping if \0 not found 
        bl      srcstr                 @ Call the function

        swi     0x11                   @ Software interrupt to terminate 

        .align
srcstr: .asciz "First string - source"
        mov     pc, lr                 @ Return
dststr: .asciz "Second string - destination"
        mov     pc, lr                 @ Return
        .end
