#lang racket
(define (myIf a b c )
  (if a (b) (c)))

(define (myDelay func)
  (mcons #f func))

(define (myForce thunk)
  (cond
    [(mcar thunk) (mcdr thunk)]
    [else
      (set-mcar! thunk #t)
      (set-mcdr! thunk ((mcdr thunk)))
      (mcdr thunk)]))

(define (onetwo)
  (+ 1 2))

(define onetwoThunk (myDelay onetwo))

;;;Stream Examples
(define ones (lambda() (cons 1 ones)))

(define nats
  (letrec ([f (λ (x) ;;;let rec???
               (cons x (λ ()
                         (f (+ x 1)))))])
    (λ () (f 0))))


(define powersoftwo
  (letrec ([f (λ (x) 
               (cons x (λ ()
                         (f (* x 2)))))])
    (λ () (f 1))))

(define (elemUntil stream predicate)
  (letrec ([f (λ (stream answer)
                (let ([pr (stream)])
                  (if (predicate (car pr))
                      answer
                      (f (cdr pr) (+ answer 1)))))])
    (f stream 1)))


(define (streamUntil stream predicate) ;;???
  (letrec ([f (λ (stream answer)
                (let ([pr (stream)])
                  (if (predicate (car pr))
                      answer
                      (f (cdr pr) (append answer (list(car pr)))))))])
    (f stream '() )))



(define (streammaker func arg)
  (letrec ([f (λ (x)
                (cons x (λ () (f (func x arg)))))])
    (λ () (f arg))))



(define ones* (streammaker (λ (a b) 1) 1))
(define nats* (streammaker (λ (a b) (+ a b)) 1))  ;;???

(define nats** (streammaker + 1))
(define powers* (streammaker * 1))