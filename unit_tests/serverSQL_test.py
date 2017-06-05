import psycopg2
import testing.postgresql
#from nose.tools import eq_
sys.path.append('../corewars')
from serverSQL import *
from config import config

# https://github.com/walkermatt/python-postgres-testing-demo

# Reference to testing.postgresql database instance
db = None

# Connection to the database used to set the database state before running each
# test
db_con = None

# Map of database connection parameters passed to the functions we're testing
db_conf = None


def setUp(self):
    """ Module level set-up called once before any tests in this file are
    executed.  Creates a temporary database and sets it up """
    global db, db_con, db_conf, server
    server = ServerSQL()
    db = testing.postgresql.Postgresql()
    db_conf = db.dsn() #config()
    db_con = psycopg2.connect(**db_conf)
    db_con.set_isolation_level(psycopg2.extensions.ISOLATION_LEVEL_AUTOCOMMIT)
    with db_con.cursor() as cur:
        # Create the initial database structure
        # basically anything that doesn't change
        cur.execute(slurp('./corewars/db_setup.sql'))


def tearDown(self):
    """ Called after all of the tests in this file have been executed to close
    the database connecton and destroy the temporary database """
    db_con.close()
    db.stop()


def test_add_user():

    # Ensure the database is in a known state before calling the function we're
    # testing
    with db_con.cursor() as cur:
        cur.execute(slurp('./tests/fixtures/state_empty.sql'))

    # Attempt to insert user
    server.add_user(cur,'zbyszek','zbyszek')

    # Inspect the state of the database and make some assertions
    with db_con.cursor() as cur:

        # Check the rows in the table after insert has been called
        rows = server.get_table(cur,'users_info')
        # Using the eq_ function from nose.tools allows us to assert that
        # complex types are equal. Here we are saying that we expect a single
        # row 
        eq_(rows, [('zbyszek',)])



def slurp(path):
    """ Reads and returns the entire contents of a file """
    with open(path, 'r') as f:
        return f.read()
