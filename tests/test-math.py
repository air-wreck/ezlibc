# unit tests for lib/ezlibc-math.so
# gcc -std=c89 -fPIC -shared -o lib/ezlibc-math.so src/math.c

import unittest
import math
from ctypes import *

lib = CDLL('lib/ezlibc-math.so')

def check_float(a, b, tolerance=0.0000001):
    # check floats a and b to be within tolerance
    return abs(a - b) < tolerance

class Test_EZ_Math(unittest.TestCase):
    def test_int_abs(self):
        lib.ez_int_abs.argtypes = (c_int,)
        lib.ez_int_abs.restype = c_int
        self.assertEqual(65, lib.ez_int_abs(65))
        self.assertEqual(65, lib.ez_int_abs(-65))

    def test_f_abs(self):
        lib.ez_f_abs.argtypes = (c_double,)
        lib.ez_f_abs.restype = c_double
        self.assertTrue(check_float(65.82, lib.ez_f_abs(65.82)))
        self.assertTrue(check_float(65.82, lib.ez_f_abs(-65.82)))

    def test_f_mod(self):
        lib.ez_f_mod.argtypes = (c_double, c_double)
        lib.ez_f_mod.restype = c_double
        self.assertTrue(check_float(1.1, lib.ez_f_mod(3.7, 1.3)))
        self.assertTrue(check_float(0.2, lib.ez_f_mod(-3.7, 1.3)))
        self.assertTrue(check_float(-0.2, lib.ez_f_mod(3.7, -1.3)))
        self.assertTrue(check_float(-1.1, lib.ez_f_mod(-3.7, -1.3)))

    def test_round(self):
        lib.ez_round.argtypes = (c_double,)
        lib.ez_round.restype = c_int
        self.assertEqual(65, lib.ez_round(65.12))
        self.assertEqual(65, lib.ez_round(64.52))
        self.assertEqual(-65, lib.ez_round(-65.36))
        self.assertEqual(-65, lib.ez_round(-64.82))

    def test_floor(self):
        lib.ez_floor.argtypes = (c_double,)
        lib.ez_floor.restype = c_int
        self.assertEqual(65, lib.ez_floor(65.82))
        self.assertEqual(-65, lib.ez_floor(-64.12))

    def test_ceil(self):
        lib.ez_ceil.argtypes = (c_double,)
        lib.ez_ceil.restype = c_int
        self.assertEqual(65, lib.ez_ceil(64.12))
        self.assertEqual(-65, lib.ez_ceil(-65.82))

    def test_fact(self):
        lib.ez_fact.argtypes = (c_int,)
        lib.ez_fact.restype = c_int
        self.assertEqual(120, lib.ez_fact(5))

    def test_nCr(self):
        lib.ez_nCr.argtypes = (c_int, c_int)
        lib.ez_nCr.restype = c_int
        self.assertEqual(10, lib.ez_nCr(5, 2))

    def test_nPr(self):
        lib.ez_nPr.argtypes = (c_int, c_int)
        lib.ez_nPr.restype = c_int
        self.assertEqual(20, lib.ez_nPr(5, 2))

    def test_ln(self):
        lib.ez_ln.argtypes = (c_double, c_double)
        lib.ez_ln.restype = c_double
        self.assertTrue(
            check_float(math.log(65.82),
                lib.ez_ln(65.82, 0.00001),
                tolerance=0.00001))

    def test_log_b(self):
        lib.ez_log_b.argtypes = (c_double, c_double, c_double)
        lib.ez_log_b.restype = c_double
        self.assertTrue(
            check_float(math.log(99.24, 64.82),
                lib.ez_log_b(64.82, 99.24, 0.00000000001),
                tolerance=0.00000000001))

    def test_int_exp_b(self):
        lib.ez_int_exp_b.argtypes = (c_double, c_int)
        lib.ez_int_exp_b.restype = c_double
        self.assertTrue(
            check_float(0.53 ** 3, lib.ez_int_exp_b(0.53, 3)))

    def test_exp(self):
        lib.ez_exp.argtypes = (c_double, c_double)
        lib.ez_exp.restype = c_double
        self.assertTrue(
            check_float(math.e ** -0.137,
                lib.ez_exp(-0.137, 0.00000001),
                tolerance=0.00000001))
        self.assertTrue(
            check_float(math.e ** 6.582,
                lib.ez_exp(6.582, 0.00000001),
                tolerance=0.00000001))

    def test_exp_b(self):
        # investigate if bignum failures are algorithmic or just a
        # machine precision limitation
        lib.ez_exp_b.argtypes = (c_double, c_double, c_double)
        lib.ez_exp_b.restype = c_double
        self.assertTrue(
            check_float(1.5 ** 2.3,
                lib.ez_exp_b(1.5, 2.3, 0.000000001),
                tolerance=0.000000001))

    def test_sin(self):
        lib.ez_sin.argtypes = (c_double, c_double)
        lib.ez_sin.restype = c_double
        self.assertTrue(
            check_float(math.sin(65.82),
                lib.ez_sin(65.82, 0.0000001),
                tolerance=0.0000001))

    def test_cos(self):
        lib.ez_cos.argtypes = (c_double, c_double)
        lib.ez_cos.restype = c_double
        self.assertTrue(
            check_float(math.cos(65.82),
                lib.ez_cos(65.82, 0.0000001),
                tolerance=0.0000001))

    def test_tan(self):
        lib.ez_tan.argtypes = (c_double, c_double)
        lib.ez_tan.restype = c_double
        self.assertTrue(
            check_float(math.tan(65.82),
                lib.ez_tan(65.82, 0.00000001),
                tolerance=0.00000001))

    def test_asin(self):
        lib.ez_asin.argtypes = (c_double, c_double)
        lib.ez_asin.restype = c_double
        self.assertTrue(
            check_float(math.asin(0.65),
                lib.ez_asin(0.65, 0.00000001),
                tolerance=0.00000001))

    def test_acos(self):
        lib.ez_acos.argtypes = (c_double, c_double)
        lib.ez_acos.restype = c_double
        self.assertTrue(
            check_float(math.acos(0.65),
                lib.ez_acos(0.65, 0.00000001),
                tolerance=0.00000001))

    def test_atan(self):
        lib.ez_atan.argtypes = (c_double, c_double)
        lib.ez_atan.restype = c_double
        self.assertTrue(
            check_float(math.atan(65.82),
                lib.ez_atan(65.82, 0.00000001),
                tolerance=0.00000001))
        self.assertTrue(
            check_float(math.atan(0.6582),
                lib.ez_atan(0.6582, 0.00000001),
                tolerance=0.00000001))

    def test_sqrt(self):
        lib.ez_sqrt.argtypes = (c_double, c_double)
        lib.ez_sqrt.restype = c_double
        self.assertTrue(
            check_float(math.sqrt(12.25),
                lib.ez_sqrt(12.25, 0.000000001),
                tolerance=0.000000001))

if __name__ == '__main__':
    unittest.main()
