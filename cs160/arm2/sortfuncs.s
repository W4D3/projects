/* ==================================================================
 *
 * CS 160 Mitchell Wade -- arm2: Sorting an array 
 *
 * sortfuncs.s
 * ARM assembly implementation of sort1, sort2, and sort3.
 * ================================================================== */

    .text

@ Export the functions for the linker:
    .global sort1           
    .global sort2
    .global sort3

@ Shorthand register renaming notation:
@
@ a1-a4 == r0-r3
@ v1-v9 == r4-r12

/* ---------- sort1 -------------------------------------------------
  Sorts a given array by comparing each element of the arrays

  for (i=0; i<N; i++) {
    if (ListA[i] < ListB[i]) {
        ListA[i] = ListB[i];
    }
  }

  Parameters: a1 -- pointer to byte array of length N
              a2 -- pointer to byte array of length N
			  a3 -- value of N
  ------------------------------------------------------------------- */
sort1:
    stmdb    sp!, {v1-v5, lr}          @ Copy registers to stack

loop:
    ldrb     v1, [a1], #1              @ Load ListA[i] and increment
    ldrb     v2, [a2], #1              @ Load ListB[i] and increment
    cmp      v1, v2                    @ Is v1 - v2 = less than zero
    blt      update                    @ go to subroutine update if b is less than
    b        counter2                  @ alway branch to counter

update:
    mov      v1, v2                    @ v1 = v2
    strb     v1, [a1, #-1]             @ store v1 in ListA[i] and decrement
    b        counter2                  @ always branch to counter

counter:
    sub      a3, a3, #1
    cmp      a3, #0
    bgt      loop
    ldmia    sp!, {v1-v5, pc}          @ Copy stack back into registers

/* ---------- sort2 -------------------------------------------------
   Sorts a given array using selection sort.

   for (j=N-1; j>0; j=j-1 {
     for (k=j-1; k >= 0; k=k-1 {
       if (list[k] > list[j]) {
         tmp = list[k];
         list[k]= list[j];
         list[j] = tmp;
       }
     }
   }

   Parameters: a1 -- pointer to byte array of length N
               a2 -- value of N
   ------------------------------------------------------------------- */
sort2:
    stmdb    sp!, {v1-v5, lr}          @ Copy registers to stack
    sub      a2, a2, #1                @ Decrement, Go to next element (a2 = a2 - 1)

outer:
    sub      a3, a3, #1                @ Save the next element in a3
    cmp      a2, #0                    @ a2 - 0 = beq??
    beq      end                       @ Break out if loop is done

inner:
    ldrb     v1, [a1, +a2]             @ Load the next element
    ldrb     v2, [a1, +a3]             @ Load the next element
    cmp      v2, v1                    @ v2 - v1 = greater than?
    bgt      counter2                  @ if greater than branch to counter

continue:
    sub     a3, a3, #1                 @ Decrement, Go to next element (a3 = a3 - 1)
    cmp     a3, #0                     @ a3 - 0 = bge??
    bge     inner                      @ Go to inner loop
    sub     a2, a2, #1                 @ Decrement
    b       outer                      @ Go to the outer loop

counter2:
    strb     v2, [a1, a2]
    strb     v1, [a1, a3]
    b        continue

end:
    ldmia    sp!, {v1-v5, pc}          @ Copy stack back into registers

/* ---------- sort3 -------------------------------------------------
  Pseudo C code of what needs to be done

  Parameters: a1 -- pointer to byte array of length N
              a2 -- value of N
  ------------------------------------------------------------------- */
sort3:
    stmdb    sp!, {v1-v5, lr}          @ Copy registers to stack
    ldmia    sp!, {v1-v5, pc}          @ Copy stack back into registers

    .end
