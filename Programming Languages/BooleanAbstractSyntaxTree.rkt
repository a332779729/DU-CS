#lang racket

(provide (all-defined-out))

;(struct boolean-value (value) #:transparent)
;(struct not-expr (arg) #:transparent)
;(struct or-expr (argOne argTwo) #:transparent)
;(struct and-expr (argOne argTwo) #:transparent)

(struct TrueVal (value) #:transparent)
(struct FalseVal (value) #:transparent)
(struct NullVal (value) #:transparent)
(struct StrVal (value) #:transparent)
(struct NumVal (value) #:transparent)

(struct StrJSONPair (string json) #:transparent) 
(struct ObjVal (list-of-strjsonpairs) #:transparent)
(struct Array (list-of-json-elements) #:transparent)