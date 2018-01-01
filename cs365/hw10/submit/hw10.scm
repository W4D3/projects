; Fibonacci Function
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
; Average Function
(define avg (lambda (L)
    (let loop ((L L)
              (count 0)
              (sum 0))
        
    (if (null? L) (/ sum (+ count 0.0))
        (loop (cdr L)
            (+ count 1)
            (+ sum (car L)))))))

; Filter Function
(define filter (lambda (proc L)
                    (cond ((null? L)  '())
                        ((proc (car L)) (cons (car L) (filter proc (cdr L))))
                        (else (filter proc (cdr L))))))

; Fringe Function
(define fringe (lambda (ls)
    (cond ((null? ls) ls)
          ((null? (cdr ls)) ls)
          (else (fold append '() (map fringe (cdr ls)))))))

; Mergesort Function
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

; Min Function
(define (min ls)
    (let imin ((l (cdr ls))
           (m (car ls)))
    (cond
        ((null? l) m)
    (else
        (let ((a (car l)))
            (imin (cdr l)
            (if (< a m) a m)))))))

; Swap Function
(define swap(lambda (a b)
                (if (< a b) 
                    (cons a b) 
                    (cons b a))))
