;NUMBER FOUR
(define (length-of-tail lst)
  (define (length-iter lst acc)
    (if (null? lst)
        acc
        (length-iter (cdr lst) (+ 1 acc))))
  (length-iter lst 0))

;NUMBER FIVE
(define (max-int lst)
  (define (helper lst current-max)
    (cond 
          ((null? lst) current-max)
     ((> (car lst) current-max) (helper (cdr lst) (car lst)))
    (else (helper (cdr lst) current-max))))

  (if (null? lst)
      (error "The list is empty")
      (helper (cdr lst) (car lst))))

;NUMBER SIX
(define (min-int lst)
  (define (helper lst current-min)
    (cond 
          ((null? lst) current-min)
     ((< (car lst) current-min) (helper (cdr lst) (car lst)))
    (else (helper (cdr lst) current-min))))

  (if (null? lst)
      (error "The list is empty")
      (helper (cdr lst) (car lst))))

;NUMBER SEVEN
(define (position-in-list atom lst)
  (define (iter lst index)
    (cond
        ((null? lst) 'NIL)
        ((eq? (car lst) atom) index)
        (else (iter (cdr lst) (+ index 1)))))

    (iter lst 0))

;NUMBER EIGHT
(define (merge-lists list1 list2)
  (cond
   ((null? list1) list2)
   ((null? list2) list1)
   ((<(car list1) (car list2))
    (cons (car list1) (merge-lists (cdr list1) list2)))
   (else 
    (cons (car list2) (merge-lists list1 (cdr list2))))))

;NUMBER NINE
(define (flatten-list lst)
  (cond
    ((null? lst) '()) 
    ((list? (car lst))
     (append (flatten-list (car lst)) (flatten-list (cdr lst))))
    (else
     (cons (car lst) (flatten-list (cdr lst))))))

;NUMBER TEN
(define (take lst n)
  (if (= n 0)
      '()
      (if (null? lst)
          '()
          (cons (car lst) (take (cdr lst) (- n 1))))))

(define (drop lst n)
  (if (= n 0)
      lst
      (if (null? lst)
          '()
          (drop (cdr lst) (- n 1)))))

(define (rotate-list lst n)
  (if (= n 0)
      lst
      (let* ((len (length lst))
             (mod-n (modulo n len))
             (first-part (take lst mod-n))
             (second-part (drop lst mod-n)))
        (append second-part first-part))))

;NUMBER ELEVEN
(define (atom-counter lst)
  (cond
    ((null? lst) 0)
    ((not (list? (car lst))) 
     (+ 1 (atom-counter (cdr lst))))
    (else
     (+ (atom-counter (car lst)) (atom-counter (cdr lst))))))

;NUMBER TWELVE
(define (drop-every-nth lst n)
  (define (helper lst count)
    (cond
      ((null? lst) '()) 
      ((= count n) (helper (cdr lst) 1)) 
      (else (cons (car lst) (helper (cdr lst) (+ 1 count)))))) 

(helper lst 1))