

from dreal import *
x4 = Variable("x4")
x3 = Variable("x3")
x2 = Variable("x2")
x1 = Variable("x1")

f_sat = And(0.01 <= x4, x4 <= 1.0,
            0.01 <= x3, x3 <= 1.0,
            0.01 <= x2, x2 <= 1.0,
            0.01 <= x1, x1 <= 1.0,
            (x1 - x2 >= 0.4) and ((x3*x3 > 0.25) and (x4*(x3 + x2/x1) <= x1*x1)) and (((x1*x3 <x2))or((x2>=x4))) and ((((x4 <x1 + x3))and((x2 + x4 <x3*x3)))or((x2 <x4))))

result = CheckSatisfiability(f_sat, 0.001)
print(result)

