/*
 * Serialcmd.cpp
 * 串口控制接口
 * 日期: 2020.10.13
 * 作者: Forairaaaaa
 */

#include "Serialcmd.h"
#include <Ticker.h>
 
Ticker ticker;                   // 建立Ticker用于实现定时功能



String inputString="";           // 储存输入字符串
int cmd[]={5,5,5,5};             // 转换数组   ( step_l,step_r,Ptich,Roll )
int mark=0;
float speed_In = 0.01;           // 速度值


// 串口读命令
void DOF8_Serial_CMD()
{
    
    Serial2.begin(115200);           // 打开串口2
    Serial2.println("2.4G Serial on...");

    ticker.attach(0.15, Serial_Get_cmd);

    while(1){
        DOF8_TROT(cmd[0]-5, cmd[1]-5, cmd[2]-5, cmd[3]-5, speed_In);
    } 
}


// 从串口获取命令
void Serial_Get_cmd()
{
    while(Serial2.available()){                       // 当串口2有可读值
            inputString += char(Serial2.read());      // 数据写入
            delay(1);
            mark = 1;
        }

    if(mark==1){                                              // 如有串口读值       

        int j = 0;                                            // 分隔切换标志
    
        for(int i=0; i<inputString.length(); i++){            // 遍历字符串
            
            if(inputString[i] == ',')                         // 判断分隔符(,)
                j++;                                          // 写入数组
            else                                              
                cmd[j] = (inputString[i] - '0');
            if(j==4)                                          // 清空接收缓冲
                break;    
            }

            inputString="";                                   // 清空字符串
            mark=0;                                           // 标志置零

            while(Serial2.read()>=0);                         // 清空接收缓冲

        if(cmd[0]==0){                                        // 更换速度
            speed_In = 0.01;
            cmd[0] = 5;}
        else if(cmd[1]==0){
            speed_In = 0.02;
            cmd[1] = 5;}

    }else{                                                    // 如无串口读值
        for(int j=0;j<4;j++)
            cmd[j]=5;                                         // 静止
    }
}

