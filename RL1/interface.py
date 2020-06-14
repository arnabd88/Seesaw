
import ctypes

rp = ctypes.CDLL("libfoo.so")
rp.IBparser.argtypes = [ctypes.c_char_p]
rp.IBparsepred.argtypes = [ctypes.c_char_p]
rp.initializeRP.argtypes = [ctypes.c_char_p]

#returnValue = rp.IBparser(b"../benchmarks/satire_examples/z2d_1")
returnValue = rp.initializeRP(b"Variables x1 in [0.01, 1.0], x2 in [0.01, 1.0], x3 in [0.01, 1.0], x4 in [0.01, 1.0] ; Constraints min(0.4 - (x1 - x2), -0.25 + x3**2) <= 0,min(0.4 - (x1 - x2), 1.11577413974828e-14 - (-5.55111512312578e-17 + x4*(x3 + x2/x1)) + x1**2) <= 0;")

print(returnValue)
