/*
 * Legs.cpp
 * �Ȳ�������
 * ����: 2020.9.30
 * ����: Forairaaaaa
 * 
 * 300'(0~1023) -> 0.3'  -> 3.41/'
 */

#include "Legs.h"

/****************************************��ʼ��****************************************/
// �Ȳ���ֵ��ʼ��
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


/***************************************�ײ��˶�ִ��***************************************/
// ʹ�˶�ִ����Ч
void Legs::Go_Action(){
    Set_Action();
}

// �Ȳ��ع���λ  ������С�ȶ������ƫ����(�Ƕ�)��
void Legs::Go_Mid(int offsets, u16 speed)
{
    u16 shank_P = 0;
    if(hip_Id==3 || hip_Id==9){     // ����������
        shank_P=shank_Mid-(offsets/0.3);
    }else{
        shank_P=shank_Mid+(offsets/0.3);
    }
    Set_Position(thigh_Id, shank_Id, hip_Id, thigh_Mid, shank_P, hip_Mid, speed);
}


// �����Ȳ���λ��
void Legs::Go_Position(u16 thigh_P, u16 shank_P, u16 hip_P, u16 speed){
    Set_Position(thigh_Id, shank_Id, hip_Id, thigh_P, shank_P, hip_P, speed);
}


/***************************************�ؽڷ���***************************************/
// ����λ��
int Legs::thigh_Pos(){
    return(Read_Pos(thigh_Id));}
// ���ȸ���
int Legs::thigh_Load(){
    return(Read_Load(thigh_Id));}
// С��λ��
int Legs::shank_Pos(){
    return(Read_Pos(shank_Id));}
// С�ȸ���                             
int Legs::shank_Load(){
    return(Read_Load(shank_Id));}
// ƨ��λ��
int Legs::hip_Pos(){
    return(Read_Pos(hip_Id));}
// ƨ�ɸ���    
int Legs::hip_Load(){
    return(Read_Load(hip_Id));}


// ��ӡ���ؽ�λ�ã������ӡͷ�����֣�
void Legs::Print_Pos(String name)
{
    name = name + "_Pos: T: " + thigh_Pos() + " S: " + shank_Pos() + " H: " + hip_Pos();
    Serial.println(name);
}

// ��ӡ���ؽڸ��أ������ӡͷ�����֣�
void Legs::Print_Load(String name)
{
    name = name + "_Load: T: " + thigh_Load() + " S: " + shank_Load() + " H: " + hip_Load();
    Serial.println(name);
}


/***************************************8���ɶȽ���***************************************/
// ���  (x, y, ����theta��)
float Legs::In_kinematic(float x, float y, u8 i)
{   
    // ����ԭ�������ƫ��
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


// ���ź���
int Legs::Get_Sgn(u8 i)
{
    if(i==1)
        return 1;
    else
        return -1;
}


// ����˶�������ϵ   p(x,y)Ϊԭ��
void Legs::Go_Coordinate(float x, float y, bool action, u16 speed)
{
    float theta_1 = In_kinematic(x,y,1);               // ����������ת��
    float theta_2 = In_kinematic(x,y,2);

    if(theta_2>0)                                      // ת��theta_2����
        theta_2 = 180-theta_2;
    else
        theta_2 = -(180+theta_2);

    if(hip_Id==3 || hip_Id==9){                        // ����������
        u16 shank_P = shank_Mid-(theta_1*3.41);  
        u16 thigh_P = thigh_Mid+(theta_2*3.41);
        Set_Position(thigh_Id, shank_Id, hip_Id, thigh_P, shank_P, hip_Mid, speed);

    }else{                                             // �Ҳ���
        u16 shank_P = shank_Mid+(theta_1*3.41);
        u16 thigh_P = thigh_Mid-(theta_2*3.41);
        Set_Position(thigh_Id, shank_Id, hip_Id, thigh_P, shank_P, hip_Mid, speed);
    }

    if(action)                                         // ����ִ��
        Set_Action();
}





/***************************************���Ժ���***************************************/
