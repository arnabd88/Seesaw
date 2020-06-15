
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
rp.initializeRP.restype = ctypes.POINTER(ctypes.POINTER(Cintervals * 3)*numBoxes)
rp.initializeRP.argtypes = [ctypes.c_char_p]

#inStr = "Variables x1 in [0.01, 1.0], x2 in [0.01, 1.0], x3 in [0.01, 1.0], x4 in [0.01, 1.0] ; Constraints min(0.4 - (x1 - x2), -0.25 + x3**2) <= 0,min(0.4 - (x1 - x2), 1.11577413974828e-14 - (-5.55111512312578e-17 + x4*(x3 + x2/x1)) + x1**2) <= 0;"

#returnValue = rp.initializeRP(b"Variables x1 in [0.01, 1.0], x2 in [0.01, 1.0], x3 in [0.01, 1.0], x4 in [0.01, 1.0] ; Constraints min(0.4 - (x1 - x2), -0.25 + x3**2) <= 0,min(0.4 - (x1 - x2), 1.11577413974828e-14 - (-5.55111512312578e-17 + x4*(x3 + x2/x1)) + x1**2) <= 0;", numVars)

inStr = "Variables x1 in [0.01, 0.1], x2 in [0.01, 0.1], x3 in [0.01, 0.1] ;Constraints min(0.4 - (x1 - x2), -5.55111512312579e-20 - x3**3) <= 0;"

returnValue = rp.initializeRP(inStr.encode())


import sys

def analyze():
	
	try:
		for box in returnValue.contents:
			if box:
				print(box.contents)
				for var in box.contents:
					if var and var.name.decode()!="Garbage":
						print( var.name.decode(), var.x, var.y)
					else:
						return
				#	print(var.name)
				#	print(var.x)
				#	print(var.y)
	except:
		pass

analyze()
