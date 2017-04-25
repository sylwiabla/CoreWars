import socket
import sys
from thread import *
 
HOST = ''   
PORT = 4000 
 
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
 

def clientthread(conn):
    """Handling connections"""
    conn.send('Welcome to the server.') 
    while 1:
        data = conn.recv(4096)
	print data
        reply = data #soon: compitation errors
        if data=='bye': 
            break
        conn.sendall(reply)
    conn.close()
 
#talking with the client
while 1:
    conn, addr = s.accept()
    print 'Connected with ' + addr[0] + ':' + str(addr[1])
     
    #start clients thread 
    start_new_thread(clientthread ,(conn,))
 
s.close()
