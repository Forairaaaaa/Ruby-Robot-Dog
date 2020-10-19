/*
 * Drive.h
 * 串口舵机底层驱动
 * 日期: 2020.9.30
 * 作者: Forairaaaaa
 */

#ifndef _DRIVE_H
#define _DRIVE_H

#include <Arduino.h>
#include "INST.h"

/******************************************串口及模式******************************************/
void Drive_Serial_Init();                                    // 串口0、1初始化
void Serial_Transmit(bool i=0);                              // 串口传递模式 （i=1时执行串口初始化）


/******************************************舵机运动******************************************/
void Set_Position(u8 thigh_Id, u8 shank_Id, u8 hip_Id,       // 设定舵机位置 （Set_Action生效）
                  u16 thigh_P, u16 shank_P, u16 hip_P, u16 speed=1500);
void Set_Action();                                           // 舵机运动执行


/******************************************舵机反馈******************************************/
int Read_FeedBack(int ID);                                   // 反馈舵机信息
int Read_Pos(int ID);                                        // 反馈位置
int Read_Load(int ID);                                       // 反馈负载


/******************************************测试函数******************************************/
void Waddles();                                              // 摇摆测试
void GetDown(u16 speed=600);                                 // 趴下动作组


#endif
