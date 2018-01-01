(define mergesort (lambda (L)
    (cond
        ((null? L) L)
        ((null? (cdr L)) L)
        (else (mergeHelper L '() '() 1)))))
 
(define mergeHelper (lambda (L L1 L2 whichlist?)
    (cond
        ((null? L) (merge (mergesort L1) (mergesort L2)))
        ((= whichList? 1) (mergeHelper (cdr L) (cons (car L) L1) L2 2))
        (else (mergeHelper (cdr L) L1 (cons (car L) L2) 1)))))
 
(define merge (lambda (L1 L2) 
    (cond
        ((null? L1) L2)
        ((null? L2) L1)
        ((< (car L1) (car L2)) (cons (car L1) (merge (cdr L1) L2)))
        (else (cons (car L2) (merge L1 (cdr L2)))))))
