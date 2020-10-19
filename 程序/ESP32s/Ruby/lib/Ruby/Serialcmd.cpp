/*
 * Serialcmd.cpp
 * ���ڿ��ƽӿ�
 * ����: 2020.10.13
 * ����: Forairaaaaa
 */

#include "Serialcmd.h"
#include <Ticker.h>
 
Ticker ticker;                   // ����Ticker����ʵ�ֶ�ʱ����



String inputString="";           // ���������ַ���
int cmd[]={5,5,5,5};             // ת������   ( step_l,step_r,Ptich,Roll )
int mark=0;
float speed_In = 0.01;           // �ٶ�ֵ


// ���ڶ�����
void DOF8_Serial_CMD()
{
    
    Serial2.begin(115200);           // �򿪴���2
    Serial2.println("2.4G Serial on...");

    ticker.attach(0.15, Serial_Get_cmd);

    while(1){
        DOF8_TROT(cmd[0]-5, cmd[1]-5, cmd[2]-5, cmd[3]-5, speed_In);
    } 
}


// �Ӵ��ڻ�ȡ����
void Serial_Get_cmd()
{
    while(Serial2.available()){                       // ������2�пɶ�ֵ
            inputString += char(Serial2.read());      // ����д��
            delay(1);
            mark = 1;
        }

    if(mark==1){                                              // ���д��ڶ�ֵ       

        int j = 0;                                            // �ָ��л���־
    
        for(int i=0; i<inputString.length(); i++){            // �����ַ���
            
            if(inputString[i] == ',')                         // �жϷָ���(,)
                j++;                                          // д������
            else                                              
                cmd[j] = (inputString[i] - '0');
            if(j==4)                                          // ��ս��ջ���
                break;    
            }

            inputString="";                                   // ����ַ���
            mark=0;                                           // ��־����

            while(Serial2.read()>=0);                         // ��ս��ջ���

        if(cmd[0]==0){                                        // �����ٶ�
            speed_In = 0.01;
            cmd[0] = 5;}
        else if(cmd[1]==0){
            speed_In = 0.02;
            cmd[1] = 5;}

    }else{                                                    // ���޴��ڶ�ֵ
        for(int j=0;j<4;j++)
            cmd[j]=5;                                         // ��ֹ
    }
}

