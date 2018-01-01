/* ==================================================================
 *
 * CS 160 (Mitchell Wade) -- arm3: Logarithmic reduction based summing of
 *                             elements in an array 
 *
 * ================================================================== */

	.text

	@ Export the logsum function to the linker
	.global sumR

/* ------------------------------------------------------------------

    Psuedo C Code
    int i, j, k, N = 7, log = 3;
    int X[] = {1, 2, 3, 4, 3, 2, 1};
    
    for (i=0; i<log; i++) {
        for (j=0; j<N/2; j++) {
        
        X[j<<1] = X[j] + X[j+1];
        
        }
    }
    
    return X[0];


   Parameters: 
   r0 - return value
   r1 - number of array elements

   ------------------------------------------------------------------ */

sumR:

    mov ip, sp                       @save registers
    stmfd   sp!, {fp, ip, lr, pc}
    sub fp, ip, #4
    sub sp, sp, #8
    str r0, [fp, #-16]               @ store arguments on stack
    str r1, [fp, #-20]
    str r1, [fp, #-24]               @ store array elements
    mov r3, #4

loop:
    ldr r0, [fp, #-16]
    ldr r1, [fp, #-24]
    and r2, r1, #1                  @ N%2
    str r2, [fp, #-28]              @ Store N%2
    mov r1, r1, lsr #1              @ Divide by 2
    str r1, [fp, #-24]              @ Increment inner loop
    cmp r1, #0                      @ Exit if r1 = zero
    beq endLoop

loop2:
    cmp r1, #0
    beq exitLoop
    ldr r2, [r0]            
    ldr r4, [r0, r3]                @ Load next pair
    add r2, r2, r4
    str r2, [r0]                    @ Store sum
    str r3, [fp, #-32]              @ Store on stack
    add r3, r3, r3
    add r0, r0, r3                  @ Add offset to next pair
    ldr r3, [fp, #-32]
    sub r1, r1, #1                  @ Decrement count
    bl loop2

exitLoop:
    ldr r2, [fp, #-28]              @ Load N%2 to r2
    cmp r2, #0                      @ Handle extra array if N%2=1, else skip
    beq loop3
    ldr r1, [r0]                    @ Load next array value
    ldr r0, [fp, #-16]
    ldr r2, [r0]
    add r2, r2, r1
    str r2, [r0]

loop3:
    add r3, r3, r3
    bl loop

endLoop:
    ldr r0, [fp, #-16]
    ldr r0, [r0]
    sub sp, fp, #12                 @ Restore registers
    ldmfd   sp, {fp, sp, pc}

	.end
