# 摆线规划测试
# 参考https://zhuanlan.zhihu.com/p/69869440

import tkinter                               
import matplotlib
matplotlib.use('TkAgg')                         # GUI
from mpl_toolkits.mplot3d import Axes3D       # 三维
import matplotlib.pyplot as plt
import numpy as np


fig = plt.figure()                           # 三维
ax = fig.gca(projection='3d')



# 时间量
t = np.linspace(0,0.5,100)  

Ts    = 1     # 步态周期              
D_Sup = 0.5   # 支撑相占空比

Xs    = 20     # 起点x
Ys    = 0    # 起点y
Zs    = 0     # 起点z

Xf    = -20    # 终点x
Yf    = 0    # 终点y
H     = 10    # 跨腿高度



# 摆线
sigma = (2*np.pi*t)/(D_Sup*Ts)
Xexp  = (Xf-Xs)*((sigma-np.sin(sigma))/(2*np.pi))+Xs
Yexp  = (Yf-Ys)*((sigma-np.sin(sigma))/(2*np.pi))+Ys
Zexp  = H*((1-np.cos(sigma))/2)+Zs
ax.plot(Xexp,Yexp,Zexp)
# plt.plot(Xexp,Zexp)



# 支撑线
Xs = -20
Xf = 20
H  = 0

sigma = (2*np.pi*t)/(D_Sup*Ts)
Xexp  = (Xf-Xs)*((sigma-np.sin(sigma))/(2*np.pi))+Xs
Yexp  = (Yf-Ys)*((sigma-np.sin(sigma))/(2*np.pi))+Ys
Zexp  = H*((1-np.cos(sigma))/2)+Zs
ax.plot(Xexp,Yexp,Zexp)
# plt.plot(Xexp,Zexp)

ax.legend()
plt.show()

