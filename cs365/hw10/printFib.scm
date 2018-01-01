(define printFib
            (lambda (fib n)
                    (if (> n 0)
                    (let ()
                            (display (car fib))
                            (display " ")
                            (printFib (force (cdr fib)) (- n 1))))))
