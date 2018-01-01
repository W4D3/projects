(define fringe (lambda (ls)
    (cond ((null? ls) ls)
          ((null? (cdr ls)) ls)
          (else (fold append '() (map fringe (cdr ls)))))))
