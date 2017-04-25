#!/usr/bin/python
import pygame
from pygame.locals import *
import graphics
import serverSQL
#from wrapper import *
#from Scanner import *

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
 
    def on_init(self):
        pygame.init()
        self._display_surf = pygame.display.set_mode(self.size, pygame.HWSURFACE | pygame.DOUBLEBUF)
        pygame.display.set_caption('CoreWar')
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
		#TODO: obsluzyc ladnie przyciski
		if clicked_sprites[0].x==201:
		    self.sign_in()
		else:
		    filename = self._scenes_line[self._sceneID].get_filename()
		    self.load_file(filename)
		
        if event.type == pygame.QUIT:
            self._running = False

    def on_loop(self):
	pass

    def on_render(self):
        pygame.display.flip()

    def on_cleanup(self):
        pygame.quit()
 
    def load_file(self,filename):
	#s = Scanner.getInstance()
	#scanner.setSourceManager(filename)
	print "Loaded file: "#+filename

    def sign_in(self):
    	server = serverSQL.ServerSQL()
	cur = server.connect()
	usr = self._scenes_line[self._sceneID].get_login()
	psw = self._scenes_line[self._sceneID].get_password()
	userID = server.get_user_id(cur,usr,psw)
	server.close_conn(cur)
	if userID:
	    self._sceneID+=1;
	else:
	    self._scenes_line[self._sceneID].display_error(self._display_surf)
	self._scenes_line[self._sceneID].on_init(self._display_surf)

    def on_execute(self):
        if self.on_init() == False:
            self._running = False
 
        while( self._running ):
	    #po wszystkich evntach z kolejki
            for event in pygame.event.get():
                self.on_event(event)
            self.on_loop()
            self.on_render()
        self.on_cleanup()
 
if __name__ == "__main__" :
    theApp = App()
    theApp.on_execute()

#    events przyciski
#    loop	ruch na podstawie kodu
#    render	wyswieltenie grafiki

