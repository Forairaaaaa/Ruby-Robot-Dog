/*
 * Drive.cpp
 * ���ڶ���ײ���������
 * ����: 2020.9.30
 * ����: Forairaaaaa
 */

#include "Drive.h"
#include <SCServo.h>

SCSCL sc;               // ʵ�����������



/******************************************���ڼ�ģʽ******************************************/
// ����0��1��ʼ��
void Drive_Serial_Init()
{
    Serial.begin(115200);    // USB
    Serial1.begin(1000000);  // Servo
    sc.pSerial = &Serial1;
    delay(1000);
}

/*
 * ���ڴ���ģʽ
 * ����0(USB) --> ����1(Servo)
 * i(0=���ݣ�1=��ʼ��)
*/
void Serial_Transmit(bool i)
{
    int inByte = 0;              // incoming serial byte
    if(i){                       // ��ʼ��
        Serial.begin(115200);    // USB
        Serial1.begin(1000000);  // Servo
    }
    else{                        // ����
        if(Serial.available() > 0){
            inByte = Serial.read();
            Serial1.write(inByte);
        }
        if(Serial1.available() > 0){
            inByte = Serial1.read();
            Serial.write(inByte);
        }
    }
}


/******************************************����˶�����******************************************/
// �趨���λ��  ��Set_Action ��Ч��
void Set_Position(u8 thigh_Id, u8 shank_Id, u8 hip_Id,   
                  u16 thigh_P, u16 shank_P, u16 hip_P, u16 speed)
{
    sc.RegWritePos(thigh_Id, thigh_P, 0, speed);
    sc.RegWritePos(shank_Id, shank_P, 0, speed);
    sc.RegWritePos(hip_Id, hip_P, 0, speed);
}


// ����˶�ִ��
void Set_Action(){
    sc.RegWriteAction();
}



/******************************************�������******************************************/
// ���������Ϣ
int Read_FeedBack(int ID){
    return(sc.FeedBack(ID));
}

// ����λ��
int Read_Pos(int ID){
    return(sc.ReadPos(ID));
}

// ��������
int Read_Load(int ID){
    return(sc.ReadLoad(ID));
}


/******************************************���Ժ���******************************************/
// ҡ�ڲ���
void Waddles()
{   
    char i=40;
    delay(300);
    sc.RegWritePos(3, 480+i, 0, 400);
    sc.RegWritePos(6, 536+i, 0, 400);
    sc.RegWritePos(9, 491-i, 0, 400);
    sc.RegWritePos(12, 525-i, 0, 400);
    sc.RegWriteAction();

    delay(300);
    sc.RegWritePos(3, 480-i, 0, 400);
    sc.RegWritePos(6, 536-i, 0, 400);
    sc.RegWritePos(9, 491+i, 0, 400);
    sc.RegWritePos(12, 525+i, 0, 400);
    sc.RegWriteAction();

}

// ſ�¶�����
void GetDown(u16 speed)
{
    sc.RegWritePos(1, 930, 0, speed);
    sc.RegWritePos(2, 706, 0, speed);
    sc.RegWritePos(3, 480, 0, speed);

    sc.RegWritePos(4, 104, 0, speed);
    sc.RegWritePos(5, 299, 0, speed);
    sc.RegWritePos(6, 536, 0, speed);

    sc.RegWritePos(7, 903, 0, speed);
    sc.RegWritePos(8, 726, 0, speed);
    sc.RegWritePos(9, 491, 0, speed);

    sc.RegWritePos(10, 154, 0, speed);
    sc.RegWritePos(11, 304, 0, speed);
    sc.RegWritePos(12, 525, 0, speed);
    sc.RegWriteAction();
}