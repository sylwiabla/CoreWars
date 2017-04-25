#!/usr/bin/python
import pygame
from pygame.locals import *
import graphics
import serverSQL
import socket
import sys
import thread

class App:
    def __init__(self):
        self._running = True
        self._display_surf = None
        self.size = self.weight, self.height = 700, 500
	self._tab_counter = False
	self._scenes_line = [
		graphics.Logger(),
		graphics.Game()
	]
	self._sceneID = 0;
	self._socket = self.create_socket()
	thread.start_new_thread (self.connect, (self._socket,))
	#self.connect(self._socket)
 
    def on_init(self):
        pygame.init()
        self._display_surf = pygame.display.set_mode(self.size, pygame.HWSURFACE | pygame.DOUBLEBUF)
        pygame.display.set_caption('CoreWars')
	box = self._scenes_line[self._sceneID]
	box.on_init(self._display_surf)
        self._running = True
 
    def on_event(self, event):
	""" Obsluga eventu """
        if event.type == KEYDOWN:
            if event.key == K_TAB:
                self._tab_counter= not self._tab_counter
            elif event.key == K_RETURN:
		pass
            else:
		self._scenes_line[self._sceneID].add_sign(self._display_surf,event.key,self._tab_counter)
            #print chr(event.key)
	elif event.type == MOUSEBUTTONDOWN:
	    pos = pygame.mouse.get_pos()
	    sprites = self._scenes_line[self._sceneID]._sprites
	    clicked_sprites = [s for s in sprites if s.collidepoint(pos)]
	    print clicked_sprites
	    if clicked_sprites:
		if clicked_sprites[0].x==201:
		    self.sign_in()
		else:
		    filename = self._scenes_line[self._sceneID].get_filename()
		    self.load_file(filename)
		
        if event.type == pygame.QUIT:
            self._running = False

    def on_loop(self):
	#thread.start_new_thread (self.recive_data, (self._socket,))
	#reply = self.recive_data(self._socket)
	pass

    def on_render(self):
        pygame.display.flip()

    def on_cleanup(self):
	self.close(self._socket)
        pygame.quit()

    def on_execute(self):
        if self.on_init() == False:
            self._running = False
 
        while( self._running ):
            for event in pygame.event.get():
                self.on_event(event)
            self.on_loop()
            self.on_render()
        self.on_cleanup()


    def load_file(self,filename):
	self.send(self._socket,filename)
	#s = Scanner.getInstance()
	#scanner.setSourceManager(filename)
	print "Loaded file: "+filename

    def sign_in(self):
	"""Connect to SQL server, check user""" 
    	sql = serverSQL.ServerSQL()
	cur = sql.connect()
	usr = self._scenes_line[self._sceneID].get_login()
	psw = self._scenes_line[self._sceneID].get_password()
	userID = sql.get_user_id(cur,usr,psw)
	sql.close_conn(cur)
	if userID:
	    self._sceneID+=1;
	else:
	    self._scenes_line[self._sceneID].display_error(self._display_surf)
	self._scenes_line[self._sceneID].on_init(self._display_surf)

    def create_socket(self):
	"""Create an INET, STREAMing socket"""
	try:
    	    self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except socket.error:
    	    print 'Failed to create socket'
    	    sys.exit()
	print 'Socket Created'
	return self._socket

    def connect(self,s):
	"""Connect to remote server"""
	s.connect(('localhost', 4000))
	print 'Socket Connected '


    def send(self,s,message):
	"""Send some data to remote server"""
	try :
    	    #Set the whole string
    	    s.sendall(message)
	except socket.error:
    	    #Send failed
    	    print 'Send failed'
    	    sys.exit()
	print 'Message send successfully'

    def recive_data(self,s):
	"""Receive data from server"""
	reply = s.recv(4096)
	print reply

    def close(self,s):
	self.send(self._socket,'bye')
	s.close()
	print 'Connection with server closed'


if __name__ == "__main__" :
    theApp = App()
    theApp.on_execute()

