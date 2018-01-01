/* ==================================================================
 *
 * CS 160 (Gregor) -- arm1: Introduction to ARM
 *
 * copy.s
 *
 * Example of loading addresses into registers.
 * [GNU ARM Assembler Workbook, Section 3]
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

        swi     0x11                   @ Software interrupt to terminate 

        .align
srcstr: .asciz "First string - source"
dststr: .asciz "Second string - destination"
        
        .end
