/*******************************************************************************  
* �ļ����ƣ����ű���Ƭ�����Ľ����--ģ�����ܹ��
* ʵ��Ŀ�ģ�ģ�����ܹ��     
* ����˵���������˽��йر�����������Ƶ���⣬�������������\
*					 ��ӭ�����Ա�������ַ��shop117015787.taobao.com
* ���ڰ汾��2017-12/V1.0
*******************************************************************************/

#include<STC15F2K60S2.H>
#include "intrins.h"
#include "iic.h"
#include "ds1302.h"
	
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff}; 
uchar yi,er,san,si,wu,liu,qi,ba;
uchar shidu;
uchar fazhi;
extern unsigned char shijian[];
bit s6=0,jia=0,jian=0,status=0,kai=1,relay=0;

void allinit(void);
void delayms(uint ms);
void keyscan(void);
void display1(uchar yi,uchar er);
void display2(uchar san,uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi,uchar ba);

void main(void)
{
	allinit();
	DS_init();
	P2=0X80;P0=0XFE;
	yi=0;er=8;san=10;si=3;wu=0;liu=11;qi=0;ba=0;
//	EEPROM_write(0x10,50);
//	delayms(5);
	fazhi=EEPROM_read(0x10);
	while(1)
	{
		DS_get();
		shidu=AD_read(0x03);
		if(status==0)
		{
			if(shidu<fazhi)
			{
				P2=0XA0;P0=0X10;
			}
			else 
			{
				P2=0XA0;P0=0X00;
			}
			
			if(s6==1)
			{
				if(jia==1)
				{
					jia=0;
					fazhi=fazhi+1;
				}
				if(jian==1)
				{
					jian=0;
					fazhi=fazhi-1;
				}
				yi=10;er=10;san=11;si=11;wu=11;liu=11;qi=fazhi/10;ba=fazhi%10;
			}
			else if(s6==0)
			{
				yi=shijian[2]/10;er=shijian[2]%10;san=10;
				si=shijian[1]/10;wu=shijian[1]%10;liu=11;
				qi=shidu/10;ba=shidu%10;				
			}
		}
		else if(status==1)
		{
			if((shidu<fazhi)&&(kai==0))
			{
				if(relay==1){P2=0XA0;P0=0X10;}
				else if(relay==0){P2=0XA0;P0=0X00;}
			}
			if((shidu<fazhi)&&(kai==1))
			{
				if(relay==1){P2=0XA0;P0=0X50;}
				else if(relay==0){P2=0XA0;P0=0X40;}
			}
			else if(shidu>fazhi)
			{
				if(relay==1){P2=0XA0;P0=0X10;}
				else if(relay==0){P2=0XA0;P0=0X00;}
			}
			yi=shijian[2]/10;er=shijian[2]%10;san=10;
			si=shijian[1]/10;wu=shijian[1]%10;liu=11;
			qi=shidu/10;ba=shidu%10;		
		}

//		shidu=AD_read(0x03);
//		liu=shidu/100;qi=shidu%100/10;ba=shidu%10;
		
//		EEPROM_write(0x10,125);
//		delayms(5);
//		shidu=EEPROM_read(0x10);
//		liu=shidu/100;qi=shidu%100/10;ba=shidu%10;
		
//		DS_get();
//		yi=shijian[2]/10;er=shijian[2]%10;san=10;
//		si=shijian[1]/10;wu=shijian[1]%10;liu=10;
//		qi=shijian[0]/10;ba=shijian[0]%10;
		
		keyscan();
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}

void keyscan(void)
{
	if(P30==0)
	{
		delayms(5);
		if(P30==0)
		{
			if(status==0)
			{
				status=1;
				P2=0X80;P0=0XFD;
			}
			else if(status==1)
			{
				status=0;
				P2=0X80;P0=0XFE;
			}
		}
		while(!P30);
	}
	else if(P31==0)
	{
		delayms(5);
		if(P31==0)
		{
			if(status==0)
			{
				if(s6==0){s6=1;}
				else if(s6==1){s6=0;EEPROM_write(0x10,fazhi);}
			}
			else if(status==1)
			{
				kai=~kai;
			}
		}
		while(!P31);
	}
	else if(P32==0)
	{
		delayms(5);
		if(P32==0)
		{
			if(status==0)jia=1;
			else if(status==1)relay=1;
		}
		while(!P32);
	}
	else if(P33==0)
	{
		delayms(5);
		if(P33==0)
		{
			if(status==0)jian=1;
			else if(status==1)relay=0;	
		}
		while(!P33);
	}
}

void allinit(void)
{
	P2=0XA0;
	P0=0x00;//�رշ������̵���
	
	P2=0X80;
	P0=0XFF;//�ر�LED��
	
	P2=0XC0;
	P0=0XFF;//ѡ�����������
	P2=0XFF;
	P0=0XFF;//�رն��������	
}

void display1(uchar yi,uchar er)
{
	P2=0XC0;
	P0=0X01;//ѡ�����������
	P2=0XFF;
	P0=tab[yi];//�رն��������	
	delayms(1);
	
	P2=0XC0;
	P0=0X02;//ѡ�����������
	P2=0XFF;
	P0=tab[er];//�رն��������	
	delayms(1);
}

void display2(uchar san,uchar si)
{
	P2=0XC0;
	P0=0X04;//ѡ�����������
	P2=0XFF;
	P0=tab[san];//�رն��������	
	delayms(1);
	
	P2=0XC0;
	P0=0X08;//ѡ�����������
	P2=0XFF;
	P0=tab[si];//�رն��������	
	delayms(1);
}

void display3(uchar wu,uchar liu)
{
	P2=0XC0;
	P0=0X10;//ѡ�����������
	P2=0XFF;
	P0=tab[wu];//�رն��������	
	delayms(1);
	
	P2=0XC0;
	P0=0X20;//ѡ�����������
	P2=0XFF;
	P0=tab[liu];//�رն��������	
	delayms(1);
}

void display4(uchar qi,uchar ba)
{
	P2=0XC0;
	P0=0X40;//ѡ�����������
	P2=0XFF;
	P0=tab[qi];//�رն��������	
	delayms(1);
	
	P2=0XC0;
	P0=0X80;//ѡ�����������
	P2=0XFF;
	P0=tab[ba];//�رն��������	
	delayms(1);
}

void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}