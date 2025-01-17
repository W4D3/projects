(define avg (lambda (L)
    (let loop ((L L)
               (count 0)
               (sum 0))
    (if (null? L) (/ sum (+ count 0.0))
        (loop (cdr L)
              (+ count 1)
              (+ sum (car L)))))))
