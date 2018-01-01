(define (merge
            (lambda (L1 L2)
                (cond
                    ((null? L1) L2)
                    ((null? L2) L1)
                    ((<= (car L1) (car L2))
                    ((cons (car L1) (merge (cdr L1) L2)))
                (else
                    ((cons (car L2) (merge (cdr L2) L1)))))))))

(define (mergesort
            (lambda L1)
                (cond
                    ((null? L1) L2)
                    ((null? L2) L1)
                    (let (left (cdr (split L1)))
                         (right (cdr (split L2))))
                         (merge (mergesort left) (mergesort right)))))

;                    ((<= (car L1) (car L2)) 
;                    (cons (car L1) (mergesort (cdr L1) L2 mergesort)))
;                (else 
;                    (cons (car L2) 
;                    (mergesort L1 (cdr L2) merge))))))
