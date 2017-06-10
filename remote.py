#!/usr/bin/python
import socket
import sys
import corewars.serverSQL as serverSQL
from thread import *
sys.path.append('./build')
import compiler_ext


HOST = ''   #localhost
PORT = 4000 
LIMIT = 2
clients_name = []
clients_id = []
clients_conn = []
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'
 
#Bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
     
print 'Socket bind complete'
 
#Start listening on socket
s.listen(2)
print 'Socket now listening'

#create table in database
db = serverSQL.ServerSQL()
cur = db.connect()
try:
    db.get_table(cur,'users_info')
except Exception, e:
    db.create_table(cur)
    db.create_warriors_table(cur)
db.close_conn(cur)


def db_auth(login,password):
    """ Authentication in database """
    sql = serverSQL.ServerSQL()
    cur = sql.connect()
    userID = sql.get_user_id(cur,login,password)
    sql.close_conn(cur)
    return userID

def db_add_usr(login,password):
    """ Save new user in database """
    sql = serverSQL.ServerSQL()
    cur = sql.connect()
    userID = sql.add_user(cur,login,password)
    sql.close_conn(cur)
    return userID

def db_add_warrior(filename, userID):
    sql = serverSQL.ServerSQL()
    cur = sql.connect()
    ID = sql.add_warrior(cur,filename,userID)
    sql.close_conn(cur)
    return ID

def db_remove_warrior(userID,convict):
    sql = serverSQL.ServerSQL()
    cur = sql.connect()
    warrior_id = sql.get_warrior_id(cur,convict,userID)
    print 'Warrior:'+str(warrior_id)
    count = sql.remove_warrior(cur,warrior_id)
    sql.close_conn(cur)
    return count

def db_get_warriors(userID):
    sql = serverSQL.ServerSQL()
    cur = sql.connect()
    rest = sql.get_warriors(cur,userID)
    sql.close_conn(cur)
    return rest

def db_get_statistics(userID):
    sql = serverSQL.ServerSQL()
    cur = sql.connect()
    text = []
    print userID
    warriors = sql.get_warriors(cur,userID)
    statistics = sql.get_statistics(cur)
    sql.close_conn(cur)
    return [warriors,statistics]

def clientthread(conn):
    """Handling connections"""
    conn.send('Welcome to the server.')
    ID = 0
    while 1:
        data = conn.recv(4096)
        reply=''
        if data=='bye':
            if ID!=0:
                index = clients_conn.index(conn)
                clients_name.remove(clients_name[index])
            clients_conn.remove(conn)
            print 'Disconnected'
        if data.startswith('show:'):
            reply = 'show:'+str(db_get_statistics(data[5:]))
        if data.startswith('auth:'):
            text = data[5:].split(',')
            ID = db_auth(text[0], text[1])
            if ID!=None:
                try:
                    clients_name.index(text[0])
                    ID = None
                except:
                    clients_name.append(text[0])
            reply = 'auth:'+str(ID)
        if data.startswith('remove_w:'):
            print data[9:]
            db_remove_warrior(ID,data[9:])
            reply = 'show:'+str(db_get_statistics(ID))
        if data.startswith('add_usr:'):
            text = data[8:].split(',')
        if data.startswith('filename:'): # compile
            db_add_warrior(data[9:],ID)
            print 'Compiling...'
            error = compiler_ext.compile('corewars/'+data[9:])
            if len(error)>0:
                print error
                reply = 'error:'+error
            else:
                reply = 'compiled:'
        #reply = data #soon: compitation errors
        if data.startswith('get:'):
            for c in clients_conn:
                c.sendall('users:'+str(clients_name))
        else:
            conn.sendall(reply)

    conn.close()
 
#talking with the client
while 1:
    if len(clients_conn) < LIMIT:
        conn, addr = s.accept()
        print 'Connected with ' + addr[0] + ':' + str(addr[1])
        clients_conn.append(conn)
        #start clients thread 
        start_new_thread(clientthread ,(conn,))
 
s.close()
