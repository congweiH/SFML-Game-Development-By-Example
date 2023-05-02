
import pygame
from Window import *

class Mushroom:
    def __init__(self):
        
        self.sprite = pygame.image.load(r"F:\workspace\BouncingMushroom-usePygame\BouncingMushroom-frame\Assets\Mushroom.png")

        self.rect = self.sprite.get_rect()

        self.increment = [1, 1]

    # update and render methods
    def Update(self):
        self.Move()

    def Render(self, window : Window):
        window.Draw(self.sprite, self.rect.topleft)

    # other
    def Move(self):
        if (self.rect.topright[0] > 640 and self.increment[0] > 0) or \
            (self.rect.x < 0 and self.increment[0]<0): 
            self.increment[0] = -self.increment[0]

        if (self.rect.bottomleft[1] > 480 and self.increment[1] > 0) or \
            (self.rect.y < 0 and self.increment[1]<0):
            self.increment[1] = -self.increment[1]
        
        self.rect.x += self.increment[0]
        self.rect.y += self.increment[1]

    # get set methods
    def GetRect(self):
        return self.rect