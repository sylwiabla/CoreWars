#!/usr/bin/python
import socket
import sys
from thread import *
sys.path.append('./build')
import compiler_ext
 
HOST = ''   #localhost
PORT = 4000 
LIMIT = 2
clients_name = []
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
 
#error = compiler_ext.compile('./sylw/test/test')

def clientthread(conn):
    """Handling connections"""
    conn.send('Welcome to the server.') 
    #first recived info is username (if it is not a goodbye)
    username = conn.recv(4096)
    if username!='bye':
        clients_name.append(username)
    else:
        clients_conn.remove(conn)
        print 'Disconnected'
        conn.close()
        return
    for c in clients_conn:
        c.send('users:'+str(clients_name)) # send to all clients
        print 'users:'+str(clients_name)
    while 1:
        data = conn.recv(4096)
	print data+', '+username
        if data=='bye':
            clients_name.remove(username)
            clients_conn.remove(conn)
            break
        if data.startswith('filename:'): # compile
            print 'Compiling...'
            error = compiler_ext.compile('corewars/'+data[9:])
            if len(error)>0:
                print error
                reply = 'error:'+error
            else:
                reply = 'compiled:'
        #reply = data #soon: compitation errors
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
