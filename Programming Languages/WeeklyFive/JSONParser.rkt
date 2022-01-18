#lang racket

;; comments:This Parser is from Sun.

(require parser-tools/yacc
         (prefix-in lex: parser-tools/lex)
         "JSONLexer.rkt"
         "JSONAbstractSyntaxTree.rkt")
(require test-engine/racket-tests)

(provide (all-defined-out))

(define myparser
  (parser
      (start expr)
      (end EOF)
      (tokens lambda-def
              sign-value
              null-values
              bool-values
              parens
              bool-operators
              end-of-file
              names-and-value)
      (error (lambda (tok-ok? tok-name tok-value)
               (printf "Parser error: token ~a value ~a"
                           tok-name
                           tok-value)))
      (grammar
          (expr [(TRUE)                               (TrueVal true)]
                [(FALSE)                              (FalseVal false)]
                [(NULL)                               (NullVal null)]
                [(STRING)                             (StrVal $1)]
                [(NUMBER)                             (NumVal $1)]
                [(LEFTBRACKET elems RIGHTBRACKET)     (Array $2)]
                [(LEFTBRACE members RIGHTBRACE)       (ObjVal $2)])

          (elems [( )                                 (emptyVal )]
                 [(expr)                              (list $1)]
                 [(elems COMMA elems)                 (cons $1 $3)])

          (member
                   [( )                               (emptyVal )]
                   [(STRING COLON expr)                (StrJSONPair $1 $3)])

          (members 
                   [(member)                          (list $1)]
                   [(member COMMA members)            (cons $1 $3)])
                   
          )


          ))

(define (parse in)
  (myparser (get-tokenizer in)))

(define (parsestr str)
  (let ([in (open-input-string str)])
    (parse in)))

(define (parsefile filename)
  (let ([in (open-input-file filename)])
    (parse in)))

(check-expect (parsestr "true") (TrueVal #t))
(check-expect (parsestr "false") (FalseVal #f))
(check-expect (parsestr "null") (NullVal '()))
(check-expect (parsestr "2019") (NumVal "2019"))
(check-expect (parsestr "20.19") (NumVal "20.19"))
(check-expect (parsestr "20.19E-114") (NumVal "20.19E-114"))
(check-expect (parsestr "20.19e114") (NumVal "20.19e114"))
(check-expect (parsestr "\"Love Programming Language\"") (StrVal "\"Love Programming Language\""))
(check-expect (parsestr "\"Fall 2019\"") (StrVal "\"Fall 2019\""))
(check-expect (parsestr "\"(true)\"") (StrVal "\"(true)\""))
(check-expect (parsestr "[true]") (Array (list (TrueVal #t))))

