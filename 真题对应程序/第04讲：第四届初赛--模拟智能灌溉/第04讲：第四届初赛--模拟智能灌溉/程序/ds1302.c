/*******************************************************************************  
* �ļ����ƣ����ű���Ƭ�����Ľ����--ģ�����ܹ��
* ʵ��Ŀ�ģ�ģ�����ܹ��     
* ����˵���������˽��йر�����������Ƶ���⣬�������������\
*					 ��ӭ�����Ա�������ַ��shop117015787.taobao.com
* ���ڰ汾��2017-12/V1.0
*******************************************************************************/

#include<STC15F2K60S2.H>
#include <intrins.h>
#include <ds1302.h>

sbit SCK=P1^7;		
sbit SDA=P2^3;		
sbit RST = P1^3;   // DS1302��λ	

unsigned char shijian[]={0,30,8,0,0,0,0};

void Write_Ds1302_Byte(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK=0;
		SDA=temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

void Write_Ds1302( unsigned char address,unsigned char dat )     
{
 	RST=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	SCK=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	RST=1;	
   	_nop_(); _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); 
 	Write_Ds1302_Byte(address);	
 	Write_Ds1302_Byte((dat/10<<4)|(dat%10));	/////////////////////////////////////////////////	
 	RST=0; 
}

unsigned char Read_Ds1302 ( unsigned char address )
{
 	unsigned char i,temp=0x00,dat1,dat2;/////////////////////////////////////
 	RST=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	SCK=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	RST=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
 	RST=0;
	SCK=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	SCK=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	SDA=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	SDA=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	
	dat1=temp/16;
	dat2=temp%16;
	temp=dat1*10+dat2;/////////////////////////////////////////////////////////////////
	
	return (temp);			
}

void DS_init(void)
{
	unsigned char i,add;
	add=0x80;
	Write_Ds1302(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		Write_Ds1302(add,shijian[i]);
		add=add+2;
	}
	Write_Ds1302(0x8e,0x80);
}


void DS_get(void)
{
	unsigned char i,add;
	add=0x81;
	Write_Ds1302(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		shijian[i]=Read_Ds1302(add);
		add=add+2;
	}
	Write_Ds1302(0x8e,0x80);
}




