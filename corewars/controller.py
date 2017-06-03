#!/usr/bin/python
import pygame
from pygame.locals import *
import graphics
import serverSQL
import socket
import sys
import thread

#TODO:
#      - wyswietlanie statystyk (dodawanie/usuwanie wojownikow, dodawanie punktow)
#      - rozpoczecie rozgrywki, obsluga przyciskow (start)
#      - dodatki, bajery, w stylu: status bitwy (jakie info moge dostac od Sylwii?)
#      - czy ja mam polaczyc dwa programy w jeden?
#      - setup.py - jak korzytac, co mi daje, co tam jeszcze dodac, co zrobic, by projekt dzialal na Windowsie? czy da sie tworzyc automatycznie nowa baze danych przy instalacji?
#      - eksport klas Sylwii do pythona, wykorzystanie w remote (errorLoger, co jeszcze?)
#      - testy (czy nalezy testowac baze danych? polaczenie z serwerem? grafike? co powinno byc przetestowane)
#      - dokumentacja (oxygen)


class App:
    def __init__(self):
        self._running = True
        self._display_surf = None
        self.size = self.weight, self.height = 700, 500
	self._tab_counter = False
	self._scenes_line = [
		graphics.Logger(),
		graphics.Game(),
                graphics.Statistics()
	]
        self._userID = 0;
	self._sceneID = 0;
        self._connected = False;
	self._socket = self.create_socket()
	thread.start_new_thread (self.connect, (self._socket,))
        

    def load_scene(self):
	self._scenes_line[self._sceneID].on_init(self._display_surf)
        #self._scenes_line[self._sceneID].light_up(self._display_surf, self._scenes_line[self._sceneID]._boxes[0])
 
    def on_init(self):
        pygame.init()
        self._display_surf = pygame.display.set_mode(self.size, pygame.HWSURFACE | pygame.DOUBLEBUF)
        pygame.display.set_caption('CoreWars')
        self.load_scene()
        self._running = True

 
    def on_event(self, event):
	"""Handling events """
        if event.type == KEYDOWN:
            if event.key == K_TAB:
                self._tab_counter= not self._tab_counter
	        if not self._tab_counter:
	            box = self._scenes_line[self._sceneID]._boxes[0]
                else:
                    box = self._scenes_line[self._sceneID]._boxes[1]
                self._scenes_line[self._sceneID].light_up(self._display_surf, box)
            elif event.key == K_RETURN:
		pass
            else:
		self._scenes_line[self._sceneID].add_sign(self._display_surf,event.key,self._tab_counter)
            #print chr(event.key)
	elif event.type == MOUSEBUTTONDOWN:
	    pos = pygame.mouse.get_pos()
            print pos
	    sprites = self._scenes_line[self._sceneID]._sprites[0]
	    titles = self._scenes_line[self._sceneID]._sprites[1]
	    clicked_sprites = [s for s in sprites if s.collidepoint(pos)]
	    print clicked_sprites
	    if clicked_sprites:
                index = sprites.index(clicked_sprites[0])
#		if clicked_sprites[0].y==313:
#		    self.sign_in()
                if titles[index]=='Sign in':
                    self.sign_in()
		elif titles[index]=='Sign up':
		    self.sign_up()
		elif titles[index]=='Load':
		    filename = self._scenes_line[self._sceneID].get_filename()
		    self.load_file(filename)
		elif titles[index]=='Start':
	            self.start_battle();
		elif titles[index]=='Scores':
	            self._sceneID+=1;
                    self.load_scene()
                    self.show_statistics(self._userID)
		elif titles[index]=='back':
	            self._sceneID-=1;
                    self.load_scene()
		elif titles[index]=='remove':
                    sql = serverSQL.ServerSQL()
	            cur = sql.connect()
                    scene = self._scenes_line[self._sceneID]
                    warrior_id = sql.get_warrior_id(cur,scene.get_convict())
                    sql.remove_warrior(cur,warrior_id)
                    text = sql.get_warriors(cur,self._userID)
	            scene.display_info(self._display_surf,text)
                    sql.close_conn(cur)

		
        if event.type == pygame.QUIT:
            self._running = False

    def on_loop(self):
        pass

    def on_render(self):
        pygame.display.flip()

    def on_cleanup(self):
        if self._connected:
	    self.close(self._socket)
        pygame.quit()

    def on_execute(self):
        """Main loop"""
        if self.on_init() == False or not self._connected:
            self._running = False
            print 'Cannot connect to remote server. Please, check if server is running.'
        while( self._running ):
            for event in pygame.event.get():
                self.on_event(event)
            self.on_loop()
            self.on_render()
        self.on_cleanup()


    def load_file(self,filename):
        """Send name of warrior program to compiler"""
	self.send(self._socket,'filename:'+filename)
        sql = serverSQL.ServerSQL()
	cur = sql.connect()
        if sql.add_warrior(cur,filename,self._userID): #name already in use
            self._scenes_line[self._sceneID].display_info(self._display_surf,'Username already exist.')
        else:
            self._scenes_line[self._sceneID].display_info(self._display_surf,"Loaded file: "+filename)
        sql.close_conn(cur)


    def sign_in(self):
	"""Connect to SQL server, check user""" 
    	sql = serverSQL.ServerSQL()
	cur = sql.connect()
	usr = self._scenes_line[self._sceneID].get_login()
	psw = self._scenes_line[self._sceneID].get_password()
        if not usr or not psw:
            sql.close_conn(cur)
            return
	userID = sql.get_user_id(cur,usr,psw)
	if userID: # if username and password is correct
	    self._sceneID+=1;
            username = sql.who_am_i(cur,userID)
            self.send(self._socket,username)
	else: # display error
	    self._scenes_line[self._sceneID].display_info(self._display_surf,"Incorrect login or password.")
            #self._tab_counter= not self._tab_counter
	#self._scenes_line[self._sceneID].on_init(self._display_surf)
        self.load_scene()
        self._tab_counter= not self._tab_counter
        self._userID = userID
        sql.close_conn(cur)


    def sign_up(self):
        """Create new account"""
    	sql = serverSQL.ServerSQL()
	cur = sql.connect()
	usr = self._scenes_line[self._sceneID].get_login()
	psw = self._scenes_line[self._sceneID].get_password()
        if not usr or not psw:
            return
        if sql.add_user(cur,usr,psw): #name already in use
            self._scenes_line[self._sceneID].display_info(self._display_surf,'Username already exist.')
        else:
	    self._scenes_line[self._sceneID].display_info(self._display_surf,'Account created. Please, sing in.')
	self._scenes_line[self._sceneID].on_init(self._display_surf)
        self._tab_counter= not self._tab_counter
        sql.close_conn(cur)

    def start_battle(self):
        """ ..."""
        # powiedz kompilatorowi, ze zaczynamy i wyslij rozmiar rdzenia
        pass


    def show_statistics(self, userID):
        """ Show scores in statistics scene """
        scene = self._scenes_line[self._sceneID]
    	sql = serverSQL.ServerSQL()
	cur = sql.connect()
        text = sql.get_warriors(cur,userID)
	scene.display_info(self._display_surf,text)
        text = sql.get_statistics(cur)
	scene.display_info(self._display_surf,text,1)
        sql.close_conn(cur)

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
        try:
	    s.connect(('localhost', 4000))
        except socket.error as msg:
            print 'Connection failed: ' + msg[1]
            sys.exit()
            # co gdy nie mozna polaczyc z serwerem???
	print 'Socket Connected '
        self._connected = True
        thread.start_new_thread (self.recive_data, (self._socket,))


    def send(self,s,message):
	"""Send some data to remote server"""
	try :
    	    s.sendall(message)
	except socket.error:
    	    print 'Send failed'
    	    sys.exit()
	print 'Message send successfully'

    def recive_data(self,s):
	"""Listen and receive data from server"""
        while(self._running):
	    reply = s.recv(4096)
	    print reply
            if reply.startswith('users:'):
                self._scenes_line[self._sceneID].save_users(self._display_surf,reply[6:])
            elif reply.startswith('compiler:'):
                self._scenes_line[self._sceneID].display_info(self._display_surf,reply[9:])


    def close(self,s):
        """Close connection with remote server"""
        if self._connected:
	    self.send(self._socket,'bye')
	    s.close()
	    print 'Connection with server closed'


if __name__ == "__main__" :
    theApp = App()
    theApp.on_execute()

