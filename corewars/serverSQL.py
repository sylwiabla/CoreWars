#!/usr/bin/python
import psycopg2
from config import config
import hashlib

class ServerSQL:
    def connect(self):
        """ Connect to the PostgreSQL database server """
        self._conn = None
        try: 
	    # read connection parameters
            params = config()
            # connect to the PostgreSQL server
            print('Connecting to the PostgreSQL database...')
            self._conn = psycopg2.connect(**params)
            # create a cursor
            cur = self._conn.cursor()
            return cur
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)


    def display_version(self,cur):
        # execute a statement
        print('PostgreSQL database version:')
        cur.execute('SELECT version()')
 
        # display the PostgreSQL database server version
        db_version = cur.fetchone()
        print(db_version)

    def close_conn(self,cur):
        """ Close the communication with the PostgreSQL """
        try:
	    self._conn.commit() #commit changes
            cur.close()
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
        finally:
            if self._conn is not None:
                self._conn.close()
                print('Database connection closed.')

# --------------------------------------------------------------

    def create_table(self,cur):
        """ Create users_info table in the PostgreSQL database """
        command = 'CREATE TABLE users_info (user_id SERIAL PRIMARY KEY,login varchar (20) NOT NULL,password varchar (32) NOT NULL, best_score integer);'
        cur.execute(command)

    def create_warriors_table(self,cur):
        """ Create warriors table in the database """
        command = 'CREATE TABLE warriors (warrior_id SERIAL,user_id int4,warrior_name varchar (32) NOT NULL, points integer, PRIMARY KEY (warrior_id), FOREIGN KEY (user_id) REFERENCES users_info(user_id));'
        cur.execute(command)

    def delete_table(self,cur,table_name):# nieprzetestowana!
        """ Drop table """
        command = "DROP TABLE "+table_name+";"
        cur.execute(command)

# --------------------------------------------------------

    def get_table(self,cur,table_name):
        cur.execute("SELECT * FROM "+table_name+";")
        rows = cur.fetchall()
#	print('Table: '+table_name)
#        for row in rows:
#            print(row)
        return rows

    def get_warriors(self,cur,user_id):
        cur.execute("SELECT warrior_name,points FROM warriors WHERE user_id="+str(user_id)+";")
        return cur.fetchall()

    def get_statistics(self,cur):
	"""Get user's best score"""
        cur.execute("SELECT login,best_score FROM users_info ORDER BY best_score DESC;")
        return cur.fetchall()

# -------------------------------------------------------------

    def count_md5(self,u_pass):
	""" Count md5 hash of given password """
        m = hashlib.md5()
        m.update(u_pass)
        u_hash = m.hexdigest()
	return u_hash


    def find_user(self,cur,u_log):
        """Check if username already exist in database"""
        cur.execute("SELECT user_id,password FROM users_info WHERE login LIKE (%s)", (u_log,))
        rows = cur.fetchall()
        return rows


    def find_warrior(self,cur,warrior_name):
        """Get warrior ID based on its name"""
        cur.execute("SELECT warrior_id FROM warriors WHERE warrior_name LIKE (%s)", (warrior_name,))
        rows = cur.fetchall()
        return rows


    def add_user(self,cur,u_log,u_pass):
        """Add new user to db"""
	rows = self.find_user(cur,u_log) 
        # check if username is avaible
	if cur.rowcount>0:
	    return rows[0][0]
	u_hash = self.count_md5(u_pass)
        print u_hash
        cur.execute("INSERT INTO users_info (login,password) VALUES (%s,%s)",(u_log,u_hash,))

# maximum number of warriors (???)
    def add_warrior(self,cur,warrior_name,user_id):
        """Add new warrior to db"""
	rows = self.find_warrior(cur,warrior_name)
	if cur.rowcount>0:
	    return rows[0][0]# warrior exist
        else:
            cur.execute("INSERT INTO warriors (warrior_name,points,user_id) VALUES (%s,%s,%s)",(warrior_name,0,user_id,))


    def get_user_id(self,cur,u_log,u_pass):
        """Sign in - check if user has an account and return ID"""
        rows = self.find_user(cur,u_log)
	if cur.rowcount>0:
	    if rows[0][1]==self.count_md5(u_pass):
	    	return rows[0][0]
	return None

    def get_warrior_id(self,cur,warrior_name):
        rows = self.find_warrior(cur,warrior_name)
	if cur.rowcount>0:
	    return rows[0][0]
	return None

    def who_am_i(self,cur,user_id):
        """Return username"""
	cmd = "SELECT login FROM users_info WHERE user_id="+str(user_id)
	cur.execute(cmd)
        rows = cur.fetchall()
	print 'Logged as: '+rows[0][0]
	return rows[0][0]


    def add_score(self,cur,warrior_id,score):# nieprzetestowana!
        """Add new score to sum of points then compare with the best result and insert new value if needed"""
        cur.execute("SELECT points FROM warriors WHERE warrior_id = %s", (user_id))
        points = cur.fetchall()
        cur.execute("INSERT INTO warriors (points) VALUES (%s)", (score+points,))
        cur.execute("SELECT best_score FROM users_info WHERE user_id = %s", (user_id))
        rows = cur.fetchall()
        if score > rows[0][0]:
            cur.execute("INSERT INTO users_info (best_score) VALUES (%s)", (score,))


    def remove_user(self,cur,user_id):
        """Remove users info from db"""
	cur.execute("DELETE FROM users_info WHERE user_id = "+str(user_id))
        rows_deleted = cur.rowcount
	cur.execute("DELETE FROM warriors WHERE user_id = " + str(user_id))

    def remove_warrior(self,cur,warrior_id):
        """Remove warriors info from db"""
	cur.execute("DELETE FROM warriors WHERE warrior_id = " + str (warrior_id))




if __name__ == '__main__':
    server = ServerSQL()
    cur = server.connect()
    #server.create_warriors_table(cur)
    #print server.get_table(cur, 'users_info')
    server.remove_warrior(cur, 5)
    #server.delete_table(cur,'warriors')
    #print server.get_warrior_id(cur,'zbyszek')
    #print server.get_statistics(cur)
    print server.get_table(cur, 'warriors')
    #print server.get_warriors(cur,1)
    server.close_conn(cur)



