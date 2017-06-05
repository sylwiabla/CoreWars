#!/usr/bin/env python

        #raise NotImplementedError('Insert test code here.')
        #  Examples:
        # self.assertEqual(fp.readline(), 'This is a test')
        # self.assertFalse(os.path.exists('a'))
        # self.assertTrue(os.path.exists('a'))
        # self.assertTrue('already a backup server' in c.stderr)
        # self.assertIn('fun', 'disfunctional')
        # self.assertNotIn('crazy', 'disfunctional')
        # with self.assertRaises(Exception):
        #	raise Exception('test')
        #
        # Unconditionally fail, for example in a try block that should raise
        # self.fail('Exception was not raised')
#    @unittest.skipIf('SKIP_SLOW_TESTS' in os.environ, 'Requested fast tests')

#     https://github.com/linsomniac/python-unittest-skeleton

import unittest
import os
import sys
sys.path.append('../corewars')
import controller


class test_controller(unittest.TestCase):
    def setUp(self):
        ###  XXX code to do setup
        pass

    def tearDown(self):
        ###  XXX code to do tear down
        pass

    def test_connect_remote(self):
        app = controller.App()
        socket = app.create_socket()
        app.connect(socket)
        reply=app.recive_data(socket)
        self.assertEqual(reply,'Welcome to the server.')
        app.close(socket)

    # nie dziala
    def test_sing_in(self):
        app = controller.App()
        user_id = app.db_auth('zpr','cae2c166cd6f1094ef1609cae3721759')
        self.assertEqual(user_id, 3)



if __name__ == '__main__':
    unittest.main()
