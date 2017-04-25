#!/usr/bin/python
import pygame, string
from pygame.locals import *
from abc import *#ABCMeta, abstract method

BLUE = (128,0,255)
WHITE = (255,255,255)

class Scene:
    __metaclass__=ABCMeta
    #def __init__(self):
	
        #self._screen = screen

    @abstractmethod
    def on_init(self,screen):
        pass
    @abstractmethod
    def add_sign(self,screen,inkey,tab):
        pass

    def display_box(self,screen,x,y):
	pygame.draw.rect(screen, BLUE,
        (x,y,200,20), 1)

    def display_label(self,screen,_string,x,y):
        myfont = pygame.font.SysFont("monospace", 20)
        label = myfont.render(_string, 1, BLUE)
        screen.blit(label, (x, y))
        return label

    def display_button(self,screen,text,x,y):
	rect = pygame.Rect(x,y,100,30)
	pygame.draw.rect(screen, BLUE, rect, 0)
        font = pygame.font.Font("fonts/starjedi/Starjedi.ttf", 16)
        label = font.render(text, 1, (0,0,0))
	self._sprites.append(rect)
        screen.blit(label, (x+10, y+2))

class Logger(Scene):
    def __init__(self):
        #self._screen = screen
        #self.on_init(screen)
	self._sprites = []
        self._temp = []
        self._login = []
        self._password = []

    def on_init(self,screen):
	font = pygame.font.Font("fonts/starjedi/Starjhol.ttf", 46)
        self._label = font.render("Core Wars", 1, BLUE)
        screen.blit(self._label,
       ((screen.get_width()/4)-20,screen.get_height()/6))
        self.display_label(screen,"Login",
	screen.get_width()/4,(screen.get_height()/3)+20)
        self.display_box(screen,
	screen.get_width()/4,(screen.get_height()/3)+40)
        self.display_label(screen,"Password",
	screen.get_width()/4,(screen.get_height()/2)-10)
        self.display_box(screen,
	screen.get_width()/4,(screen.get_height()/2)+10)
	self.display_button(screen,"Sign in",201,313)

    def add_sign(self,screen,inkey,tab):
        if tab==False:
            self.add_sign_to_log(screen,inkey)
        else:
            self.add_sign_to_pass(screen,inkey)


    def add_sign_to_log(self,screen,inkey):
        """Zapisywanie znakow loginu"""
        log_x = screen.get_width()/4+5
        log_y = screen.get_height()/3+40
        pass_x = screen.get_width()/4+5
        pass_y = screen.get_height()/2+10
        if inkey == K_BACKSPACE: 
            self._login = self._login[0:-1]
            screen.fill((0,0,0))
            self.on_init(screen)
            hidden_pass = "*"*len(self._password)
            self.display_label(screen,hidden_pass,pass_x,pass_y)
        elif inkey <= 127:
            self._login+=chr(inkey)
        self._login = string.join(self._login,"")
        self.display_label(screen,self._login,log_x,log_y)

        
    def add_sign_to_pass(self,screen,inkey):
        """Zapisywanie znakow hasla"""
        log_x = screen.get_width()/4+5
        log_y = screen.get_height()/3+40
        pass_x = screen.get_width()/4+5
        pass_y = screen.get_height()/2+10
        if inkey == K_BACKSPACE:
            self._password = self._password[0:-1]
            screen.fill((0,0,0))
            self.on_init(screen)
            self.display_label(screen,self._login,log_x,log_y)
        elif inkey <= 127:
            self._password+=chr(inkey)
        self._password = string.join(self._password,"")
        hidden_pass = "*"*len(self._password)
        self.display_label(screen,hidden_pass,pass_x,pass_y)

    def get_login(self):
        return self._login

    def get_password(self):
        return self._password

    def display_error(self,screen):
	""" Display error message """
	screen.fill((0,0,0))
	self.display_label(screen,"Incorrect login or password.",
	screen.get_width()/4-40,(screen.get_height()/3-10))
	self.__init__()
	#self.on_init(screen)

"""class Sign_Up(Logger):
	#scena zakladania konta
    #def __init__(self):
        #self.on_init(screen)
    def on_init(self,screen):
        self.display_label(screen,'Create new account',
	(screen.get_width()/4)-20,(screen.get_height()/6)+60)"""

class Game(Scene):
    """ Main game scene """
    def __init__(self):
        #self.on_init(screen)
	self._sprites = []
	self._filename = []
	self._memory = []

    def on_init(self,screen):
        screen.fill((0,0,0))
	self._width = screen.get_width()
	self._height = screen.get_height()
	font = pygame.font.Font("fonts/starjedi/Starjedi.ttf", 20)
        label = font.render("Battle", 1, BLUE)
        screen.blit(label,(self._width/32,self._height/3))
	self.display_button(screen,"Start",
	self._width/32,self._height/1.1)
	self.display_button(screen,"Stop",
	(self._width/32)+110,self._height/1.1)
	self.display_button(screen,"view core",
	(self._width/32)+220,self._height/1.1)
	self.draw_memory(screen,400)
        self.display_label(screen,"File",
	screen.get_width()/32,(screen.get_height()/2)-10)
        self.display_box(screen,
	screen.get_width()/32,(screen.get_height()/2)+10)
	self.display_button(screen,"Load",
	(self._width/32)+220,(screen.get_height()/2)+5)


    def add_sign(self,screen,inkey,tab):
	""" read filename by sign """
        x = screen.get_width()/32+5
        y = screen.get_height()/2+10
        if inkey == K_BACKSPACE:
            self._filename = self._filename[0:-1]
            screen.fill((0,0,0))
            self.on_init(screen)
        elif inkey <= 127:
            self._filename+=chr(inkey)
	self._filename = string.join(self._filename,"")
        self.display_label(screen,self._filename,x,y)

    def get_filename(self):
	return self._filename

    def compile(self):
	pass

    def display_error(self,message):
	pass

    def draw_memory(self,screen,core_size):
	columns = int((self._width/20)-5)
	rows = int(core_size/columns)
	for x in range(columns):
	    for y in range(rows):
	        self.draw_cell(screen,BLUE,
	        (self._width/32)+21*x,self._height/32+11*y, 1)

    def draw_cell(self,screen,color,x,y,fill):
	pygame.draw.rect(screen, color,
        (x,y,20,10),fill)



