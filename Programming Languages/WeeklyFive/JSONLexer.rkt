#lang racket

;; comments:This file is from Sun.

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))
(require test-engine/racket-tests)

(provide (all-defined-out))

(define-empty-tokens null-values (NULL))
(define-empty-tokens end-of-file (EOF))
(define-empty-tokens sign-value (SIGN))
(define-empty-tokens bool-values (TRUE FALSE))
(define-empty-tokens lambda-def (LAMBDA DOT QUOTE COMMA COLON))
(define-empty-tokens bool-operators (AND OR NOT))
(define-empty-tokens parens (LEFTPAREN
                             RIGHTPAREN
                             LEFTBRACE
                             RIGHTBRACE
                             LEFTBRACKET
                             RIGHTBRACKET))

(define-tokens names-and-value (NUMBER STRING ARRAY OBJECT))

(define mylexer
  (lexer
   [(eof)                                                                                       (token-EOF)]
   [whitespace                                                                                  (mylexer input-port)]
   [#\.                                                                                         (token-DOT)]
   [#\,                                                                                         (token-COMMA)]
   [#\"                                                                                         (token-QUOTE)]
   [#\:                                                                                         (token-COLON)]
   [(:or #\λ "lambda")                                                                          (token-LAMBDA)]
   [#\[                                                                                         (token-LEFTBRACKET)]
   [#\]                                                                                         (token-RIGHTBRACKET)]
   [#\{                                                                                         (token-LEFTBRACE)]
   [#\}                                                                                         (token-RIGHTBRACE)]
   [#\(                                                                                         (token-LEFTPAREN)]
   [#\)                                                                                         (token-RIGHTPAREN)]

   ["true"                                                                                      (token-TRUE)]
   ["false"                                                                                     (token-FALSE)]
   ["null"                                                                                      (token-NULL)]

   [(:: (:: #\" (:+ (:or (complement (:: (:* any-string) #\" (:* any-string)))) (:: #\\ #\") ) #\"))
                                                                                                (token-STRING lexeme)]

   [(:or "" #\+ #\-)                                                                            (token-SIGN)]
   ;[(:or (char-range #\1 #\9))                                                                  (token-ONENINE (string->number lexeme))]    
   ;[(:or #\0 (char-range #\1 #\9))                                                              (token-DIGIT (string->number lexeme))]
   ;[(:+ (:or #\0 (char-range #\1 #\9)))                                                         (token-DIGITS (string->number lexeme))]

   ;[(:or "" (:: (:+ (:or #\0 (char-range #\1 #\9))) #\. (:+ (:or #\0 (char-range #\1 #\9)))))   (token-FRACTION (string->number lexeme))]
   ;[(:or (:or #\0 (char-range #\1 #\9)) (:: (char-range #\1 #\9) (:+ (:or #\0 (char-range #\1 #\9))))
   ;      (:: #\- (:or #\0 (char-range #\1 #\9))) (:: #\- (char-range #\1 #\9) (:+ (:or #\0 (char-range #\1 #\9)))))
   ;                                                                                             (token-INTEGER lexeme)]
   ;[(:or "" (:: "E" (:or "" #\+ #\-) (:+ (:or #\0 (char-range #\1 #\9))))
   ;         (:: "e" (:or "" #\+ #\-) (:+ (:or #\0 (char-range #\1 #\9)))))                      (token-EXPONENT lexeme)]
   [(:or (:or (:or #\0 (char-range #\1 #\9)) (:: (char-range #\1 #\9) (:+ (:or #\0 (char-range #\1 #\9))))
         (:: #\- (:or #\0 (char-range #\1 #\9))) (:: #\- (char-range #\1 #\9) (:+ (:or #\0 (char-range #\1 #\9)))))
         (:or "" (:: (:* (:or #\0 (char-range #\1 #\9))) #\. (:+ (:or #\0 (char-range #\1 #\9)))))
         (:or "" (:: (:* (:or #\0 (char-range #\1 #\9))) (:* (:: #\. (:+ (:or #\0 (char-range #\1 #\9))))) "E" (:or "" #\+ #\-) (:+ (:or #\0 (char-range #\1 #\9))))
                 (:: (:* (:or #\0 (char-range #\1 #\9))) (:* (:: #\. (:+ (:or #\0 (char-range #\1 #\9))))) "e" (:or "" #\+ #\-) (:+ (:or #\0 (char-range #\1 #\9))))))
                                                                                                (token-NUMBER lexeme)]
   ))

(define (get-tokenizer in)
  (lambda () (mylexer in)))

(define (lex in)
  (let ([tokenizer (get-tokenizer in)])
    (define (lex-function)
              (let ([tok (tokenizer)])
                   (cond
                      [(eq? tok (token-EOF)) null]
                      [else (cons tok (lex-function))])))
    (lex-function)))

(define (lexstr str)
  (lex (open-input-string str)))

(define (lexerfile filename)
  (let ([in (open-input-file filename)])
     (lex in)))

(define (lexfile filename)
  (lex (open-input-file filename)))

(check-expect (mylexer (open-input-string "+")) 'SIGN)
(check-expect (mylexer (open-input-string "false")) 'FALSE)
(check-expect (mylexer (open-input-string "true")) 'TRUE)
(check-expect (mylexer (open-input-string "1")) (token-NUMBER 1))
(check-expect (mylexer (open-input-string "2003")) (token-NUMBER 2003))
(check-expect (mylexer (open-input-string "\"he234sdaf\"")) (token-STRING "\"he234sdaf\""))
(check-expect (mylexer (open-input-string "\"11\"")) (token-STRING "\"11\""))
(check-expect (mylexer (open-input-string "null")) 'NULL)
(check-expect (mylexer (open-input-string "13.46")) (token-NUMBER "13.46"))
(check-expect (mylexer (open-input-string "-1118")) (token-NUMBER "-1118"))
(check-expect (mylexer (open-input-string "123E-1118")) (token-NUMBER "123E-1118"))
(check-expect (mylexer (open-input-string "1.1E-1118")) (token-NUMBER "1.1E-1118"))
(check-expect (mylexer (open-input-string "1E-1118")) (token-NUMBER "1E-1118"))
(check-expect (mylexer (open-input-string ".66")) (token-NUMBER ".66"))
(check-expect (lexstr "[ \"hahaha\", true, false, null, 0.66, 1E-12, 356, null, \"ads\" ]") (list 'LEFTBRACKET (token-STRING "\"hahaha\"") 'COMMA 'TRUE 'COMMA 'FALSE 'COMMA 'NULL 'COMMA (token-NUMBER "0.66") 'COMMA (token-NUMBER "1E-12") 'COMMA (token-NUMBER "356") 'COMMA 'NULL 'COMMA (token-STRING "\"ads\"") 'RIGHTBRACKET))
(check-expect (lexstr "[ \"hahaha\", true ]") (list 'LEFTBRACKET (token-STRING "\"hahaha\"") 'COMMA 'TRUE 'RIGHTBRACKET))
(check-expect (lexstr " { \"name\" : 123} ") (list 'LEFTBRACE (token-STRING "\"name\"") 'COLON (token-NUMBER "123") 'RIGHTBRACE))

;(string->number "123")