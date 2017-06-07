#!/usr/bin/python
import pygame, string
from pygame.locals import *
from abc import *#ABCMeta, abstract method

#BLUE = (128,0,255)
BLUE = (133,139,222)
WHITE = (255,255,255)

class Scene:
    __metaclass__=ABCMeta

    @abstractmethod
    def on_init(self,screen):
        pass
    @abstractmethod
    def add_sign(self,screen,inkey,tab):
        pass

    @abstractmethod
    def display_info(self,screen,message,n=0):
        pass

    def display_box(self,screen,x,y, width=200, height=20, color=BLUE):
	rect = pygame.draw.rect(screen, color,
        (x,y,width,height), 1)
        self._boxes.append(rect)

    def clear_textbox(self,screen,rect):
       pygame.draw.rect(screen, (0,0,0),
       (rect[0],rect[1],rect[2],rect[3]),0)
       self.display_box(screen,rect[0],rect[1],rect[2],rect[3])


    def display_label(self,screen,_string,x,y,color=BLUE):
        myfont = pygame.font.SysFont("monospace", 20)
        label = myfont.render(_string, 1, color)
        screen.blit(label, (x, y))
        return label

    def display_bold_label(self,screen, text,x,y,size=20):
	font = pygame.font.Font("fonts/starjedi/Starjedi.ttf", size)
        label = font.render(text, 1, BLUE)
        screen.blit(label, (x, y))
        return label

    def create_button(self,screen,text,x,y):
        rect = self.display_button(screen,text,x,y)
        self._sprites[0].append(rect)
        self._sprites[1].append(str(text))
        #print self._sprites

    def display_button(self,screen,text,x,y):
	rect = pygame.Rect(x,y,100,30)
	pygame.draw.rect(screen, BLUE, rect, 0)
        font = pygame.font.Font("fonts/starjedi/Starjedi.ttf", 16)
        label = font.render(text, 1, (0,0,0))
        screen.blit(label, (x+10, y+2))
        return rect
            

    def light_up(self,screen, rect):
        index = self._boxes.index(rect)
        rest = abs(index-1)
        self.light_off(screen,self._boxes[rest])
        x = rect[0]
        y = rect[1]
        width = rect[2]
        height = rect[3]
        self.display_box(screen,x,y, width, height, WHITE)
        self._highlighted = index

    def light_off(self,screen,rect):
        self.display_box(screen,rect[0],rect[1],rect[2],rect[3], BLUE)


class Logger(Scene):
    def __init__(self):
	self._sprites = [[] for i in range(2)]
        self._temp = []
        self._login = []
        self._password = []
        self._boxes = []
        self._highlighted = 0

    def on_init(self,screen):
	font = pygame.font.Font("fonts/starjedi/Starjhol.ttf", 46)
        label = font.render("Core Wars", 1, BLUE)
        screen.blit(label,
       ((screen.get_width()/4)-20,screen.get_height()/6))
        #self.display_bold_label(screen,"Core Wars",(screen.get_width()/4)-20,screen.get_height()/6,46)
        self.display_label(screen,"Login",
	screen.get_width()/4,(screen.get_height()/3)+20)
        self.display_box(screen,
	screen.get_width()/4,(screen.get_height()/3)+40)
        self.display_label(screen,"Password",
	screen.get_width()/4,(screen.get_height()/2)-10)
        self.display_box(screen,
	screen.get_width()/4,(screen.get_height()/2)+10)
	self.create_button(screen,"Sign in",201,313)
	self.create_button(screen,"Sign up",201,360)
        self.light_up(screen,self._boxes[self._highlighted])

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

    def display_info(self,screen,message,n=0):
	""" Display message """
	screen.fill((0,0,0))
	self.display_label(screen,message,
	screen.get_width()/4-40,(screen.get_height()/3-10))
	self.__init__()
	#self.on_init(screen)



class Game(Scene):
    """ Main game scene """
    def __init__(self):
	self._sprites = [[] for i in range(2)]
	self._filename = []
        self._core_size_str = []
        self._core_size = 400
	self._core = []
        self._players = []
        self._players_str = ""
        self._battle_status = "Server, halo?"
        self._boxes = []
        self._highlighted = 0
        self._info = ""


    def on_init(self,screen):
        screen.fill((0,0,0))
	self._width = screen.get_width()
	self._height = screen.get_height()
        self.display_bold_label(screen,'Battle',
self._width/32,self._height/3)
        if len(self._sprites[0])==0:
	    self.create_button(screen,"Start",21,454)
	    self.create_button(screen,"Stop",(self._width/32)+110,self._height/1.1)
	    self.create_button(screen,"Core",(self._width/32)+220,self._height/1.1)
	    self.create_button(screen,"Scores",(self._width/32)+330,self._height/1.1)
	    #self.create_button(screen,"Load",(self._width/32)+220,(screen.get_height()/2)-15)
        else:
            for i in range(len(self._sprites[0])):
                rect = self._sprites[0][i]
                self.display_button(screen,self._sprites[1][i],rect[0],rect[1])
	self.draw_memory(screen)
        self.display_label(screen,"File",
	screen.get_width()/32,(screen.get_height()/2)-30)
        self.display_label(screen,"Battle status:",26,285)
        self.display_bold_label(screen,self._battle_status,199,282,16)
        self.display_label(screen,"Core size:",26,310)
        if not self._boxes:
            self.display_box(screen,
	screen.get_width()/32,(screen.get_height()/2)-10)
            self.display_box(screen,146,311, 50, 20)
        self.light_up(screen,self._boxes[self._highlighted])
        self.display_users(screen)
        self.display_label(screen,self._info,26, 351)
        self.display_label(screen,self._filename,screen.get_width()/32,(screen.get_height()/2)-10)
        self.display_label(screen,self._core_size_str,146,311)


    def add_sign(self,screen,inkey,tab):
	""" Read sign of textbox input """
        # get highlighted box 
        rect = self._boxes[self._highlighted]
        x = rect[0]
        y = rect[1]
        if self._highlighted==0:
            self.add_sign_to_filename(screen,inkey,x,y)
        else:
            self.add_sign_to_size(screen, inkey,x,y,rect[2],rect[3])
            

    def add_sign_to_filename(self,screen,inkey,x,y):
        if inkey == K_BACKSPACE:
            self._filename = self._filename[0:-1]
            screen.fill((0,0,0))
            self.on_init(screen)
        elif inkey <= 127:
            self._filename+=chr(inkey)
	self._filename = string.join(self._filename,"")
        self.display_label(screen,self._filename,x,y)

    def add_sign_to_size(self,screen,inkey,x,y, width,height):
        if inkey == K_BACKSPACE:
            self._core_size_str = self._core_size_str[0:-1]
            screen.fill((0,0,0))
            self.on_init(screen)
        elif inkey >= 48 and inkey <= 57:
            self._core_size_str+=chr(inkey)
        else:
            return
	self._core_size_str = string.join(self._core_size_str,"")
        self.display_label(screen,self._core_size_str,x,y)


    def get_filename(self):
	return self._filename


    def save_users(self,screen,users):
        self._players = users.split(",")
        if len(self._players)>1:
	    user1 = self._players[0]
            self._players[0] = user1[2:len(user1)-1]
            user2 = self._players[1]
            self._players[1] = user2[2:len(user2)-2]
            self.change_battle_status(screen,'Ready to go (load file)')
            self._players_str = self._players[0]+' vs. '+self._players[1]
        else:
	    user1 = self._players[0]
            self._players[0] = user1[2:len(user1)-2]
            self.change_battle_status(screen,'Waiting for second player')
            self._players_str = self._players[0]
        self.display_users(screen)

    def display_users(self,screen):
        self.display_bold_label(screen,self._players_str,121,170,16)


    def change_battle_status(self,screen,status):
        """Change current battle status for given string: waiting for second player, ready to go, in progres, finished"""
        self._battle_status = status
        print status
        self.on_init(screen)


    def display_info(self,screen,message,n=0):
        self._info = message
        screen.fill((0,0,0))
        self.on_init(screen)
	


    def draw_memory(self,screen):
        """Draw current core status"""
	rows = 15 #int((self._width/20)-5)
	columns = int(self._core_size/rows) #int(self._core_size/columns)
        width = 670/columns
	for x in range(columns):
	    for y in range(rows):
	        self.draw_cell(screen,BLUE, 1,
	        width*x+20,10*y+17, width)


    def draw_cell(self,screen,color,fill,x,y,width=20,height=10):
	pygame.draw.rect(screen, color,
        (x,y,width,height),fill)




class Statistics(Scene):

# TODO:
# usuniecie konta

    def __init__(self):
        self._boxes = []
        self._sprites = [[] for i in range(2)]
        self._convict = []
        self._highlighted = 0

    def on_init(self,screen):
        screen.fill((0,0,0))
        self.display_bold_label(screen,'Statistics',210,20, 30)
        self.display_bold_label(screen,'My Worriors',28,104-30)
        self.display_box(screen,28,130-30,250,300)
        self.display_bold_label(screen,'users',300+100,104-30)
        self.display_box(screen,300+100,130-30,250,300)
        self.create_button(screen,'back',547,455)
        self.display_box(screen,36, 430)
        self.light_up(screen, self._boxes[-1])
        self.create_button(screen,'remove',36,455)

    def add_sign(self,screen,inkey,tab):
       """Add sign to warrior name that will be removed"""
       rect = self._boxes[self._highlighted]
       x = rect[0]
       y = rect[1]
       if inkey == K_BACKSPACE: 
           self._convict = self._convict[0:-1]
           self.clear_textbox(screen,rect)
           self.light_up(screen, rect)
       elif inkey <= 127:
           self._convict+=chr(inkey)
       self._convict = string.join(self._convict,"")
       self.display_label(screen,self._convict,x,y)


    def display_info(self,screen,message,n=0):
        self.clear_textbox(screen,self._boxes[n])
        nb = len(message)
        for i in range(nb):
            self.display_label(screen,str(message[i][0])+' : '+str(message[i][1]),self._boxes[n][0], self._boxes[n][1]+20*i)

    def get_convict(self):
        return self._convict

