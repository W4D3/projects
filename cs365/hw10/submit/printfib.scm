(define fib
    (letrec (
        (fib-helper 
            (lambda (f1 f2)
                (cons f1 
                    (delay (fib-helper f2 (+ f1 f2)))))))
                        (fib-helper 0 1)))

(define printFib
    (lambda (fib n)
        (if (> n 0)
            (let ()
                    (display (car fib))
                    (display " ")
                    (printFib (force (cdr fib)) (- n 1))))))
