/*
 * Legs.cpp
 * 腿部对象定义
 * 日期: 2020.9.30
 * 作者: Forairaaaaa
 * 
 * 300'(0~1023) -> 0.3'  -> 3.41/'
 */

#include "Legs.h"

/****************************************初始化****************************************/
// 腿部数值初始化
Legs::Legs(u8 u_thigh_Id, u8 u_shank_Id, u8 u_hip_Id,   
           u16 u_thigh_Mid, u16 u_shank_Mid, u16 u_hip_Mid)
{
    thigh_Id  = u_thigh_Id;
    shank_Id  = u_shank_Id;
    hip_Id    = u_hip_Id;
    thigh_Mid = u_thigh_Mid  ;
    shank_Mid = u_shank_Mid  ;
    hip_Mid   = u_hip_Mid    ;
}

Legs::~Legs(){
}


/***************************************底层运动执行***************************************/
// 使运动执行生效
void Legs::Go_Action(){
    Set_Action();
}

// 腿部回归中位  （传入小腿舵机向上偏移量(角度)）
void Legs::Go_Mid(int offsets, u16 speed)
{
    u16 shank_P = 0;
    if(hip_Id==3 || hip_Id==9){     // 如果是左侧腿
        shank_P=shank_Mid-(offsets/0.3);
    }else{
        shank_P=shank_Mid+(offsets/0.3);
    }
    Set_Position(thigh_Id, shank_Id, hip_Id, thigh_Mid, shank_P, hip_Mid, speed);
}


// 设置腿部各位置
void Legs::Go_Position(u16 thigh_P, u16 shank_P, u16 hip_P, u16 speed){
    Set_Position(thigh_Id, shank_Id, hip_Id, thigh_P, shank_P, hip_P, speed);
}


/***************************************关节反馈***************************************/
// 大腿位置
int Legs::thigh_Pos(){
    return(Read_Pos(thigh_Id));}
// 大腿负载
int Legs::thigh_Load(){
    return(Read_Load(thigh_Id));}
// 小腿位置
int Legs::shank_Pos(){
    return(Read_Pos(shank_Id));}
// 小腿负载                             
int Legs::shank_Load(){
    return(Read_Load(shank_Id));}
// 屁股位置
int Legs::hip_Pos(){
    return(Read_Pos(hip_Id));}
// 屁股负载    
int Legs::hip_Load(){
    return(Read_Load(hip_Id));}


// 打印各关节位置，输入打印头（名字）
void Legs::Print_Pos(String name)
{
    name = name + "_Pos: T: " + thigh_Pos() + " S: " + shank_Pos() + " H: " + hip_Pos();
    Serial.println(name);
}

// 打印各关节负载，输入打印头（名字）
void Legs::Print_Load(String name)
{
    name = name + "_Load: T: " + thigh_Load() + " S: " + shank_Load() + " H: " + hip_Load();
    Serial.println(name);
}


/***************************************8自由度解算***************************************/
// 逆解  (x, y, 所解theta角)
float Legs::In_kinematic(float x, float y, u8 i)
{   
    // 坐标原点向足端偏移
    x = x+x_offset;
    y = y+y_offseet;

    float E = (-2)*l1*y;
    float F = (-2)*l1*(x-(Get_Sgn(i)*le));
    float G = (x*x)+(y*y)+(le*le)+(l1*l1)-(l2*l2)-(2*Get_Sgn(i)*le*x);

    double theta = 2*(atan(((-1)*E + Get_Sgn(i)*(sqrt(E*E - G*G + F*F))) / (G - F)));

    // Serial.println(E);
    // Serial.println(F);
    // Serial.println(G);
    // Serial.println(theta);

    theta = (theta*180)/M_PI;

    return theta;
}


// 符号函数
int Legs::Get_Sgn(u8 i)
{
    if(i==1)
        return 1;
    else
        return -1;
}


// 足端运动至坐标系   p(x,y)为原点
void Legs::Go_Coordinate(float x, float y, bool action, u16 speed)
{
    float theta_1 = In_kinematic(x,y,1);               // 逆解得主动臂转角
    float theta_2 = In_kinematic(x,y,2);

    if(theta_2>0)                                      // 转换theta_2方向
        theta_2 = 180-theta_2;
    else
        theta_2 = -(180+theta_2);

    if(hip_Id==3 || hip_Id==9){                        // 如果是左侧腿
        u16 shank_P = shank_Mid-(theta_1*3.41);  
        u16 thigh_P = thigh_Mid+(theta_2*3.41);
        Set_Position(thigh_Id, shank_Id, hip_Id, thigh_P, shank_P, hip_Mid, speed);

    }else{                                             // 右侧腿
        u16 shank_P = shank_Mid+(theta_1*3.41);
        u16 thigh_P = thigh_Mid-(theta_2*3.41);
        Set_Position(thigh_Id, shank_Id, hip_Id, thigh_P, shank_P, hip_Mid, speed);
    }

    if(action)                                         // 立即执行
        Set_Action();
}





/***************************************测试函数***************************************/
