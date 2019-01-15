import unittest
import math
from ctypes import *

libmath = CDLL('lib/ezlibc-math.so')  # for speed comparison
libqmath = CDLL('lib/ezlibc-qmath.so')

# check two floats
def check_float(a, b, tolerance=0.001):
    return abs(a - b) < tolerance

class Test_EZ_QMath(unittest.TestCase):
    def test_qsqrt(self):
        libqmath.ez_qsqrt.argtypes = (c_double,)
        libqmath.ez_qsqrt.restype = c_double
        libmath.ez_sqrt.argtypes = (c_double,)
        libmath.ez_sqrt.restype = c_double
        print math.sqrt(13482), libmath.ez_sqrt(13482), libqmath.ez_qsqrt(13482)
        self.assertTrue(
            check_float(math.sqrt(13482), libqmath.ez_qsqrt(13482)))

if __name__ == '__main__':
    unittest.main()
