#lang racket

(define-syntax myIf
  (syntax-rules (then else)
    [(myIf e1 then e2 else e3)
         (if e1 e2 e3)]))

(define-syntax comment
  (syntax-rules ()
    [(comment e1 e2) e2]))



(define (fact n)
  (if (zero? n)
      1
      (* n (fact (- n 1)))))

(define-syntax myAnd
  (syntax-rules ()
    [(e1 and e2) (and e1 e2)]))