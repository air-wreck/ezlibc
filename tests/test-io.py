# unit tests for lib/ezlibc-io.so

import unittest, subprocess

# RIP...can't open an -m32 executable in 64-bit Python
# except I wrote all the assembly for 32-bit x86
# so, we'll instead write C driver programs in ./io-driver
# each program will wrap one function
# it will accept that function's arguments through the file args
# it will return that function's return value on stdout???
# then we can just run the binary and redirect stdin/out/err

class Test_EZ_IO(unittest.TestCase):
    def test_print(self):
        with open('tests/io-driver/stdout_dummy', 'r+') as stdout_f:
            self.assertEqual(13, subprocess.call(
                ['tests/io-driver/ez_print.out', 'Hello World!\n', '13'],
                    stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), 'Hello World!\n')
            stdout_f.seek(0)
            stdout_f.truncate()

    def test_str_print(self):
        with open('tests/io-driver/stdout_dummy', 'r+') as stdout_f:
            self.assertEqual(15,
                subprocess.call(['tests/io-driver/ez_str_print.out',
                    'Goodbye World!\n'], stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), 'Goodbye World!\n')
            stdout_f.seek(0)
            stdout_f.truncate()

    def test_int_print(self):
        with open('tests/io-driver/stdout_dummy', 'r+') as stdout_f:
            self.assertEqual(3,
                subprocess.call(['tests/io-driver/ez_int_print.out',
                    '65'], stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), '+65')
            stdout_f.seek(0)
            stdout_f.truncate()
            self.assertEqual(3,
                subprocess.call(['tests/io-driver/ez_int_print.out',
                    '-65'], stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), '-65')
            stdout_f.seek(0)
            stdout_f.truncate()

    def test_str10_to_int(self):
        # honestly, this is basically the same as test_int_print
        with open('tests/io-driver/stdout_dummy', 'r+') as stdout_f:
            self.assertEqual(3,
                subprocess.call(['tests/io-driver/ez_str10_to_int.out', '65'],
                    stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), '+65')
            stdout_f.seek(0)
            stdout_f.truncate()
            self.assertEqual(3,
                subprocess.call(['tests/io-driver/ez_str10_to_int.out', '+65'],
                    stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), '+65')
            stdout_f.seek(0)
            stdout_f.truncate()
            self.assertEqual(3,
                subprocess.call(['tests/io-driver/ez_str10_to_int.out', '-65'],
                    stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), '-65')
            stdout_f.seek(0)
            stdout_f.truncate()
            self.assertEqual(2,
                subprocess.call(['tests/io-driver/ez_str10_to_int.out', 'a65'],
                    stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), '-1')
            stdout_f.seek(0)
            stdout_f.truncate()
            self.assertEqual(2,
                subprocess.call(['tests/io-driver/ez_str10_to_int.out', 'aaa'],
                    stdout=stdout_f))
            stdout_f.seek(0)
            self.assertEqual(stdout_f.read(), '-1')
            stdout_f.seek(0)
            stdout_f.truncate()

if __name__ == '__main__':
    # flush stdout, stdin, and stderr files by opening for writing then closing
    stdin_f = open('tests/io-driver/stdin_dummy', 'w')
    stdin_f.close()
    stdout_f = open('tests/io-driver/stdout_dummy', 'w')
    stdout_f.close()
    stderr_f = open('tests/io-driver/stderr_dummy', 'w')
    stderr_f.close()
    unittest.main()
