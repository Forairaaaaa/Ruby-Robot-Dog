/*
同步读指令，回读ID1与ID2两个舵机的位置与速度信息
*/

#include <SCServo.h>

SMSBL sm;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(1000000);
  sm.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  uint8_t ID[] = {1, 2};
  uint8_t rxPacket[4];
  int16_t Position;
  int16_t Speed;
  
  sm.syncReadPacketTx(ID, sizeof(ID), SMSBL_PRESENT_POSITION_L, sizeof(rxPacket));//同步读指令包发送

  uint8_t i;
  for(i=0; i<sizeof(ID); i++){
    //接收ID[i]同步读返回包
    if(!sm.syncReadPacketRx(ID[i], rxPacket)){
     Serial.print("ID:");
     Serial.println(ID[i]);
     Serial.println("sync read error!");
     continue;//接收解码失败
    }
    Position = sm.syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位
    Speed = sm.syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位
    Serial.print("ID:");
    Serial.println(ID[i]);
    Serial.print("Position:");
    Serial.println(Position);
    Serial.print("Speed:");
    Serial.println(Speed);
  }
  delay(10);
}
