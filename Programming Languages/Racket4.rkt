#lang racket


(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide (all-defined-out))

(define-empty-tokens bool-values (TRUE FALSE))

;(define-empty-tokens parens (LEFTPAREN RIGHTPAREN))

(define-empty-tokens bool-operators (AND OR NOT))



(define-empty-tokens parens (LEFTPAREN RIGHTPAREN))
(define-empty-tokens lambda-def (LAMBDA DOT)) 
(define-empty-tokens end-of-file(EOF))

(define-tokens names (IDENTIFIER))

(define mylexer
  (lexer
   [#\(                      (token-LEFTPAREN)]
   [#\)                      (token-RIGHTPAREN)]
   [#\.                      (token-DOT)]
   ;["foo fifi"               (token-DOT)]
   [(:or #\λ "lambda")       (token-LAMBDA)]
   ;[:or "and" "And" "AND"]   (token-AND)
   ;["or"                     (token-OR)]
   ;["not"                    (token-NOT)]
   ;["true"                   (token-TRUE)]
   ;["false"                  (token-FALSE)]
   [(:: (:* alphabetic) (:*  (:or numeric alphabetic)))
                     (token-IDENTIFIER  lexeme)]
   [(:+ numeric (token-NUMBER lexeme))]
   [whitespace               (mylexer input-port)]
   [(eof)                    (token-EOF)]
   ))
  

;(define (lex in)
 ; (let ([tokenizer (get-tokenizer in)])
  ;  (cond
   ;   [(eq? tok (token-EOF)) null]
    ;  [else (cons tok (lex-functino))])))


(define (get-tokenizer in)
  (λ () (mylexer in)))

(define (lexer in)
  (let ([tokenizer (get-tokenizer in)])
    (define (lex-function)
      (let ([tok (tokenizer)])
        (cond
          [(eq? tok (token-EOF)) null]
          [else (cons tok (lex-functino))])))
    (lex-function)))

(define (lexstr str)
  (lex (open-input-string str)))

(define example (open-input-string "(not true)"))
   
   