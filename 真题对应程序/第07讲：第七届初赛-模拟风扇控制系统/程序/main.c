/*******************************************************************************  
* �ļ����ƣ����ű���Ƭ�����߽����-ģ����ȿ���ϵͳ
* ʵ��Ŀ�ģ�ģ����ȿ���ϵͳ
* ����˵���������˽��йر�����������Ƶ���⣬�������������\
*					 ��ӭ�����Ա�������ַ��shop117015787.taobao.com
* ���ڰ汾��2017-12/V1.0
*******************************************************************************/


#include<STC15F2K60S2.H>
#include "onewire.h"

#define uchar unsigned char
#define uint unsigned int
	
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff,0xc6}; 
uchar yi,er,san,si,wu,liu,qi,ba;
uchar mode=1;
uchar Time=0;
uchar tt=0;
uint miao=0;
bit shiwen=0;
bit fla=0;

void allinit(void);
void delayms(uint ms);
void keyscan(void);
void display1(uchar yi,uchar er);
void display2(uchar san,uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi,uchar ba);
void Timer0Init(void);

void main(void)
{
	allinit();
	Timer0Init();
	yi=10;er=1;san=10;si=11;wu=0;liu=0;qi=5;ba=0;
	while(1)
	{
		if(shiwen==0)
		{
			yi=10;er=mode;san=10;si=11;
			wu=Time/1000;liu=Time%1000/100;qi=Time%100/10;ba=Time%10;
		}
		else if(shiwen==1)
		{
			yi=10;er=4;san=10;si=11;wu=11;
			liu=Tempget()/10;qi=Tempget()%10;ba=12;
		}
		
		if(Time>0)
		{
			if(mode==1){P2=0X80;P0=0XFE;}
			else if(mode==2){P2=0X80;P0=0XFD;}
			else if(mode==3){P2=0X80;P0=0XFB;}
		}
		else {P2=0X80;P0=0XFF;fla=0;}
		
		keyscan();
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}

void Timer0Init(void)		//100΢��@11.0592MHz   // 10
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xAE;		//���ö�ʱ��ֵ
	TH0 = 0xFB;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
	ET0=1;
	EA=1;
}


void timer0() interrupt 1
{
	tt++;miao++;
	
	if(tt==11)tt=1;
	
	if(Time>0)
	{
		if(mode==1)
		{
			if(tt<3)P34=1;
			else P34=0;
		}
		else if(mode==2)
		{
			if(tt<4)P34=1;
			else P34=0;
		}
		else if(mode==3)
		{
			if(tt<8)P34=1;
			else P34=0;
		}
	}
	
	if(miao==10000)
	{
		miao=0;
		if(Time>0)Time--;
	}
}



void keyscan(void)
{
	if(P30==0)
	{
		delayms(5);
		if(P30==0)
		{
			shiwen=~shiwen;
		}
		while(!P30);
	}
	else if(P31==0)
	{
		delayms(5);
		if(P31==0)
		{
			Time=0;fla=0;
		}
		while(!P31);
	}
	else if(P32==0)
	{
		delayms(5);
		if(P32==0)
		{
			if(Time==0)Time=60;
			else if((Time>0)&&(fla==0)){Time=120;fla=1;}
			else if(fla==1){Time=0;fla=0;}
		}
		while(!P32);
	}
	else if(P33==0)
	{
		delayms(5);
		if(P33==0)
		{
			if(mode==1)mode=2;
			else if(mode==2)mode=3;
			else if(mode==3)mode=1;
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
	
	P2=0XC0;
	P0=0XFF;//ѡ�����������
	P2=0XFF;
	P0=0XFF;//�رն��������	
}

void delayms(uint ms)
{
	uint i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}