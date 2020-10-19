import pygame
import serial
import time


'''串口初始化'''
serial = serial.Serial('COM3',115200)
# print(serial.readline())


'''pygame初始化'''
pygame.init()
screen = pygame.display.set_mode((500,700))
# background=pygame.image.load(r"cate.png")
pygame.display.set_caption('controller')



'''手柄定义'''
pygame.joystick.init()                                 # 初始化
joystick = pygame.joystick.Joystick(0)                 # 创建对象
joystick.init()                                               
print('Controller name is : ', joystick.get_name())    # 显示名称




'''处理函数'''
def contrl():

    vA,vB,a,b,c,d=5,5,5,5,5,5

    Lx = -int(LSx * 4) + 5
    Ly = -int(LSy * 4) + 5
    Rx = -int(RSx * 4) + 5
    Ry = -int(RSy * 4) + 5

    # a = Lx
    # b = Ly
    # c = Rx
    # d = Ry

    if Ly == 5:           # 静止
        if Lx == 5:
            a = 5
            b = 5
        else:             # 左右
            a = 5-(Lx-5)
            b = 5+(Lx-5)

    elif Ly > 5:          # 前进
        if Lx == 5:
            a = Ly
            b = Ly
        elif Lx > 5:      # 左
            a = Ly-(Lx-5)
            b = Ly
            if a<=5:
                a = 6
        elif Lx < 5:      # 右
            a = Ly
            b = Ly+(Lx-5)
            if b<=5:
                b = 6
    elif Ly < 5:          # 后退
        if Lx == 5:
            a = Ly
            b = Ly
        elif Lx > 5:      # 左
            a = Ly+(Lx-5)
            b = Ly
            if a>=5:
                a = 4
        elif Lx < 5:      # 右
            a = Ly
            b = Ly-(Lx-5)
            if b>=5:
                b = 4

    if Ry != 5:           # 姿态
        c = 5-(Ry-5)
    elif Rx != 5:
        c = 5
        d = 10-Rx

    if Shot != 0:
        if Shot > 0.90:        # 左扳机键  减速
            a = 0
        elif Shot < -0.90:      # 右扳机键  加速
            a = 5
            b = 0

    pack=str(a)+','+str(b)+','+str(c)+','+str(d)+','
    # print(pack)
    serial.write(pack.encode("utf-8"))

    time.sleep(0.1)

    return pack

    



'''主循环'''
done = False
while done==False:
    for event in pygame.event.get():             # 事件处理
        if event.type == pygame.QUIT:
            done=True                                        # 退出循环


    LSx = round(joystick.get_axis(0),3)
    LSy = round(joystick.get_axis(1),3)

    RSx = round(joystick.get_axis(4),3)
    RSy = round(joystick.get_axis(3),3)

    Shot = round(joystick.get_axis(2),3)

    BX = joystick.get_button(2)
    BB = joystick.get_button(1)

    #print(int((1000*SHOT)/4))

    pack = contrl()

    myfont=pygame.font.Font(None,45)
    white=255,255,255
    black=0,0,0
    textImage=myfont.render(str(pack),True,white)
    screen.fill(black)
    screen.blit(textImage,(0,655))
    pygame.display.update()




'''结束'''
pygame.quit()

a,b,c,d=5,5,5,5
pack=str(a)+','+str(b)+','+str(c)+','+str(d)+','
# print(pack)
serial.write(pack.encode("utf-8"))

serial.close()









'''
import serial
serial = serial.Serial('COM3',115200)
print(serial.readline())
serial.write(shit.encode("utf-8"))
serial.close()
'''



        
