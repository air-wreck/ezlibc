# trying to unit test ezlibc-math.so through Python
# it is not going well
import ctypes

_math = ctypes.CDLL('lib/ezlibc-math.so')
_math.ez_sin.argtypes = (ctypes.c_double, ctypes.c_double)

res = _math.ez_sin(ctypes.c_double(1.0), ctypes.c_double(0.00001))
print type(res)  # this returns 4???

a = ctypes.c_double(0.00001)
print a.value
