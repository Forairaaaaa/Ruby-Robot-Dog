/*
 * Body.h
 * 整体控制
 * 日期: 2020.10.6
 * 作者: Forairaaaaa
 */

#ifndef _BODY_H
#define _BODY_H

#include "Legs.h"


/***************************************初始化***************************************/

void Body_init(int x=0, int y=0);     // Ruby初始化，开启串口，四腿回归原点
void Body_Gohome(int x=0, int y=0);   // 所有腿回归原点


/***************************************8自由度步态**************************************/

// 最小Jerk轨迹规划
// t:时间量   Xs:X起点   Xf:X终点   Zs:Z起点   H:抬腿高度   Ts:周期   D_Sup:支撑相占空比  (Ys,Yf同理)
void Jerk_Trail(float t=0,
                float Xs=0, float Xf=0,
                float Ys=0, float Yf=0,
                float Zs=0, float H=0,
                float Ts=1, float D_Sup=0.5);


// 简单对角步态
// t:时间量   step:步长   step_h:步高   body_h:位高(基于足端原点)   Ts:步态周期
void Gait_TROT(float t, float step=0, float step_h=0, float body_h=0, float Ts=1);


// 单腿对角步态， Gait_Action()生效
// t:时间量   step:步长   step_h:步高   body_h:位高   Ts:步态周期   leg: 1(LF)、2(RF)、3(LB)、4(RB)  
void Gait_TROT_Senior(float t, float step=0, float step_h=0, float body_h=0, float Ts=1, u8 leg=1);
// 步态执行
void Gait_Action();                   
// 由步态数据集生成步态
void Gait_TROT_FromSet(float t, float Ts=1);

// 修改数据集   step:步长   step_h:步高   body_h:位高   leg: 1(LF)、2(RF)、3(LB)、4(RB)
void TROT_DataSet(u8 leg=1, float step=0, float step_h=0, float body_h=0);

// 8自由度应用层（未完善）
/*

    _____
  1|     |2       V_y
   |     |      ^
   |     |      |
  3|_____|4     | 
                 ——————> V_x

// Pitch：俯仰角    Roll：滚动角
 
   取值范围及对应表：
                         0   1   2   3   4   5   6   7   8   9
                        -5  -4  -3  -2  -1   0   1   2   3   4

// step_max：步长极限值    step_h：步高

*/

void DOF8_TROT(float step_l=0, float step_r=0, float Pitch=0, float Roll=0, float speed=0.02, float step_max=25, float step_h=4);



/***************************************测试函数***************************************/
void In_kine();                                   // 逆解测试
void In_kine_Test();                              // 四腿逆解动作测试
void GetPosition();                               // 腿部关节反馈测试

void TROT_test();
void TROT_S_test();                               // 数据集步态测试
void run_test();

#endif