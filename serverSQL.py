#!/usr/bin/python
import psycopg2
import hashlib

class ServerSQL:
    def connect(self):
        """ Connect to the PostgreSQL database server """
        self._conn = None
        try: 
            # connect to the PostgreSQL server
            print('Connecting to the PostgreSQL database...')
            self._conn = psycopg2.connect(host="localhost",database="users", user="postgres", password="zpr#corewar")
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
	    self._conn.commit()
            cur.close()
        except (Exception, psycopg2.DatabaseError) as error:
            print(error)
        finally:
            if self._conn is not None:
                self._conn.close()
                print('Database connection closed.')

    def create_table(self,cur):
        """ Create tables in the PostgreSQL database """
        command = 'CREATE TABLE users_info (user_id SERIAL PRIMARY KEY,login varchar (20) NOT NULL,password varchar (32) NOT NULL);'
        cur.execute(command)
 
    def display_table(self,cur,table_name):
        cmd = "SELECT * FROM "+table_name+";";
        cur.execute(cmd)
        rows = cur.fetchall()
	print('Table: '+table_name)
        for row in rows:
            print(row)

    def count_md5(self,u_pass):
        m = hashlib.md5()
        m.update(u_pass)
        u_hash = m.hexdigest()
	return u_hash

    def add_user(self,cur,u_log,u_pass):
	u_hash = self.count_md5(u_pass)
        print u_hash
	#TODO:prevent SQL injection!!
	#cmd = "INSERT INTO users_info (login,password) VALUES(%s,%s)"
        cur.execute("INSERT INTO users_info (login,password) VALUES ('"+u_log+"','"+u_hash+"')")

    def get_user_id(self,cur,u_log,u_pass):
        """Sign in - check if user has an account and return ID"""
	cmd = "SELECT user_id,password FROM users_info WHERE login LIKE '"+u_log+"'"
        cur.execute(cmd)
        rows = cur.fetchall()
	if cur.rowcount>0:
	    if rows[0][1]==self.count_md5(u_pass):
	    	return rows[0][0]
	return None


    def add_score(self,cur,user_id,score):
        """Dodaj wynik do sumy, porownaj z najlepszym wynikiem"""
        pass

    def remove_user(self,cur,user_id):
        """Usun uzytkownika"""
	cur.execute("DELETE FROM users_info WHERE user_id = %s", (user_id))
        # get the number of updated rows
        rows_deleted = cur.rowcount

    def get_statistics(self,cur,user_id):
	"""Suma punktow i najlepszy wynik uzytkownika"""
	pass


if __name__ == '__main__':
    server = ServerSQL()
    cur = server.connect()
    #server.display_table(cur,'users_info')
    #server.add_user(cur,'test','test')
    server.get_user_id(cur,"kama",'kama')
    server.close_conn(cur)
