#lang racket

(require test-engine/racket-tests)

(define (streammaker func arg)
  (letrec ([f (λ (x)
                (cons x (λ () (f (func x arg)))))])
    (λ () (f arg))))

(define s (lambda() (cons 1 s)))

(define ones* (streammaker (λ (a b) 1) 1))
(define nats* (streammaker (λ (a b) (+ a b)) 1)) 
(define powers* (streammaker(λ (a b) (* a 2)) 1))



;;Write a function next-k-items that takes two arguments, the first is a stream s and the second is a number k, and it produces a list consisting of the next k elements extracted from the stream.
;;You can assume k is non-negative. Note: this can be used to test the streams you make later.

;;This function named next-k-items, and this function can get k elements from the stream. It is return the list.
;;type: list
(define (next-k-items s k)
  (if  (or (< k 0) (= k 0))
      '()
      (cons (car (s)) (next-k-items (cdr(s)) (- k 1)))))



;;Write a function kth-item that takes two arguments, the first is a stream s and the second is a number k, and it produces the result of extracting k elements from the stream, returning only the last element.
;;Very similar to the previous problem, but only returns a single element. You may assume k is greater than 0.

;;This function named kth-item, and this function can get kth element from the stream, which is single element. element. It is return the element from stream the type from stream.
;;type: number
(define (kth-item s k)
  (if (or (< k 0) (= k 0))
      '()
      (if (= k 1)
          (car(s))
          (kth-item (cdr(s)) (- k 1)))))



    (define (getEnv x y cenv)
                   (if (or (null? x) (null? y))
                       cenv
                       (getEnv (cdr x) (cdr y) (extend-env cenv (car x) (eval-expr cenv (car y))))))


(check-expect (next-k-items ones* 1) '(1))
(check-expect (next-k-items ones* 5) '(1 1 1 1 1))
(check-expect (next-k-items nats* 1) '(1))
(check-expect (next-k-items nats* 5) '(1 2 3 4 5))
(check-expect (next-k-items powers* 1) '(1))
(check-expect (next-k-items powers* 5) '(1 2 4 8 16))
(check-expect (kth-item ones* 1) 1)
(check-expect (kth-item ones* 5) 1)
(check-expect (kth-item nats* 1) 1)
(check-expect (kth-item nats* 5) 5)
(check-expect (kth-item powers* 1) 1)
(check-expect (kth-item powers* 5) 16)

(test)