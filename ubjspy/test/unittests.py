# coding=utf-8
"""
Unittests for ubjspy module.
"""

import io
from decimal import Decimal
from unittest import main, TestCase, skip

# pylint: disable=import-error
import ubjspy
# pylint: enable=import-error


def test_structure(self):
    """
        Tests for structure of exposed ubjspy module.
    """

    self.assertTrue(callable(ubjspy.dumps))
    self.assertTrue(callable(ubjspy.pretty_prints))
    self.assertTrue(callable(ubjspy.loads))
    self.assertTrue(callable(ubjspy.dump))
    self.assertTrue(callable(ubjspy.pretty_print))
    self.assertTrue(callable(ubjspy.load))
    self.assertTrue(set(['NOOP']).issubset(dir(ubjspy)))


class TestDumps(TestCase):
    """
        Tests for ubjspy.dumps().
    """

    def test_error(self):
        """
            Expectd faults.
        """
        self.assertRaises(TypeError, ubjspy.dumps)
        self.assertRaises(ubjspy.Exception, ubjspy.dumps, object())
        self.assertRaises(ubjspy.Exception, ubjspy.dumps, [object()])
        self.assertRaises(ubjspy.Exception, ubjspy.dumps, (object(),))
        self.assertRaises(ubjspy.Exception, ubjspy.dumps, {1: object()})
        self.assertRaises(ubjspy.Exception, ubjspy.dumps, {'a': object()})

    def test_null(self):
        """
            Dumps null.
        """

        self.assertEqual(b'Z', ubjspy.dumps(None))

    def test_noop(self):
        """
            Dumps noop.
        """

        self.assertEqual(b'N', ubjspy.dumps(ubjspy.NOOP))

    def test_true(self):
        """
            Dumps true.
        """
        self.assertEqual(b'T', ubjspy.dumps(True))

    def test_false(self):
        """
            Dumps false.
        """
        self.assertEqual(b'F', ubjspy.dumps(False))

    def test_numbers(self):
        """
            Dumps numbers to ints/floats.
        """

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
        """
            Dumps strings.
        """

        self.assertEqual(b'SU\x00', ubjspy.dumps(""))
        self.assertEqual(b'SU\x05rower', ubjspy.dumps("rower"))
        self.assertEqual(b'SU\x11Z\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00',
                         ubjspy.dumps("Zażółć gęślą jaźń"))

    def test_hpn(self):
        """
            Dumps decimals to HPNs.
        """

        self.assertEqual(b'HU\x010', ubjspy.dumps(Decimal(0)))

    def test_bytes(self):
        """
            Special case - dumps byte(array)s to string.
        """

        self.assertEqual(b'SU\x0512345', ubjspy.dumps(b'12345'))
        self.assertEqual(b'SU\x0512345', ubjspy.dumps(bytearray(b'12345')))

    def test_array(self):
        """
            Dumps arrays.
        """

        self.assertEqual(b'[$U#U\x03\x01\x02\x03', ubjspy.dumps((1, 2, 3)))
        self.assertEqual(b'[]', ubjspy.dumps([]))
        self.assertEqual(b'[[[[]]]]', ubjspy.dumps([[[[]]]]))
        self.assertEqual(b'[U\x01SU\x01a]', ubjspy.dumps([1, "a"]))
        self.assertEqual(b'[#U\x03U\x01SU\x01a[]', ubjspy.dumps([1, "a", []]))
        self.assertEqual(b'[$U#U\x05\x01\x02\x03\x04\x05',
                         ubjspy.dumps([1, 2, 3, 4, 5]))
        self.assertEqual(b'[$Z#U\xFF', ubjspy.dumps(
            [None for _ in range(255)]))

    @skip("issue #63")
    def test_dict(self):
        """
            Dumps dicts to objects.
        """

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


class TestDump(TestCase):
    """
        Tests for ubjspy.dump().
    """

    def test_sunnyday(self):
        """
            Regular flow.
        """

        afile = io.BytesIO()
        ubjspy.dump("rower", afile)
        self.assertEqual(b'SU\x05rower', afile.getvalue())

    def test_raises_when_no_io(self):
        """
            Raises when no io provided.
        """
        self.assertRaises(ubjspy.Exception, ubjspy.dump, "rower", None)

    def test_raises_when_io_not_io(self):
        """
            Raises when io is not an io stream.
        """

        ubject_without_write = object()
        self.assertRaises(ubjspy.Exception, ubjspy.dump,
                          "rower", ubject_without_write)

    def test_raises_unknown_primitive(self):
        """
            Raises upon dumping unknown primitive.
        """

        afile = io.BytesIO()
        self.assertRaises(ubjspy.Exception, ubjspy.dump, object(), afile)


class TestPrettyPrint(TestCase):
    """
        Tests for ubjspy.pretty_print().
    """

    def test_sunnyday(self):
        """
            Regular flow.
        """

        afile = io.StringIO()
        ubjspy.pretty_print("rower", afile)
        self.assertEqual('[S][U][5][rower]', afile.getvalue())

    def test_raises_when_no_io(self):
        """
            Raises when no io provided.
        """
        self.assertRaises(ubjspy.Exception, ubjspy.pretty_print, "rower", None)

    def test_raises_when_io_not_io(self):
        """
            Raises when io is not an io stream.
        """

        ubject_without_write = object()
        self.assertRaises(ubjspy.Exception, ubjspy.pretty_print,
                          "rower", ubject_without_write)

    def test_raises_unknown_primitive(self):
        """
            Raises upon dumping unknown primitive.
        """

        afile = io.StringIO()
        self.assertRaises(ubjspy.Exception, ubjspy.dump, object(), afile)


class TestPrettyPrints(TestCase):
    """
        Tests for ubjspy.pretty_prints().
    """

    def test_null(self):
        """
            Null.
        """

        self.assertEqual('[Z]', ubjspy.pretty_prints(None))

    def test_error(self):
        """
            Expectd faults.
        """
        self.assertRaises(TypeError, ubjspy.pretty_prints)
        self.assertRaises(ubjspy.Exception, ubjspy.pretty_prints, object())
        self.assertRaises(ubjspy.Exception, ubjspy.pretty_prints, [object()])
        self.assertRaises(ubjspy.Exception, ubjspy.pretty_prints, (object(),))
        self.assertRaises(ubjspy.Exception,
                          ubjspy.pretty_prints, {1: object()})
        self.assertRaises(ubjspy.Exception,
                          ubjspy.pretty_prints, {'a': object()})

    def test_noop(self):
        """
            Noop.
        """

        self.assertEqual('[N]', ubjspy.pretty_prints(ubjspy.NOOP))

    def test_true(self):
        """
            True.
        """

        self.assertEqual('[T]', ubjspy.pretty_prints(True))

    def test_false(self):
        """
            False.
        """

        self.assertEqual('[F]', ubjspy.pretty_prints(False))

    def test_numbers(self):
        """
            Numbers.
        """

        self.assertEqual('[U][0]', ubjspy.pretty_prints(0))
        self.assertEqual('[U][127]', ubjspy.pretty_prints(127))
        self.assertEqual('[i][-1]', ubjspy.pretty_prints(-1))
        self.assertEqual('[i][-128]', ubjspy.pretty_prints(-128))
        self.assertEqual('[I][32767]', ubjspy.pretty_prints(32767))
        self.assertEqual('[l][1048576]', ubjspy.pretty_prints(1048576))
        self.assertEqual('[L][12351256300]', ubjspy.pretty_prints(12351256300))
        # self.assertEqual('d\x00\x00\x10\x00', ubjspy.pretty_prints(0.5))
        self.assertEqual('[D][0.555556]', ubjspy.pretty_prints(0.55555555))

    def test_str(self):
        """
            Strings.
        """

        self.assertEqual('[S][U][0][]', ubjspy.pretty_prints(""))
        self.assertEqual('[S][U][5][rower]', ubjspy.pretty_prints("rower"))
        self.assertEqual('[S][U][17][Z\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
                         '\x00\x00\x00\x00\x00\x00]',
                         ubjspy.pretty_prints("Zażółć gęślą jaźń"))

    def test_hpn(self):
        """
            Decimals to HPNs.
        """

        self.assertEqual('[H][U][1][0]', ubjspy.pretty_prints(Decimal(0)))

    def test_bytes(self):
        """
            Byte(array)s to strings.
        """

        self.assertEqual('[S][U][5][12345]', ubjspy.pretty_prints(b'12345'))
        self.assertEqual('[S][U][5][12345]',
                         ubjspy.pretty_prints(bytearray(b'12345')))

    def test_array(self):
        """
            Arrays.
        """

        self.assertEqual(
            '[[][$][U][#][U][3]\n    [1]\n    [2]\n    [3]', ubjspy.pretty_prints((1, 2, 3)))
        self.assertEqual('[[][]]', ubjspy.pretty_prints([]))

        expected = """[[]
    [[]
        [[]
            [[][]]
        []]
    []]
[]]"""
        self.assertEqual(expected, ubjspy.pretty_prints([[[[]]]]))

        expected = """[[]
    [U][1]
    [S][U][1][a]
[]]"""
        self.assertEqual(expected, ubjspy.pretty_prints([1, "a"]))

        expected = """[[][#][U][3]
    [U][1]
    [S][U][1][a]
    [[][]]"""
        self.assertEqual(expected, ubjspy.pretty_prints([1, "a", []]))

        expected = """[[][$][U][#][U][5]
    [1]
    [2]
    [3]
    [4]
    [5]"""
        self.assertEqual(expected, ubjspy.pretty_prints([1, 2, 3, 4, 5]))

        self.assertEqual('[[][$][Z][#][U][255]',
                         ubjspy.pretty_prints([None for _ in range(255)]))

    @skip("issue #63")
    def test_dict(self):
        """
            Dicts to objects.
        """

        self.assertEqual('[{][}]', ubjspy.pretty_prints(dict()))
        self.assertEqual('[{]\n    [U][1][a][U][1]\n[}]',
                         ubjspy.pretty_prints({"a": 1}))

        expected = """[{][$][U][#][U][50]
    [U][1][0][0]
    [U][2][10][10]
    [U][2][11][11]
    [U][2][12][12]
    [U][2][13][13]
    [U][2][14][14]
    [U][2][15][15]
    [U][2][16][16]
    [U][2][17][17]
    [U][2][18][18]
    [U][1][1][1]
    [U][2][19][19]
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
    [U][1][2][2]
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
    [U][1][3][3]
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
    [U][1][4][4]
    [U][1][5][5]
    [U][1][6][6]
    [U][1][7][7]
    [U][1][8][8]
    [U][1][9][9]
[}]"""

        self.assertEqual(expected, ubjspy.pretty_prints(
            {str(n): n for n in range(50)}))


class TestLoads(TestCase):
    """
        Tests for ubjspy.loads().
    """

    def test_raises_bad_input(self):
        """
            Input is neither bytes, nor bytearray.
        """

        self.assertRaises(TypeError, ubjspy.loads)
        self.assertRaises(ubjspy.Exception, ubjspy.loads, None)

    def test_raises_on_parser_error(self):
        """
            Raises exception upon any parser error.
        """

        self.assertRaises(ubjspy.Exception, ubjspy.loads, b']')

    def test_returns_only_first_item(self):
        """
            Only first parsed item is returned, the rest is discarded.
        """

        self.assertEqual(None, ubjspy.loads(b'ZN'))

    def test_null(self):
        """
            Null.
        """

        self.assertEqual(None, ubjspy.loads(b'Z'))

    def test_noop(self):
        """
            Noop.
        """
        self.assertEqual(ubjspy.NOOP, ubjspy.loads(b'N'))

    def test_true(self):
        """
            True.
        """
        self.assertEqual(True, ubjspy.loads(b'T'))

    def test_false(self):
        """
            False.
        """
        self.assertEqual(False, ubjspy.loads(b'F'))

    def test_numbers(self):
        """
            Numbers.
        """
        self.assertEqual(0, ubjspy.loads(b'U\x00'))
        self.assertEqual(0, ubjspy.loads(b'i\x00'))
        self.assertEqual(0, ubjspy.loads(b'I\x00\x00'))
        self.assertEqual(0, ubjspy.loads(b'l\x00\x00\x00\x00'))
        self.assertEqual(0, ubjspy.loads(b'L\x00\x00\x00\x00\x00\x00\x00\x00'))
        self.assertEqual(0, ubjspy.loads(b'd\x00\x00\x00\x00'))
        self.assertEqual(0, ubjspy.loads(b'D\x00\x00\x00\x00\x00\x00\x00\x00'))

    def test_str(self):
        """
            Strings.
        """

        self.assertEqual('', ubjspy.loads(b'SU\x00'))
        self.assertEqual('rower', ubjspy.loads(b'SU\x05rower'))

    def test_char(self):
        """
            Chars map to 1-length strings.
        """

        self.assertEqual('a', ubjspy.loads(b'Ca'))

    def test_hpn(self):
        """
            HPNs map to Decimals.
        """

        self.assertEqual(Decimal(0), ubjspy.loads(b'HU\x010'))

    def test_array(self):
        """
            Arrays.
        """

        self.assertEqual([1, 2, 3], ubjspy.loads(b'[$U#U\x03\x01\x02\x03'))
        self.assertEqual([], ubjspy.loads(b'[]'))
        self.assertEqual([[[[]]]], ubjspy.loads(b'[[[[]]]]'))
        self.assertEqual([1, "a"], ubjspy.loads(b'[U\x01SU\x01a]'))
        self.assertEqual([1, "a", []], ubjspy.loads(b'[#U\x03U\x01SU\x01a[]'))
        self.assertEqual([1, 2, 3, 4, 5],
                         ubjspy.loads(b'[$U#U\x05\x01\x02\x03\x04\x05'))
        self.assertEqual([None for _ in range(255)],
                         ubjspy.loads(b'[$Z#U\xFF'))

    def test_bytes_bytearray_same(self):
        """
            Same bytes input means same bytearray input.
        """

        self.assertEqual(ubjspy.loads(b'[$Z#U\xFF'),
                         ubjspy.loads(bytearray(b'[$Z#U\xFF')))

    def test_object(self):
        """
            Objects.
        """

        self.assertEqual(dict(), ubjspy.loads(b'{}'))
        self.assertEqual({"a": 1}, ubjspy.loads(b'{U\x01aU\x01}'))
        payload = b'{$U#U2U\x010\x00U\x011\x01U\x0210\nU\x0211\x0bU\x0212\x0cU\x0213\rU\x0214' + \
            b'\x0eU\x0215\x0fU\x0216\x10U\x0217\x11U\x0218\x12U\x0219\x13U\x012\x02U\x0220\x14U' + \
            b'\x0221\x15U\x0222\x16U\x0223\x17U\x0224\x18U\x0225\x19U\x0226\x1aU\x0227\x1bU' + \
            b'\x0228\x1cU\x0229\x1dU\x013\x03U\x0230\x1eU\x0231\x1fU\x0232 U\x0233!U\x0234"U' + \
            b'\x0235#U\x0236$U\x0237%U\x0238&U\x0239\'U\x014\x04U\x0240(U\x0241)U\x0242*U\x0243' + \
            b'+U\x0244,U\x0245-U\x0246.U\x0247/U\x02480U\x02491U\x015\x05U\x016\x06U\x017\x07U' + \
            b'\x018\x08U\x019\t'
        self.assertEqual({str(n): n for n in range(50)}, ubjspy.loads(payload))


class TestLoad(TestCase):
    """
        Tests for ubjspy.load().
    """

    def test_sunnyday(self):
        """
            Regular flow.
        """

        afile = io.BytesIO(b'SU\x05rower')
        self.assertEqual('rower', ubjspy.load(afile))

    def test_raises_wrong_arguments(self):
        """
            Wrong arguments count.
        """

        self.assertRaises(TypeError, ubjspy.load)

    def test_raises_io_not_io(self):
        """
            Raises when io is not a valid io stream.
        """

        object_without_read = object()
        self.assertRaises(ubjspy.Exception, ubjspy.load, object_without_read)

    def test_raises_uncomplete(self):
        """
            Raises when there is no complete primitive in parsed stream.
        """

        afile = io.BytesIO(b'S')
        self.assertRaises(ubjspy.Exception, ubjspy.load, afile)

    def test_raises_parse_error(self):
        """
            Raises when parse error occurs.
        """

        afile = io.BytesIO(b']')
        self.assertRaises(ubjspy.Exception, ubjspy.load, afile)

if __name__ == '__main__':
    main(verbosity=2)
