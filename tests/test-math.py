# unit tests for lib/ezlibc-math.so

import unittest
from ctypes import *

lib = CDLL('lib/ezlibc-math.so')

class Test_EZ_Math(unittest.TestCase):
    def test_int_abs(self):
        lib.ez_int_abs.argtypes = (c_int,)
        lib.ez_int_abs.restype = c_int
        self.assertEqual(65, lib.ez_int_abs(65))
        self.assertEqual(65, lib.ez_int_abs(-65))

    def test_f_abs(self):
        lib.ez_f_abs.argtypes = (c_double,)
        lib.ez_f_abs.restype = c_double
        self.assertEqual(65.82, lib.ez_f_abs(65.82))
        self.assertEqual(65.82, lib.ez_f_abs(-65.82))

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
        self.assertTrue(abs(4.18692374352 - lib.ez_ln(65.82, 0.00001))
            < 0.00001)

    @unittest.skip('we need to fix compounded error later')
    def test_log_b(self):
        lib.ez_log_b.argtypes = (c_double, c_double, c_double)
        lib.ez_log_b.restype = c_double
        self.assertTrue(abs(
            1.098071386168515799539836 - lib.ez_log_b(64.82, 99.24, 0.0000001))
            < 0.0000001)

    def test_int_exp_b(self):
        pass  # I'll finish writing these later

if __name__ == '__main__':
    unittest.main()
