#ifndef _IIC_H
#define _IIC_H

#include "Head.h"

void IIC_Start(void); 
void IIC_Stop(void);  
bit IIC_WaitAck(void);  
void IIC_SendAck(bit ackbit); 
void IIC_SendByte(unsigned char byt); 
unsigned char IIC_RecByte(void); 
uchar Read_AD(uchar addr);
void EEPROM_Write(uchar addr,uchar dat);
uchar EEPROM_Read(uchar addr);

#endif