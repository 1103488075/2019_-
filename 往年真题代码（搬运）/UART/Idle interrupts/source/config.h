/*
*******************************************************************************
* 文件名：config.h
* 描  述：一些公用文件
* 作  者：CLAY
* 版本号：v1.0.0
* 日  期: 
* 备  注：
*         
*******************************************************************************
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stc15.h>

typedef unsigned char u8;
typedef unsigned int  u16;
typedef unsigned long u32;

#define LCD1602_DB P0
sbit LCD1602_RS = P2^0;
sbit LCD1602_RW = P2^1;
sbit LCD1602_E  = P1^2;

sbit KEY_OUT_1 = P3^0;
sbit KEY_OUT_2 = P3^1;
sbit KEY_OUT_3 = P3^2;
sbit KEY_OUT_4 = P3^3;
sbit KEY_IN_1  = P4^4;
sbit KEY_IN_2  = P4^2;
sbit KEY_IN_3  = P3^5;
sbit KEY_IN_4  = P3^4;

sbit I2C_SCL = P2^0;
sbit I2C_SDA = P2^1;


#endif