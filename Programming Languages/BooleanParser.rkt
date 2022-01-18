#lang racket

(require test-engine/racket-tests)

(require parser-tools/yacc
         (prefix-in lex: parser-tools/lex)
         "JSONLexer.rkt"
         "BooleanAbstractSyntaxTree.rkt")

(provide (all-defined-out))

(define myparser
  (parser
      (start expr)
      (end EOF)
      (tokens bool-values     ;true false
              null-values     ;null
              string          ;a string, surrounded by double quotes and allowing some escaped characters
              number          ;a number, represented as a floating point value
              parens          
              bool-operators
              lambda-def
              comma
              colon
              end-of-file)
      (error (lambda (tok-ok? tok-name tok-value)
               (printf "Parser error: token ~a value ~a"
                           tok-name
                           tok-value)))
      (grammar
          (expr [(TRUE)                               (TrueVal true)]
                [(FALSE)                              (FalseVal false)]
                [(NULL)                               (NullVal null)]
                ;a string, surrounded by double quotes and allowing some escaped characters
                [(STRING)                             (StrVal $1)]
                ;a number, represented as a floating point value
                [(NUMBER)                             (NumVal $1)]
                ;this is the list
                [(expr COMMA expr)                    (cons $1 $3)]
                [(expr COLON expr)                             (StrJSONPair $1 $3)]
                ;an "object", which is surrounded by braces and is a list of field/value pairs, separated by commas with a colon between the field and value.
                ;The field name is always a string literal, while the value can be any legal JSON value.
                [(LEFTBRACKET expr RIGHTBRACKET)               (ObjVal $2)]
                ;an array of JSON values, surrounded by brackets and with the values separated by commas
                [(LEFTBRACE expr RIGHTBRACE)                   (Array $2)] 

            )
        
          )))

(define (parse in)
  (myparser (get-tokenizer in)))

(define (parsestr str)
  (let ([in (open-input-string str)])
    (parse in)))

;;Write Racket programs that read from files.

;;this function named parsefile, and this function can read the file. It is return the file.
;;type: file
(define (parsefile filename)
  (let ([in (open-input-file filename)])
    (parse in)))

;this is test for true false null
(check-expect (parsestr "true") (TrueVal #t))
(check-expect (parsestr "false") (FalseVal #f))
(check-expect (parsestr "null")  (NullVal '()))
;this is test number
(check-expect (parsestr "1") (NumVal "1"))
(check-expect (parsestr "123") (NumVal "123"))
;this is test string
(check-expect (parsestr "\"a\"") (StrVal "\"a\""))
(check-expect (parsestr "\"abc\"") (StrVal "\"abc\""))
;this is test the list array StrJSONPair object
(check-expect (parsestr "1, 2, 3") (list* (NumVal "1") (NumVal "2") (NumVal "3")))
(check-expect (parsestr "[1, 2, 3]") (Array (list* (NumVal "1") (NumVal "2") (NumVal "3"))))
(check-expect (parsestr "{\"id\":\"1\", \"id2\":\"2\"}") (ObjVal (StrJSONPair (StrVal "\"id\"") (cons (StrVal "\"1\"") (StrJSONPair (StrVal "\"id2\"") (StrVal "\"2\""))))))
(check-expect (parsestr "{\"id\":{\"test\"}}") (ObjVal (StrJSONPair (StrVal "\"id\"") (ObjVal (StrVal "\"test\"")))))
(check-expect (parsestr "{\"id\":[1,2,3]}") (ObjVal (StrJSONPair (StrVal "\"id\"") (Array (list* (NumVal "1") (NumVal "2") (NumVal "3"))))))
(test)