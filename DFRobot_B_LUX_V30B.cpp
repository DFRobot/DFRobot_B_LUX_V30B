/*!
 * @file DFRobot_B_LUX_V30B.cpp
 * @brief Implementations of  methods in the class of DFRobot_B_LUX_V30B
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Fary](Fary_young@outlook.com)
 * @version  V1.0
 * @date  2020-12-03
 * @https://github.com/DFRobot/DFRobot_B_LUX_V30B
 */

#include <DFRobot_B_LUX_V30B.h>


DFRobot_B_LUX_V30B::DFRobot_B_LUX_V30B(uint8_t cEN, uint8_t scl, uint8_t sda)
{
  _deviceAddr = DFRobot_B_LUX_V30_IIC_Addr;
  _SCL = scl;
  _SDA = sda;
  _cEN = cEN;
}

void DFRobot_B_LUX_V30B::begin()
{
  pinMode(_SDA,OUTPUT);
  pinMode(_SCL,OUTPUT);
  pinMode(_cEN,OUTPUT);
  digitalWrite(_SCL,HIGH);
  digitalWrite(_SDA,HIGH);
  digitalWrite(_cEN,LOW);
  delay(1000);
  digitalWrite(_cEN,HIGH);
  while(lightStrengthLux()<=0);
  
}
uint8_t DFRobot_B_LUX_V30B::readMode(void)
{
  uint8_t mode;
  iicStartBit();
  if(iicSend(_deviceAddr+0)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
    }
  if(iicSend(DFRobot_B_LUX_V30_ConfigReg)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
    }
  iicStartBit();
  if(iicSend(_deviceAddr+1)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
    }
  delay(10);
  mode=iicReadByte();
  iicSendAck(1);
  iicStopBit();
  while(lightStrengthLux()<=0);
  return mode;
}
uint8_t DFRobot_B_LUX_V30B::setMode(uint8_t isManualMode,uint8_t isCDR,uint8_t isTime)
{
  uint8_t mode =isManualMode+isCDR+isTime;
  iicStartBit();
  
  if(iicSend(_deviceAddr+0)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
    }
  if(iicSend(DFRobot_B_LUX_V30_ConfigReg)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
  }
  if(iicSend(mode)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
  }
  digitalWrite(_SDA,LOW);
  iicStopBit();
  delay(10);
  return 1;
}
void DFRobot_B_LUX_V30B::iicStartBit()
{
  digitalWrite(_SCL,HIGH);
  digitalWrite(_SDA,HIGH);
  delayMicroseconds(5);
  digitalWrite(_SDA,LOW);
  delayMicroseconds(5);
  digitalWrite(_SCL,LOW);
  delayMicroseconds(5);
}

void DFRobot_B_LUX_V30B::iicStopBit()
{
  digitalWrite(_SCL,HIGH);
  digitalWrite(_SDA,LOW);
  delayMicroseconds(5);
  digitalWrite(_SDA,HIGH);
  delayMicroseconds(5);
  digitalWrite(_SCL,LOW);
  delayMicroseconds(5);
}

void DFRobot_B_LUX_V30B::iicSendAck(uint8_t ack)
{
  pinMode(_SDA,OUTPUT);
  if(ack & 0x01 ){/*ack=0,send ACK，ack=1,send NACK*/
    digitalWrite(_SDA,HIGH);
  }else{
    digitalWrite(_SDA,LOW);
  }
  digitalWrite(_SCL,HIGH);
  delayMicroseconds(5);
  digitalWrite(_SCL,LOW);
  delayMicroseconds(5);
}
uint8_t DFRobot_B_LUX_V30B::iicRecvAck()
{
  uint8_t cy=0;
  pinMode(_SDA,INPUT);
  digitalWrite(_SCL,HIGH);
  delayMicroseconds(5);
  cy=digitalRead(_SDA);
  digitalWrite(_SCL,LOW);
  digitalWrite(_SDA,HIGH);
  pinMode(_SDA,OUTPUT);
  delayMicroseconds(5);
  return cy;
}

uint8_t DFRobot_B_LUX_V30B::iicSend(uint8_t data)
{
  for(uint8_t i=0; i<8;i++){  
    if(data & (0x80)){
      digitalWrite(_SDA,HIGH);
    }else{
      digitalWrite(_SDA,LOW);
    }
    delayMicroseconds(5); 
    digitalWrite(_SCL,HIGH);
    delayMicroseconds(5); 
    digitalWrite(_SCL,LOW);
    delayMicroseconds(5); 
    data = data<<1;
  }
  return iicRecvAck();
}

uint8_t DFRobot_B_LUX_V30B::iicReadByte()
{
  uint8_t data=0;
  pinMode(_SDA,INPUT_PULLUP);
  for(uint8_t i=0; i<8; i++){
    digitalWrite(_SCL,HIGH);   
    delayMicroseconds(5);
    data |= digitalRead(_SDA);
    digitalWrite(_SCL,LOW);
    delayMicroseconds(5);
    if(i<7) 
      data<<=1;
  }
  pinMode(_SDA,OUTPUT);
  return data;
}
uint8_t DFRobot_B_LUX_V30B::iicRead(uint8_t num, uint8_t* data)
{
  iicStartBit();
  if(iicSend(_deviceAddr+0)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
  }
  if(iicSend(0x00)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
  }
  //
  iicStartBit();
  if(iicSend(_deviceAddr+1)){
    digitalWrite(_SDA,LOW);
    iicStopBit();
    return 0;
    }
  delay(10);
  for(uint8_t i=0; i<num; i++){
    data[i]=iicReadByte();
    if(i==num-1){
      iicSendAck(NACK);//send NACK
    }else{
      iicSendAck(ACK);//send ACK
    }
  }
  digitalWrite(_SDA,LOW);
  iicStopBit();
  return 1;
}
float DFRobot_B_LUX_V30B::lightStrengthLux()
{
  uint32_t value = 0;
  uint8_t data[6];
  if(iicRead(4,data)){
  value = data[3];
  value = (value<<8)|data[2];
  value = (value<<8)|data[1];
  value = (value<<8)|data[0];
  return ((float)value*1.4) / 1000;
  }
  return -1;
}
















