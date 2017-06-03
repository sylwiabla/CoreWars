import unittest
import testing.postgresql

# Generate Postgresql class which shares the generated database
Postgresql = testing.postgresql.PostgresqlFactory(cache_initialized_db=True)


def tearDownModule(self):
    # clear cached database at end of tests
    Postgresql.clear_cache()


class MyTestCase(unittest.TestCase):
    def setUp(self):
        # Use the generated Postgresql class instead of testing.postgresql.Postgresql
        self.postgresql = Postgresql()

    def tearDown(self):
        self.postgresql.stop()
