/*
 * Drive.h
 * ���ڶ���ײ�����
 * ����: 2020.9.30
 * ����: Forairaaaaa
 */

#ifndef _DRIVE_H
#define _DRIVE_H

#include <Arduino.h>
#include "INST.h"

/******************************************���ڼ�ģʽ******************************************/
void Drive_Serial_Init();                                    // ����0��1��ʼ��
void Serial_Transmit(bool i=0);                              // ���ڴ���ģʽ ��i=1ʱִ�д��ڳ�ʼ����


/******************************************����˶�******************************************/
void Set_Position(u8 thigh_Id, u8 shank_Id, u8 hip_Id,       // �趨���λ�� ��Set_Action��Ч��
                  u16 thigh_P, u16 shank_P, u16 hip_P, u16 speed=1500);
void Set_Action();                                           // ����˶�ִ��


/******************************************�������******************************************/
int Read_FeedBack(int ID);                                   // ���������Ϣ
int Read_Pos(int ID);                                        // ����λ��
int Read_Load(int ID);                                       // ��������


/******************************************���Ժ���******************************************/
void Waddles();                                              // ҡ�ڲ���
void GetDown(u16 speed=600);                                 // ſ�¶�����


#endif
