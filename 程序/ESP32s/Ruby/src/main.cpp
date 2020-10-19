/*
 * main.cpp
 * 主函数
 * 日期: 2020.10.6
 * 作者: Forairaaaaa
 */

#include <Arduino.h>
// #include "Body.h"
#include "Serialcmd.h"


void run_thing(float step_L, float step_R, float step_h);



void setup()
{
    // Serial_Transmit(1);
    Body_init();
    delay(1000);
}

void loop()
{
    // Serial_Transmit();
    // In_kine_Test();
    // run_test();

    DOF8_Serial_CMD();

}

