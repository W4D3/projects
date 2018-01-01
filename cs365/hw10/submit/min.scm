(define (min ls)
    (let imin ((l (cdr ls))
           (m (car ls)))
    (cond
        ((null? l) m)
    (else
        (let ((a (car l)))
            (imin (cdr l)
            (if (< a m) a m)))))))
