import pygame
from Window import *
from Mushroom import *

class Game:
    def __init__(self):
        self.window = Window()
        
        self.mushroom = Mushroom()

    def HandleInput(self):
        pass


    def Update(self):
        self.window.Update()

        self.mushroom.Update()


    def Render(self):
        self.window.BeginDraw()
        # draw
        self.mushroom.Render(self.window)
        self.window.EndDraw()

    # get set methods
    def GetWindow(self):
        return self.window