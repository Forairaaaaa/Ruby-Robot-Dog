/*
 * Legs.h
 * 腿部对象定义
 * 日期: 2020.9.30
 * 作者: Forairaaaaa
 */

#ifndef _LEGS_H
#define _LEGS_H

#include <Arduino.h>
#include <math.h>
#include "Drive.h"
#include "INST.h"


// 臂长参数
#define le 7
#define l1 30
#define l2 80

// p(x,y)  (足端坐标所需偏移量)
#define x_offset  5
#define y_offseet -70


/* 机构简图：

               l1    le 
theta_2     @------@----|----@------@      theta_1
            -                      -
                -               -   l2
                    -        -
                        --
                            p(x, y)

*/

class Legs
{
private:
    // 舵机ID
    u8 thigh_Id = 1;
    u8 shank_Id = 2;
    u8 hip_Id   = 3;
    // 中位值
    u16 thigh_Mid  = 512;
    u16 shank_Mid  = 512;
    u16 hip_Mid    = 512;

public:
/****************************************初始化****************************************/
    Legs(u8 u_thigh_Id, u8 u_shank_Id, u8 u_hip_Id,         // 腿部数值初始化
         u16 u_thigh_Mid, u16 u_shank_Mid, u16 u_hip_Mid);
    ~Legs();


/***************************************底层运动执行***************************************/
    void Go_Action();                                       // 使运动执行生效
    void Go_Mid(int offsets=0, u16 speed=1500);             // 腿部回归中位 （传入小腿舵机向上偏移量(角度)）
    void Go_Position(u16 thigh_P, u16 shank_P, u16 hip_P, u16 speed=1500);  // 设置腿部各位置


/***************************************关节反馈***************************************/
    int thigh_Pos();                                        // 大腿位置
    int thigh_Load();                                       // 大腿负载
    int shank_Pos();                                        // 小腿位置
    int shank_Load();                                       // 小腿负载
    int hip_Pos();                                          // 屁股位置
    int hip_Load();                                         // 屁股负载
    void Print_Pos(String name="NamePlz");                  // 打印各关节位置，输入打印头（名字）
    void Print_Load(String name="NamePlz");                 // 打印各关节负载，输入打印头（名字）


/***************************************8自由度解算***************************************/
    float In_kinematic(float x, float y, u8 i);             // 逆解  (x, y, theta角)
    int Get_Sgn(u8 i);                                      // 符号函数
    void Go_Coordinate(float x, float y,                    // 足端运动至坐标  p(x,y)为原点
                       bool action=0, u16 speed=1500);      // action为1时立即执行




/***************************************12自由度解算***************************************/

/***************************************测试函数***************************************/


};





#endif