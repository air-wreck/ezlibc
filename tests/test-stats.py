import unittest
import math
from ctypes import *

lib = CDLL('lib/ezlibc-stats.so')

def check_float(a, b, tolerance=0.0000001):
    # check floats a and b to be within tolerance
    return abs(a - b) < tolerance

class Test_EZ_Stats(unittest.TestCase):
    def test_normcdf(self):
        lib.ez_normcdf.argtypes = (c_double, c_double, c_double, c_double, c_double)
        lib.ez_normcdf.restype = c_double
        tol = 0.0000001
        self.assertTrue(check_float(0.989216838359, lib.ez_normcdf(3.5, 65, 42, 10, tol), tol))

if __name__ == '__main__':
    unittest.main()
