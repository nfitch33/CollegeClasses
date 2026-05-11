(let f (-> float float)
  (rec f (-> float float)
    (fun n float
      (if (< n 1)
         0
         (+ n (f (- n 1))))))
  (f 10))
