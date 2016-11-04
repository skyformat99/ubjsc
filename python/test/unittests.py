# coding=utf-8

import os
import sys
from unittest import main, TestCase, skip

import ubjspy


class TestStructure(TestCase):

    def test_structure(self):
        self.assertTrue(callable(ubjspy.dumps))
        self.assertTrue(callable(ubjspy.pretty_print))
        self.assertTrue(callable(ubjspy.loads))
        self.assertTrue(set(['NOOP']).issubset(dir(ubjspy)))


class TestDumps(TestCase):

    def test_error(self):
        self.assertRaises(ubjspy.Exception, ubjspy.dumps, object())

    def test_null(self):
        self.assertEqual(b'Z', ubjspy.dumps(None))

    def test_noop(self):
        self.assertEqual(b'N', ubjspy.dumps(ubjspy.NOOP))

    def test_true(self):
        self.assertEqual(b'T', ubjspy.dumps(True))

    def test_false(self):
        self.assertEqual(b'F', ubjspy.dumps(False))

    def test_int(self):
        self.assertEqual(b'U\x00', ubjspy.dumps(0))
        self.assertEqual(b'U\x7F', ubjspy.dumps(127))
        self.assertEqual(b'i\xFF', ubjspy.dumps(-1))
        self.assertEqual(b'i\x80', ubjspy.dumps(-128))
        self.assertEqual(b'I\xFF\x7f', ubjspy.dumps(32767))
        self.assertEqual(b'l\x00\x00\x10\x00', ubjspy.dumps(1048576))
        self.assertEqual(b'L\xec61\xe0\x02\x00\x00\x00',
                         ubjspy.dumps(12351256300))
        # self.assertEqual(b'd\x00\x00\x10\x00', ubjspy.dumps(0.5))
        self.assertEqual(b'D\xb6\x8f\xcbn\x1c\xc7\xe1?',
                         ubjspy.dumps(0.55555555))

    def test_str(self):
        self.assertEqual(b'SU\x00', ubjspy.dumps(""))
        self.assertEqual(b'SU\x05rower', ubjspy.dumps("rower"))
        self.assertEqual(b'SU\x11Z\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00',
                         ubjspy.dumps("Zażółć gęślą jaźń"))

    def test_bytes(self):
        self.assertEqual(b'SU\x0512345', ubjspy.dumps(b'12345'))
        self.assertEqual(b'SU\x0512345', ubjspy.dumps(bytearray(b'12345')))

    def test_array(self):
        self.assertEqual(b'[$U#U\x03\x01\x02\x03', ubjspy.dumps((1, 2, 3)))
        self.assertEqual(b'[]', ubjspy.dumps([]))
        self.assertEqual(b'[[[[]]]]', ubjspy.dumps([[[[]]]]))
        self.assertEqual(b'[U\x01SU\x01a]', ubjspy.dumps([1, "a"]))
        self.assertEqual(b'[#U\x03U\x01SU\x01a[]', ubjspy.dumps([1, "a", []]))
        self.assertEqual(b'[$U#U\x05\x01\x02\x03\x04\x05',
                         ubjspy.dumps([1, 2, 3, 4, 5]))
        self.assertEqual(b'[$Z#U\xFF', ubjspy.dumps(
            [None for _ in range(255)]))

    def test_object(self):
        self.assertEqual(b'{}', ubjspy.dumps(dict()))
        self.assertEqual(b'{U\x01aU\x01}', ubjspy.dumps({"a": 1}))
        expected = b'{$U#U2U\x010\x00U\x011\x01U\x0210\nU\x0211\x0bU\x0212\x0cU\x0213\rU\x0214' + \
            b'\x0eU\x0215\x0fU\x0216\x10U\x0217\x11U\x0218\x12U\x0219\x13U\x012\x02U\x0220\x14U' + \
            b'\x0221\x15U\x0222\x16U\x0223\x17U\x0224\x18U\x0225\x19U\x0226\x1aU\x0227\x1bU' + \
            b'\x0228\x1cU\x0229\x1dU\x013\x03U\x0230\x1eU\x0231\x1fU\x0232 U\x0233!U\x0234"U' + \
            b'\x0235#U\x0236$U\x0237%U\x0238&U\x0239\'U\x014\x04U\x0240(U\x0241)U\x0242*U\x0243' + \
            b'+U\x0244,U\x0245-U\x0246.U\x0247/U\x02480U\x02491U\x015\x05U\x016\x06U\x017\x07U' + \
            b'\x018\x08U\x019\t'
        self.assertEqual(expected, ubjspy.dumps(
            {str(n): n for n in range(50)}))


class TestPrettyPrints(TestCase):

    def test_null(self):
        self.assertEqual('[Z]', ubjspy.pretty_print(None))

    def test_noop(self):
        self.assertEqual('[N]', ubjspy.pretty_print(ubjspy.NOOP))

    def test_true(self):
        self.assertEqual('[T]', ubjspy.pretty_print(True))

    def test_false(self):
        self.assertEqual('[F]', ubjspy.pretty_print(False))

    def test_int(self):
        self.assertEqual('[U][0]', ubjspy.pretty_print(0))
        self.assertEqual('[U][127]', ubjspy.pretty_print(127))
        self.assertEqual('[i][-1]', ubjspy.pretty_print(-1))
        self.assertEqual('[i][-128]', ubjspy.pretty_print(-128))
        self.assertEqual('[I][32767]', ubjspy.pretty_print(32767))
        self.assertEqual('[l][1048576]', ubjspy.pretty_print(1048576))
        self.assertEqual('[L][12351256300]', ubjspy.pretty_print(12351256300))
        # self.assertEqual('d\x00\x00\x10\x00', ubjspy.pretty_print(0.5))
        self.assertEqual('[D][0.555556]', ubjspy.pretty_print(0.55555555))

    def test_str(self):
        self.assertEqual('[S][U][0][]', ubjspy.pretty_print(""))
        self.assertEqual('[S][U][5][rower]', ubjspy.pretty_print("rower"))
        self.assertEqual('[S][U][17][Z\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00]',
                         ubjspy.pretty_print("Zażółć gęślą jaźń"))

    def test_bytes(self):
        self.assertEqual('[S][U][5][12345]', ubjspy.pretty_print(b'12345'))
        self.assertEqual('[S][U][5][12345]',
                         ubjspy.pretty_print(bytearray(b'12345')))

    def test_array(self):
        self.assertEqual(
            '[[][$][U][#][U][3]\n    [1]\n    [2]\n    [3]\n[]]', ubjspy.pretty_print((1, 2, 3)))
        self.assertEqual('[[][]]', ubjspy.pretty_print([]))

        expected = """[[]
    [[]
        [[]
            [[][]]
        []]
    []]
[]]"""
        self.assertEqual(expected, ubjspy.pretty_print([[[[]]]]))

        expected = """[[]
    [U][1]
    [S][U][1][a]
[]]"""
        self.assertEqual(expected, ubjspy.pretty_print([1, "a"]))

        expected = """[[][#][U][3]
    [U][1]
    [S][U][1][a]
    [[][]]
[]]"""
        self.assertEqual(expected, ubjspy.pretty_print([1, "a", []]))

        expected = """[[][$][U][#][U][5]
    [1]
    [2]
    [3]
    [4]
    [5]
[]]"""
        self.assertEqual(expected, ubjspy.pretty_print([1, 2, 3, 4, 5]))

        self.assertEqual('[[][$][Z][#][U][255][]]',
                         ubjspy.pretty_print([None for _ in range(255)]))

    def test_object(self):
        self.assertEqual('[{][}]', ubjspy.pretty_print(dict()))
        self.assertEqual('[{]\n    [U][1][a][U][1]\n[}]',
                         ubjspy.pretty_print({"a": 1}))

        expected = """[{][$][U][#][U][50]
    [U][1][0][0]
    [U][1][1][1]
    [U][2][10][10]
    [U][2][11][11]
    [U][2][12][12]
    [U][2][13][13]
    [U][2][14][14]
    [U][2][15][15]
    [U][2][16][16]
    [U][2][17][17]
    [U][2][18][18]
    [U][2][19][19]
    [U][1][2][2]
    [U][2][20][20]
    [U][2][21][21]
    [U][2][22][22]
    [U][2][23][23]
    [U][2][24][24]
    [U][2][25][25]
    [U][2][26][26]
    [U][2][27][27]
    [U][2][28][28]
    [U][2][29][29]
    [U][1][3][3]
    [U][2][30][30]
    [U][2][31][31]
    [U][2][32][32]
    [U][2][33][33]
    [U][2][34][34]
    [U][2][35][35]
    [U][2][36][36]
    [U][2][37][37]
    [U][2][38][38]
    [U][2][39][39]
    [U][1][4][4]
    [U][2][40][40]
    [U][2][41][41]
    [U][2][42][42]
    [U][2][43][43]
    [U][2][44][44]
    [U][2][45][45]
    [U][2][46][46]
    [U][2][47][47]
    [U][2][48][48]
    [U][2][49][49]
    [U][1][5][5]
    [U][1][6][6]
    [U][1][7][7]
    [U][1][8][8]
    [U][1][9][9]
[}]"""

        self.assertEqual(expected, ubjspy.pretty_print(
            {str(n): n for n in range(50)}))

if __name__ == '__main__':
    main(verbosity=2)
