
import pygame, sys

class main:
    def __init__(self):
        # 初始化 pygame
        pygame.init()
        # 创建一个窗口
        window = pygame.display.set_mode([640, 480])

        mushroom = pygame.image.load(r'F:\workspace\BouncingMushroom-usePygame\BouncingMushroom-simple\Assets\Mushroom.png')

        mushroom_rect = mushroom.get_rect()

        increment = [1, 1]

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()

            if (mushroom_rect.x + mushroom_rect.w > 640 and increment[0] > 0) or (mushroom_rect.x < 0 and increment[0]<0): 
                increment[0] = -increment[0]

            if (mushroom_rect.y + mushroom_rect.h > 480 and increment[1] > 0) or (mushroom_rect.y < 0 and increment[1]<0):
                increment[1] = -increment[1]

            mushroom_rect.x += increment[0]
            mushroom_rect.y += increment[1]

            # 清除屏幕
            window.fill((0,0,0))
            # draw here
            window.blit(mushroom, mushroom_rect.topleft)
            # 绘制屏幕
            pygame.display.update()


if __name__ == "__main__":
    main()