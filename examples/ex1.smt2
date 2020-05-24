;x4 = [0.01, 1.0];x3 = [0.01, 1.0];x2 = [0.01, 1.0];x1 = [0.01, 1.0];(x3^2 > 0.24999999999999994) && (x1 - x2 > 0.39999999999999997) && (x4*(x3 + x2/x1) - 5.55111512312578e-17 <= x1^2 + 1.11577413974828e-14) && ((x3^2 < 0.25000000000000006) || (x4*(x3 + x2/x1) + 5.55111512312578e-17 >= x1^2 - 1.11577413974828e-14));

(set-logic QF_NRA)

(declare-fun x1 () Real)
(declare-fun x2 () Real)
(declare-fun x3 () Real)
(declare-fun x4 () Real)
(declare-fun y_0 () Bool)
(declare-fun y_1 () Bool)
(declare-fun y_2 () Bool)
(declare-fun y_3 () Bool)
(declare-fun y_4 () Bool)

; Assertion in input intervals

(assert (and (>= x1 0.01) (<= x1 1.0)))
(assert (and (>= x2 0.01) (<= x2 1.0)))
(assert (and (>= x3 0.01) (<= x3 1.0)))
(assert (and (>= x4 0.01) (<= x4 1.0)))

(assert (= y_0 (> (* x3 x3) 0.24999999999999994)))

(assert (= y_1 (> (- x1 x2) 0.39999999999999997)))

(assert (= y_2 (< (- x1 x2) 0.4000000000000001)))

(assert (= y_3 (<= 
				(- (* x4 (+ x3 (/ x2 x1))) 5.55111512312578e-17)
				(+ (* x1 x1) 1.11577413974828e-14)
				)
		)
		)

(assert (= y_4 (or 
			   (< (* x3 x3) 0.25000000000000006)
			   (>=
			   (+ (* x4 (+ x3 (/ x2 x1))) 5.55111512312578e-17)
			   (- (* x1 x1) 1.11577413974828e-14)
			   )
			   ) ) )


(assert (and (and (and (and y_0 y_1) y_2) y_3) y_4))

(check-sat)
(get-model)
(exit)
