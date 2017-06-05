import unittest
import testing.postgresql
import psycopg2
import pg8000
from contextlib import closing

def slurp(path):
    """ Reads and returns the entire contents of a file """
    with open(path, 'r') as f:
        return f.read()

# create initial data on create as fixtures into the database
def handler(postgresql):
    conn = psycopg2.connect(**postgresql.dsn())
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE hello(id int, value varchar(256))")
    cursor.execute("INSERT INTO hello values(1, 'hello'), (2, 'ciao')")
    #cursor.execute(slurp('../corewars/db_setup.sql'))
    cursor.close()
    conn.commit()
    conn.close()

# Generate Postgresql class which shares the generated database
Postgresql = testing.postgresql.PostgresqlFactory(cache_initialized_db=True,on_initialized=handler)                                    


def tearDownModule():
    # clear cached database at end of tests
    Postgresql.clear_cache()


class MyTestCase(unittest.TestCase):
    def setUp(self):
        # Use the generated Postgresql class instead of testing.postgresql.Postgresql
        self.postgresql = Postgresql()

    def tearDown(self):
        self.postgresql.stop()

    def test_PostgresqlFactory_with_initialized_handler(self):
        try:
            with Postgresql() as pgsql:
                conn = pg8000.connect(**pgsql.dsn())
                with closing(conn.cursor()) as cursor:
                    cursor.execute('SELECT * FROM hello ORDER BY id')
                    self.assertEqual(cursor.fetchall(), ([1, 'hello'], [2, 'ciao']))
                conn.close()
        finally:
            Postgresql.clear_cache()


if __name__ == '__main__':
    unittest.main()


