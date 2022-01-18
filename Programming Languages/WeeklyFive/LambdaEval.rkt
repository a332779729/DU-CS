#lang racket

(require parser-tools/yacc
         (prefix-in lex: parser-tools/lex)
         "JSONAbstractSyntaxTree.rkt"
         "JSONParser.rkt")

(require test-engine/racket-tests)

(define (empty-env)
  (lambda (searchVar)
    (error "No Binding Found" searchVar)))

(define (extend-env savedVar savedVal savedEnv)
  (lambda (searchVar)
    (if (equal? searchVar savedVar)
        savedVal
        (apply-env savedEnv searchVar))))

(define (apply-env env searchVar)
  (env searchVar))

;(struct identifier (name) #:transparent)
;(struct def (name expr) #:transparent)
;(struct app (expr1 expr2) #:transparent)

(define (eval expression)
  (evalHelper expression (empty-env)))

(define (evalHelper expression env)
  (match expression
    [(emptyVal)        '()]
    [(TrueVal e1)      #t]
    [(FalseVal e1)      #f]
    [(NullVal e1)       '()]
    [(StrVal e1)         e1]
    [( NumVal e1)         e1]
    [(StrJSONPair e1 e2)    (list e1 (eval e2))]
    [(list e1) (eval e1)]
    [(Array e1)          (map eval e1)]
    [(ObjVal e1)         (map eval e1)]
    
    ;;; Apply function expr1 to the argument expr2
    
                    
    ))

;;1. Write a function objectContains? which consumes a JSON Object and a field name and produces a boolean (the type is: JSON -> String -> Boolean).
;;If the JSON object contains a field given by the second argument, it will return true and otherwise it returns false.
;;If the function is called on something that is not an ObjVal, it should throw an error.

;;this function named objectContains?, and this function can check the Json is or isnot a Object of json type. It is return the boolean.
;;type: bool

(define (objectContains? json str)
  (if (ObjVal? json)
      (objectContainsHelper? (eval json) str)
      (error "not ObjVal"))) 

(define (objectContainsHelper? json str)
  
      (if( empty? json)
         #f
         (if (equal? str (first(first json)))
             #t
             (objectContainsHelper? (rest  json)  str  )))
       
       )
             
              
  ;(if (empty? json)
     ;#f
      ;(if (equal? str (first (eval json)))
        ;#t
         ;(objectContains? str (rest (eval json))))))
(define Ob1 (ObjVal (list (StrJSONPair "\"No1\"" (NumVal 1)))) )
(define Ob2 (ObjVal (list (StrJSONPair "\"id\"" (StrVal "\"1\"")) (StrJSONPair "\"val\"" (StrVal "\"2\"")))))


;;2.Write a function getField which consumes a JSON Object and a field name and produces the JSON value corresponding to that field name (The type is JSON -> String -> JSON).
;;If the function is called on something that is not an ObjVal, it should thrown an error.


;(define (myeval json)
  ;(letrec (
          ; [checkjson (lambda (myjson)
                       ; (if empty? myjson)
                        
;;this function named getField, and this function can get the json value corresponding to that field name. It is return the json.
;;type: json

(define (getField json str)
  (if (ObjVal? json)
      (if (empty? (eval json))
          "null"
          (parsestr (~a (first (getFieldHelper (eval json) str)))))
      (error "not ObjVal")))  
       
(define (getFieldHelper json str)
  (if (empty? json)
      "null"
      (if (equal? (first (first json)) str)
                   (rest (first json))
                   (getFieldHelper (rest json) str))))

;;3.Write a function filterKeys which consumes a function of type (String -> Bool)  and a  JSON Object and then produces another JSON object.
;;This function will take a predicate function, and apply it to each (key, value) pair in the JSON object. If the predicate returns True, the pair is kept, else it is ignored.
;;The function will return a JSON object containing only those keys for which the predicate returned True.  If you call it on something that's not an ObjVal, it should throw an error. 

;;this function named filterKeys, and this function can  take a predicate function and each pair in the JSON object. If it is true ,it is return the json. It return the error if it is not ture.
;;type: json

(define (filterKeys predicate json)
  (if (ObjVal? json)
      (parsestr (beJson (filterKeysHelper predicate (eval json))))
      (error "not ObjVal"))) 

(define (filterKeysHelper predicate json)
  (if (empty? json)
    '()
    (if (predicate (first (first json)))
                   (append (list (first json)) (filterKeysHelper predicate (rest json)))
                   (filterKeysHelper predicate (rest json)))))


(define (beJson str)
  (if (empty? str)
    "null"
    (~a "{" (first (first str)) ":" (first (rest (first str))) "}")))
    
(define (test str)
  #t)

(define (test2 str)
  #f)
;;(define (predicate str)
;;  (equal? str ("id")
;;          #t
;;          #f))
  


;;4.Write a function keyCount which consumes a JSON Object and produces an integer. The function should produce the number of keys in the JSON object.
;;If you call it on something that is not an ObjVal, it should throw an error.

;;this function named keyCount, and this function can get number of keys in the JSON object. It is return the Number.
;;type: number

(define (keyCount json)
  (if (ObjVal? json)
      (keyCount (eval json))
      (if (list? json)
          (if (empty? json)
              0 
              (+ 1 (keyCount (rest json))))
          (error "not ObjVal"))))



;;5.Write a function keyList which consumes a JSON Object and produces a list of strings which contains all of the keys in the JSON structure.
;;If you call it on something that's not an ObjVal, it should throw an error.

;;this function named keyList, and this function can get all key in the JSON object. It is return list of key.
;;type: list
(define (keyList json)
  (if (ObjVal? json)
      (keyList (eval json))
      (if (list? json)
          (if(empty? json)
             '()
             (append (list(first(first json))) (keyList (rest json)) ) )
          (error "not ObjVal"))
       ))


;;6.Write a function arrayLength which consumes a JSON array and returns the number of elements contained in the array.
;;If you call it on something that's not an Array, it should throw an error.

;;this function named arrayLength, and this function can get the length of array in the JSON object. It is return number.
;;type: number
(define (arrayLength json)
  (if (Array? json)
      (arrayLength (eval json))
      (if (list? json)
          (if (empty? json)
              0
              (+ 1 (arrayLength (rest json))))
          (error "not Array"))))

(define Arr1 (parsestr "[1 ,2,3,4,6,5,6]"))
(define Arr2 (parsestr "[0,1,2,3,4,5,6,7]"))

;;7.Write a function filterRange that takes a low and a high value and a JSON Array and returns a JSON array only containing the range of elements between low and high.
;;For example, filterRange 2 3 (Array [NumVal 0, NumVal 1, NumVal 2, NumVal 3, NumVal 4]) should give you Array [NumVal 2.0, NumVal 3.0].
;;If you call it on something that's not a JSON Array, it should throw an error.

;;this function named filterRange, and this function can a array from low to high in the JSON object. It is return json array.
;;type: json
(define (filterRange array low high)
  (if (Array? array)
      (filterRange (eval array) low high)
      (if (list? array)
          (if (empty? array)
              0
              (parsestr (beJson2 (drop (drop-right array (-(- (length array) high) 1) ) low))))
          (error "not Array"))
      ))
      
(define (beJson2 alist)
  (if (empty? alist)
      "null"
      (~a "["   (first alist) ","   (beJson3 (rest alist)) "]")))
  
 (define (beJson3 alist)
  (if (= (length alist) 1)
      (first alist)
      (~a   (first alist) ","   (beJson3 (rest alist)) )))

;;(filterRange (parsestr "[0,1,2,3,4,5,6]") 3 5)
  
;;(define (filterRangeHelper array)
  ;;(if (empty? array)
    ;;'()
    ;;(if (predicate (first (first json)))
                ;;   (append (list (first json)) (filterKeysHelper predicate (rest json)))
                 ;;  (filterKeysHelper predicate (rest json)))))



;;8.Write a function filterArray which consumes a function of type (Any JSON Value -> Bool) and a JSON Array, and returns a JSON Array containing only those elements where the predicate function returns True.
;;If you call it on something that's not an Array, it should throw an error.

;;this function named filterArray, and this function can check function is or not true and return json array in the JSON object. It is return json array.
;;type: json
(define (filterArray predicate json)
  (if (Array? json)
      (parsestr (beJson2 (filterArrayHelper predicate (eval json))))
      (error "not Array"))) 

(define (filterArrayHelper predicate json)
  (if (empty? json)
    '()
    (if (predicate (first json))
                   (append (list (first json)) (filterArrayHelper predicate (rest json)))
                   (filterArrayHelper predicate (rest json)))))


;;9.Write a function extractElements that takes a JSON Array and a list of indices into the array, and returns a new array consisting only of those indices.
;;If you call it on something that's not an Array, it should throw an error.

;;this function named extractElements, and this function can get array and index in the JSON object, and to save array elements for index numbers. It is return json array.
;;type: json
(define (extractElements array index)
   (if (Array? array)
      (parsestr (beJson2 (extractElementsHelper array index)))
      (error "not Array")) 
  )
(define (extractElementsHelper array index)
  (if (Array? array)
      (extractElementsHelper (eval array) index)
      (if (list? array)
          (if (empty? index)
              '()
              (append (list (list-ref array (first index)))  (extractElementsHelper array (rest index)) ))
          (error "not Array"))))


;;(extractElements (parsestr "[1,2,3,4,5,6]") '(1 2 3 ))
;;(extractElements Arr1 '(1 4 3))
;;(extractElements Arr2 '(1 4 3))
;;(filterRange Arr2 2 5)
;;(filterArray test2 Arr2)

;;10.Write a function increasingIncidents that processes the JSON file to find all the diseases that have had increasing numbers of incidents since 2013 (the most recent data goes to 2018).
;;To do this, you must understand the layout of the data. Because 2018 is not complete, the numbers will be too few, thus only compare the earliest year, 2013, to 2017 for this problem.
;;Note that the data is listed by weeks and thus you may need to add up all the incidents for the various diseases. Your output must be something like:

;;this function named increasingIncidents , and this function can get JSON file then to find all the diseases that have had increasing numbers of incidents since 2013 to 2017. It is return compare result that is string
;;;;type: string

(define (extractElementsToList json list)
  (match (extractElements json list)
    [(Array '(emptyVal)) '()]
    [(Array lst) lst]))

(define (lineHelper line)
  (letrec
      ([data (extractElementsToList line '(8 17 25))])
       (if (> (list-ref data 2) (list-ref data 1))
           (printf "~a: ~a cases in 2013, ~a cases in 2017" (list-ref data 0) (list-ref data 1) (list-ref data 2))
           #f)
))

(define (increasingIncidents)
  (match (getField (parsefile "cdc2018.json") "data")
    [(Array lst) (map lineHelper lst)]))

;;11.Write a new function, strictlyIncreasing that returns only those diseases where the number of incidents has been monotonically increasing since 2013.
;;To determine if something is monotonically increasing, you should use (>=) to compare each year to the year before.

;;this function named strictlyIncreasing, and this function can get JSON file then to find all the diseases that have had increasing numbers of incidents since 2013 to 2017. It is return compare result that is string
;;;;type: string

(define (extractElementsToList2 json list)
  (match (extractElements json list)
    [(Array '(emptyVal)) '()]
    [(Array lst) lst]))

(define (lineHelper2 line)
  (letrec
      ([data (extractElementsToList2 line '(8 17 19 21 23 25))])
       (if (> (list-ref data 5)(list-ref data 4)(list-ref data 3)(list-ref data 2) (list-ref data 1) (list-ref data 0))
           (printf "~a: ~a cases in 2013, ~a cases in 2017" (list-ref data 0) (list-ref data 1) (list-ref data 2)(list-ref data 3)(list-ref data 4)(list-ref data 5))
           #f)
))

(define (strictlyIncreasing)
  (match (getField (parsefile "cdc2018.json") "data")
    [(Array lst) (map lineHelper2 lst)]))
