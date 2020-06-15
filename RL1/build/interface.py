
import ctypes

#rp = ctypes.CDLL("libfoo.so")
#rp.IBparser.argtypes = [ctypes.c_char_p]
#rp.IBparsepred.argtypes = [ctypes.c_char_p]
#rp.initializeRP.argtypes = [ctypes.c_char_p]
#
##returnValue = rp.IBparser(b"../benchmarks/satire_examples/z2d_1")
#returnValue = rp.initializeRP(b"Variables x1 in [0.01, 1.0], x2 in [0.01, 1.0], x3 in [0.01, 1.0], x4 in [0.01, 1.0] ; Constraints min(0.4 - (x1 - x2), -0.25 + x3**2) <= 0,min(0.4 - (x1 - x2), 1.11577413974828e-14 - (-5.55111512312578e-17 + x4*(x3 + x2/x1)) + x1**2) <= 0;")
#
#print(returnValue)

class Cintervals(ctypes.Structure):
	_fields_ = ("name", ctypes.c_char_p), ("x", ctypes.c_double), ("y", ctypes.c_double)

numVars = 4;
numBoxes = 10;


rp = ctypes.CDLL("libfoo.so")
rp.initializeRP.restype = ctypes.POINTER(ctypes.POINTER(Cintervals * numVars)*numBoxes)
rp.initializeRP.argtypes = [ctypes.c_char_p, ctypes.c_int]

returnValue = rp.initializeRP(b"Variables x1 in [0.01, 1.0], x2 in [0.01, 1.0], x3 in [0.01, 1.0], x4 in [0.01, 1.0] ; Constraints min(0.4 - (x1 - x2), -0.25 + x3**2) <= 0,min(0.4 - (x1 - x2), 1.11577413974828e-14 - (-5.55111512312578e-17 + x4*(x3 + x2/x1)) + x1**2) <= 0;", numVars)

for box in returnValue.contents:
	for var in box.contents:
		print("==========")
		print(var.name)
		print(var.x)
		print(var.y)

