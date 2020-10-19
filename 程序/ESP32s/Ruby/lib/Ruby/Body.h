/*
 * Body.h
 * �������
 * ����: 2020.10.6
 * ����: Forairaaaaa
 */

#ifndef _BODY_H
#define _BODY_H

#include "Legs.h"


/***************************************��ʼ��***************************************/

void Body_init(int x=0, int y=0);     // Ruby��ʼ�����������ڣ����Ȼع�ԭ��
void Body_Gohome(int x=0, int y=0);   // �����Ȼع�ԭ��


/***************************************8���ɶȲ�̬**************************************/

// ��СJerk�켣�滮
// t:ʱ����   Xs:X���   Xf:X�յ�   Zs:Z���   H:̧�ȸ߶�   Ts:����   D_Sup:֧����ռ�ձ�  (Ys,Yfͬ��)
void Jerk_Trail(float t=0,
                float Xs=0, float Xf=0,
                float Ys=0, float Yf=0,
                float Zs=0, float H=0,
                float Ts=1, float D_Sup=0.5);


// �򵥶Խǲ�̬
// t:ʱ����   step:����   step_h:����   body_h:λ��(�������ԭ��)   Ts:��̬����
void Gait_TROT(float t, float step=0, float step_h=0, float body_h=0, float Ts=1);


// ���ȶԽǲ�̬�� Gait_Action()��Ч
// t:ʱ����   step:����   step_h:����   body_h:λ��   Ts:��̬����   leg: 1(LF)��2(RF)��3(LB)��4(RB)  
void Gait_TROT_Senior(float t, float step=0, float step_h=0, float body_h=0, float Ts=1, u8 leg=1);
// ��ִ̬��
void Gait_Action();                   
// �ɲ�̬���ݼ����ɲ�̬
void Gait_TROT_FromSet(float t, float Ts=1);

// �޸����ݼ�   step:����   step_h:����   body_h:λ��   leg: 1(LF)��2(RF)��3(LB)��4(RB)
void TROT_DataSet(u8 leg=1, float step=0, float step_h=0, float body_h=0);

// 8���ɶ�Ӧ�ò㣨δ���ƣ�
/*

    _____
  1|     |2       V_y
   |     |      ^
   |     |      |
  3|_____|4     | 
                 ������������> V_x

// Pitch��������    Roll��������
 
   ȡֵ��Χ����Ӧ��
                         0   1   2   3   4   5   6   7   8   9
                        -5  -4  -3  -2  -1   0   1   2   3   4

// step_max����������ֵ    step_h������

*/

void DOF8_TROT(float step_l=0, float step_r=0, float Pitch=0, float Roll=0, float speed=0.02, float step_max=25, float step_h=4);



/***************************************���Ժ���***************************************/
void In_kine();                                   // ������
void In_kine_Test();                              // ������⶯������
void GetPosition();                               // �Ȳ��ؽڷ�������

void TROT_test();
void TROT_S_test();                               // ���ݼ���̬����
void run_test();

#endif