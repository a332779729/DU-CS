#lang racket
(define (fibonacci n)
  (if (or (= n 1) (= n 2))
      1
      (+ (fibonacci (- n 1))
         (fibonacci (- n 2)))))


(define (fibi n)
  (letrec ([f (lambda (acc1 acc2 y)
                (if (= n y)
                    (+ acc1 acc2)
                    (f (+ acc1 acc2) acc1 (+ y 1))))])
    (if (or (= n 1) (= n 2))
        1
        (f 1 1 3))))


(define fibm
  (letrec ([memo null]
           [f (lambda (x)
                (let ([ans (assoc x memo)])
                  (if ans
                      (cdr ans)
                      (let ([new-ans (if (or (= x 1) (= x 2))
                                         1
                                         (+ (f (- x 1))
                                            (f (- x 2))))])
                        (set! memo (cons (cons x new-ans) memo))
                        new-ans))))])
    f))


