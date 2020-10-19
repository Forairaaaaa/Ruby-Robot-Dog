# 平面二自由度并联臂解算

import numpy as np 


# 主动臂偏转角
theta1 = 0
theta2 = 0

# 各臂长度
e  = 7
l1 = 30
l2 = 80

# 符号函数
def sgnShit(i):
	if(i==1):
		return 1
	elif(i==2):
		return -1
	else:
		return 0

# 逆解函数
def calculation(x=0, y=0, i=1):
	# 坐标系平移
	x = x+5
	y = y-70

	E = (-2)*l1*y
	F = (-2)*l1*(x-(sgnShit(i)*e))
	G = (x*x) + (y*y) + (e*e) + (l1*l1) - (l2*l2) - (2*sgnShit(i)*e*x)
	print(E, F, G)

	theta = 2*(np.arctan(((-1)*E + sgnShit(i)*(np.sqrt(E*E - G*G + F*F))) / (G - F)))
	print(theta)

	return (theta*180)/np.pi

x = 0
y = 30
print(calculation(x=x, y=y, i=2),calculation(x=x, y=y, i=1))