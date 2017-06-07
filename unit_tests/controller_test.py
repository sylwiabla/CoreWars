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

    def test_sing_in_positive(self):
        app = controller.App()
        user_id = app.db_auth('bartek','bartek')
        self.assertEqual(user_id, 6)

    def test_sing_in_wrong_password(self):
        app = controller.App()
        user_id = app.db_auth('bartek','barteky')
        self.assertEqual(user_id, 6)

    def test_sing_in_unknown_username(self):
        app = controller.App()
        user_id = app.db_auth('barteky','bartek')
        self.assertEqual(user_id, 6)

    def test_add_warrior_1_positive(self):
        app = controller.App()
        test = app.db_add_warrior('setydrth',6)
        print test
        self.assertEqual(test,None)

    def test_add_warrior_2_name_exist(self):
        app = controller.App()
        test = app.db_add_warrior('setydrth',6)
        print test
        self.assertEqual(test,None)

    def test_remove_warrior_3_positive(self):
        app = controller.App()
        test = app.db_remove_warrior('setydrth')
        print test
        self.assertEqual(test,1)

    def test_remove_warrior_4_not_exist(self):
        app = controller.App()
        test = app.db_remove_warrior('setydrth')
        print test
        self.assertEqual(test,1)

        


if __name__ == '__main__':
    unittest.main()
