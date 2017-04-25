import unittest
import serverSQL

class SQLTests(unittest.TestCase):

    def testConnect(self):
        server = serverSQL.ServerSQL()
        self.failUnless(server.connect())

    def testCloseConn(self):
        server = serverSQL.ServerSQL()
        cur = server.connect()
	self.failUnless(server.close_conn(cur))

def main():
    unittest.main()

if __name__ == '__main__':
    main()
