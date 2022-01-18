#lang racket

(require test-engine/racket-tests)

;;module A8 where
;;Write a function, squareSum, which takes a non-negative integer n and returns the sum of the squares of all integers 0 through n.
;;Your function need not behave well on inputs less than zero.

;;This function named squareSum, and this function can square all element that smaller than the number user entered and sum. It is return the number of sum.
;;type: number
(define (squareSum num)
  (if (< num 0)
      0
      (+ (* num num) (squareSum (- num 1)))))


(define squareSum2 (λ (x) (* x x)))



;;Write a function, cycleOne, which takes a list and returns a list which is the same as the input parameter list but with the first element of the list moved to the end.
;;For example, cycleOne '(1 2 3 4) should produce '(2 3 4 1).

;;This function named cycleOne, and this function can get a list and let the first element move to last in the list. It is return the list.
;;type: list
(define (cycleOne alist)
  (if (or (empty? alist) (empty? (rest alist)))
      alist
      (append (rest alist) (list (first alist)))))



;;Write a function, cycleN that takes two parameters, count and a list, and produces the same list but with the first element cycled to the end of the list count number of times.
;;For example: cycleN 2 '(1 2 3 4) should produce '(3 4 1 2) and cycleN 0 '(1 2 3 4) should produce '(1 2 3 4) and cycleN 4 '(1 2 3 4) should also produce '(1 2 3 4).

;;This function named cycleN, and this function can get a list and let the first element move to last in the list, and this fuction do it n times. It is return the list.
;;type: list
(define (cycleN num alist)
  (if (empty? alist)
      '()
      (if (= num 0)
          alist
          (cycleN (- num 1) (append (rest alist) (list (first alist)))))))
          ;(for ([i num])
            ;(cycleOne alist)))))
          


;;Write a function, memberOf?, which takes a value and a list of values. The function returns true if the list contains the value and false otherwise.
;;Use the equal? predicate to determine whether two values are equal or not.

;;This function named memberOf?, and this function can check if the number is in the list, and this fuction do it n times. It is return the boolean.
;;type: boolean
(define (memberOf? value alist)
  (if (empty? alist)
     #f
     (if (equal? value (first alist))
         #t
         (memberOf? value (rest alist)))))



;;Write a function, intersection, which takes two lists as parameters and produces a new list which is the intersection of the values in the lists.
;;You should use the memberOf? function from the previous problem.

;;This function named intersection, and this function can check if both lists have the same elements, and it will return the same element to a new list.
;;type: list
(define (intersection alist blist)
  ;(cond [(empty? alist) '()]
        ;[(empty? blist) '()]
        ;[(memberOf? (first alist) blist) (list (first alist))]
        ;[else (intersection (rest alist) blist)]))
  (if (or (empty? alist) (empty? blist))
      '()
      (if (memberOf? (first alist) blist)
          (append (list (first alist)) (intersection (rest alist) blist))
          (intersection (rest alist) blist))))
      
(check-expect (squareSum 0) 0)
(check-expect (squareSum 1) 1)
(check-expect (squareSum 2) 5)
(check-expect (squareSum 3) 14)
(check-expect (squareSum 4) 30)
(check-expect (squareSum 5) 55)
(check-expect (cycleOne '()) '())
(check-expect (cycleOne '(0)) '(0))
(check-expect (cycleOne '(1 2)) '(2 1))
(check-expect (cycleOne '(1 2 3 4)) '(2 3 4 1))
(check-expect (cycleOne '(a b c d w)) '(b c d w a))
(check-expect (cycleOne '("this" "is" "fun")) '("is" "fun" "this"))
(check-expect (cycleN 0 '()) '())
(check-expect (cycleN 100 '(a)) '(a))
(check-expect (cycleN 0 '(1 2 3 4)) '(1 2 3 4))
(check-expect (cycleN 1 '(1 2 3 4)) '(2 3 4 1))
(check-expect (cycleN 2 '(1 2 3 4)) '(3 4 1 2))
(check-expect (cycleN 5 '(a b c d e)) '(a b c d e))
(check-expect (memberOf? 0 '()) #f)
(check-expect (memberOf? 0 '(0)) #t)
(check-expect (memberOf? 0 '(0 1 2 3 4)) #t)
(check-expect (memberOf? 0 '(1 2 3 4 5)) #f)
(check-expect (memberOf? 0 '(2 3 4 5 6 0)) #t)
(check-expect (memberOf? "abc" '("def" "hij" "kmn" "abc")) #t)
(check-expect (intersection '() '()) '())
(check-expect (intersection '(1 2 3 4) '()) '())
(check-expect (intersection '() '(1 2 3 4)) '())
(check-expect (intersection '(1 2 3 4) '(1 2 3 4)) '(1 2 3 4))
(check-expect (intersection '(1 2 3 4 5 6) '(4 5 6 7 8 9)) '(4 5 6))
(check-expect (intersection '("A" "a" "B" "b" "C" "c") '("A" "B" "C" "D" "E")) '("A" "B" "C"))

(test)
      
      




     