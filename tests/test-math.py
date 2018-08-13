# unit tests for lib/ezlibc-math.so

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
        self.assertTrue(
            check_float(65.82, lib.ez_f_abs(65.82))
        )
        self.assertTrue(
            check_float(65.82, lib.ez_f_abs(-65.82))
        )

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

    def test_ln(self):
        lib.ez_ln.argtypes = (c_double, c_double)
        lib.ez_ln.restype = c_double
        self.assertTrue(
            check_float(4.18692374352, lib.ez_ln(65.82, 0.00001),
                tolerance=0.00001)
        )

    @unittest.skip('we need to fix compounded error later')
    def test_log_b(self):
        lib.ez_log_b.argtypes = (c_double, c_double, c_double)
        lib.ez_log_b.restype = c_double
        self.assertTrue(
            check_float(1.098071386168515799539836,
                lib.ez_log_b(64.82, 99.24, 0.0000001),
                tolerance=0.0000001
            )
        )

    def test_int_exp_b(self):
        lib.ez_int_exp_b.argtypes = (c_double, c_int)
        lib.ez_int_exp_b.restype = c_double
        self.assertTrue(
            check_float(0.148877, lib.ez_int_exp_b(0.53, 3))
        )

    def test_exp(self):
        lib.ez_exp.argtypes = (c_double, c_double)
        lib.ez_exp.restype = c_double
        self.assertTrue(
            check_float(721.981849948,
                lib.ez_exp(6.582, 0.00000001),
                tolerance=0.00000001
            )
        )

    @unittest.skip('fix compounded error later')
    def test_exp_b(self):
        lib.ez_exp_b.argtypes = (c_double, c_double, c_double)
        lib.ez_exp_b.restype = c_double
        self.assertTrue(
            check_float(4633290.43424,
                lib.ez_exp_b(6.5, 8.2, 0.00001),
                tolerance=0.00001
            )
        )

    def test_sin(self):
        lib.ez_sin.argtypes = (c_double, c_double)
        lib.ez_sin.restype = c_double
        self.assertTrue(
            check_float(math.sin(65.82),
                lib.ez_sin(65.82, 0.0000001),
                tolerance=0.0000001
            )
        )

    def test_cos(self):
        lib.ez_cos.argtypes = (c_double, c_double)
        lib.ez_cos.restype = c_double
        self.assertTrue(
            check_float(math.cos(65.82),
                lib.ez_cos(65.82, 0.0000001),
                tolerance=0.0000001
            )
        )

    def test_tan(self):
        lib.ez_tan.argtypes = (c_double, c_double)
        lib.ez_tan.restype = c_double
        self.assertTrue(
            check_float(math.tan(65.82),
                lib.ez_tan(65.82, 0.0000001),
                tolerance=0.0000001
            )
        )

if __name__ == '__main__':
    unittest.main()
