(define filter (lambda (proc L)
                    (cond ((null? L)  '())
                        ((proc (car L)) (cons (car L) (filter proc (cdr L))))
                        (else (filter proc (cdr L))))))

