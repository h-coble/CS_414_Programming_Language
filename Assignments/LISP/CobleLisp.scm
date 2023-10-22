#lang scheme

;GIVEN LIST
(define sample-list '( -8 9 4 5 -3 -1 2))

;FUNCTION 1
(define (sum-all lst)
    (define (helper lst sum)
      (cond
        ((null? lst) sum) ;If list is empty, return sum
        (else (helper (cdr lst) (+ sum (car lst)) ) ) ;else return car + return from iter of cdr
        ) 
      )
    
    (helper lst 0))

;FUNCTION TWO
(define (positive-only lst)
    (cond
      ((null? lst) '())
      ((> (car lst) 0) (cons (car lst) (positive-only (cdr lst)) ) ) 
    (else (positive-only (cdr lst)))))

;FUNCTION THREE
(define (negative-only lst)
    (cond
      ((null? lst) '())
      ((< (car lst) 0) (cons (car lst) (negative-only (cdr lst)))) 
    (else (negative-only (cdr lst)))))

;FUNCTION FOUR (USED FOR 5 AND 6)
(define (average lst)
  (define (count-help lst count)
    (cond
      ((null? lst) count)
      (else (count-help (cdr lst) (+ count 1)))))
  
  (/ (sum-all lst) (count-help lst 0)))



;PROGRAM PROBLEMS 1 - 6
(define (Program1)
(display (sum-all sample-list))
(newline)
(display (positive-only sample-list))
(newline)
(display (negative-only sample-list))
(newline)
(display (average sample-list))
(newline)
(display (average (positive-only sample-list)))
(newline)
(display (average (negative-only sample-list))))


;PROBLEM 7
(define (getprop lst prop)
   (cond
      ((null? lst) '())
      ((equal? (car lst) prop)  (car(cdr lst)) ) ;if property is found, return value
    (else (getprop (cdr(cdr lst)) prop) ))) ;lst is formatted prop, val, prop, val -> skip val to search for prop


;PROBLEM 8
(define (changeprop lst prop val)
        (cond
          ((null? lst) '())
          ((equal? (car lst) prop)   (cons (car lst) (cons val (cdr (cdr lst))) ))  ;if property is found, call func to replace it
          (else (cons (car lst) (cons (cadr lst) (changeprop (cdr (cdr lst)) prop val)))))) ;lst is formatted prop, val, prop, val -> skip val to search for prop

;PROBLEM 9
(define (addprop lst prop val)
  (cons prop (cons val lst)))

;PROPERTY LIST
(define (pl) '(Title Associate_Professor Department MCNS University ATSU Tenure Yes))

;PROGRAM PROBLEMS 7 - 9
(define (Program2)
  (display "Starting List: ")
  (display (pl))
  (newline)

  
  (display "Dept = Art: ")
  (display (changeprop (pl) 'Department 'ART))
  (newline)

  
  (display "New Title: ")
  (display (changeprop (pl) 'Title 'CLOWN))
  (newline)

  
  (display "Change a property not present: ")
  (display (changeprop (pl) 'Salary '8_Bajillion))

  (newline)
  (display "Add Salary to Property List: ")
  (display (addprop (pl) 'Salary 'TWO_MEASLY_CENTS))
  (newline)
  
  (display "Clown in Art Dept: ")
  (display (changeprop (changeprop (pl) 'Department 'ART) 'Title 'CLOWN)))

(display "Program1 (Problems 1 - 6)")
(newline)
(Program1)

(newline)
(newline)

(display "Program2 (Problems 7 - 9)")
(newline)
(Program2)
(newline)