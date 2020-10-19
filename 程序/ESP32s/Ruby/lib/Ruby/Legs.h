/*
 * Legs.h
 * �Ȳ�������
 * ����: 2020.9.30
 * ����: Forairaaaaa
 */

#ifndef _LEGS_H
#define _LEGS_H

#include <Arduino.h>
#include <math.h>
#include "Drive.h"
#include "INST.h"


// �۳�����
#define le 7
#define l1 30
#define l2 80

// p(x,y)  (�����������ƫ����)
#define x_offset  5
#define y_offseet -70


/* ������ͼ��

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
    // ���ID
    u8 thigh_Id = 1;
    u8 shank_Id = 2;
    u8 hip_Id   = 3;
    // ��λֵ
    u16 thigh_Mid  = 512;
    u16 shank_Mid  = 512;
    u16 hip_Mid    = 512;

public:
/****************************************��ʼ��****************************************/
    Legs(u8 u_thigh_Id, u8 u_shank_Id, u8 u_hip_Id,         // �Ȳ���ֵ��ʼ��
         u16 u_thigh_Mid, u16 u_shank_Mid, u16 u_hip_Mid);
    ~Legs();


/***************************************�ײ��˶�ִ��***************************************/
    void Go_Action();                                       // ʹ�˶�ִ����Ч
    void Go_Mid(int offsets=0, u16 speed=1500);             // �Ȳ��ع���λ ������С�ȶ������ƫ����(�Ƕ�)��
    void Go_Position(u16 thigh_P, u16 shank_P, u16 hip_P, u16 speed=1500);  // �����Ȳ���λ��


/***************************************�ؽڷ���***************************************/
    int thigh_Pos();                                        // ����λ��
    int thigh_Load();                                       // ���ȸ���
    int shank_Pos();                                        // С��λ��
    int shank_Load();                                       // С�ȸ���
    int hip_Pos();                                          // ƨ��λ��
    int hip_Load();                                         // ƨ�ɸ���
    void Print_Pos(String name="NamePlz");                  // ��ӡ���ؽ�λ�ã������ӡͷ�����֣�
    void Print_Load(String name="NamePlz");                 // ��ӡ���ؽڸ��أ������ӡͷ�����֣�


/***************************************8���ɶȽ���***************************************/
    float In_kinematic(float x, float y, u8 i);             // ���  (x, y, theta��)
    int Get_Sgn(u8 i);                                      // ���ź���
    void Go_Coordinate(float x, float y,                    // ����˶�������  p(x,y)Ϊԭ��
                       bool action=0, u16 speed=1500);      // actionΪ1ʱ����ִ��




/***************************************12���ɶȽ���***************************************/

/***************************************���Ժ���***************************************/


};





#endif