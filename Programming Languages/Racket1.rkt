#lang racket

(define x 5)
(define  (fact n)
   (if (= n 0)
      1
      (* n (fact (- n 1 )))))

(define (len alist)
   (if  (empty? alist)
       0
       (+ 1 (len (rest alist)))))

(define (foo x)
   (lambda (y)
     (+ x y)))



;;(define cubeNum
  ;;(p (n)
    ;; (* n n n )))

(define (cubeNum2 n)
  (* n n n))

(define (add x y )
  (+ x y))

(define (sumlist alist)
  (if (empty? alist)
      0
      (+ (first alist) (sumlist (rest alist)))))

(define (sumlist03 alist)
  (let ([f (first alist)]
        [f2 (rest alist)])
  (cond
    [(empty? alist) 0]
    [(list? (first alist))
     (+ (sumlist3 (first alist))
       (sumlist3 (rest alist)))]
    [else
     (+ (first alist ) ( sumlist3 (rest alist)))]
  [else
   (+ (first alist) (sumlist3 ( rest alist)))])))


 (define (sumlist3 alist)
  (if (empty? alist)
      0
      (let ([f (first alist)]
            [r (rest alist)])
        (cond
          [(empty? alist) 0]
          [(list? f)
           (+ (sumlist3 f)
              (sumlist3 r))]
          [else
           (+ f (sumlist3 r))]))))

;;(define x 10)
(define y x)

;;(define (foo n)
  ;;(let ([x x])
   ;; (+ n x)))

(set! x 12)


(define foo2 (cons 1 '(2 3)))

(define fifi (mcons 1 '(2 3)))

(struct person (name age))