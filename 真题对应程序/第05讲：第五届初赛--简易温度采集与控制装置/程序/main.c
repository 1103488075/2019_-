/*******************************************************************************  
* �ļ����ƣ����ű���Ƭ�������ʡ��-�����¶Ȳɼ������װ��
* ʵ��Ŀ�ģ������¶Ȳɼ������װ��    
* ����˵���������˽��йر�����������Ƶ���⣬�������������\
*					 ��ӭ�����Ա�������ַ��shop117015787.taobao.com
* ���ڰ汾��2017-12/V1.0
*******************************************************************************/
#include<STC15F2K60S2.H>
#include "onewire.h"

#define uchar unsigned char
#define uint unsigned int
	
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff}; 
uchar yi,er,san,si,wu,liu,qi,ba;
uchar wendu;
uchar max=30,min=20,qujian=0;
uchar tt=0;
uchar num=0;
bit fla=0;
bit shezhi=0,qingchu=0,flag=0;

void allinit(void);
void delayms(uint ms);
void keyscan16(void);
void display1(uchar yi,uchar er);
void display2(uchar san,uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi,uchar ba);
void Timer0Init(void);

void main(void)
{
	allinit();
	Timer0Init();
	yi=10;er=1;san=10;si=11;wu=11;liu=11;qi=0;ba=0;
	while(1)
	{
		if(shezhi==0)
		{
			wendu=Tempget();
			if(wendu<min)
			{
				qujian=0;P2=0XA0;P0=0X00;
			}
			else if((wendu>=min)&&(wendu<=max))
			{
				qujian=1;P2=0XA0;P0=0X00;
			}
			else if(wendu>max)
			{
				qujian=2;P2=0XA0;P0=0X10;
			}
			yi=10;er=qujian;san=10;si=11;wu=11;liu=11;qi=wendu/10;ba=wendu%10;				
		}
		else if(shezhi==1)
		{
			if(qingchu==1)
			{
				qingchu=0;
				yi=10;er=11;san=11;si=11;wu=11;liu=10;qi=11;ba=11;	
			}
			
			if((er==11)&&(flag==1))
			{
				flag=0;er=num;	
			}
			else if((san==11)&&(flag==1))
			{
				flag=0;san=num;
			}
			else if((qi==11)&&(flag==1))
			{
				flag=0;qi=num;
			}
			else if((ba==11)&&(flag==1))
			{
				flag=0;ba=num;
				if((qi*10+ba)>(er*10+san))
				{
					yi=10;er=11;san=11;si=11;wu=11;liu=10;qi=11;ba=11;
					P2=0X80;P0=0XFD;
				}			
			}
		}
		
		keyscan16();
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}

void Timer0Init(void)		//5����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x00;		//���ö�ʱ��ֵ
	TH0 = 0x28;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
	ET0=1;
	EA=1;
}

void timer0() interrupt 1
{
	tt++;
	if((qujian==0)&&(tt==160))
	{
		tt=0;
		if(fla==0){fla=1;P2=0X80;P0=0XFE;}
		else if(fla==1){fla=0;P2=0X80;P0=0XFF;}
	}
	else 	if((qujian==1)&&(tt==80))
	{
		tt=0;
		if(fla==0){fla=1;P2=0X80;P0=0XFE;}
		else if(fla==1){fla=0;P2=0X80;P0=0XFF;}
	}
	else 	if((qujian==2)&&(tt==40))
	{
		tt=0;
		if(fla==0){fla=1;P2=0X80;P0=0XFE;}
		else if(fla==1){fla=0;P2=0X80;P0=0XFF;}
	}
}

void keyscan16(void)
{
	uchar temp;
	P3=0X7F;P44=0;P42=1;
	temp=P3;
	temp=temp&0x0f;
	if(temp!=0x0f)
	{
		delayms(5);
		temp=P3;
		temp=temp&0x0f;
		if(temp!=0x0f)
		{
			temp=P3;
			switch(temp)
			{
				case 0x7e:num=0; flag=1; break;
				case 0x7d:num=3; flag=1; break;
				case 0x7b:num=6; flag=1; break;
				case 0x77:num=9; flag=1; break;
			}
			while(temp!=0x0f)
			{
				temp=P3;
				temp=temp&0x0f;
			}
		}
	}
	
	P3=0XbF;P44=1;P42=0;
	temp=P3;
	temp=temp&0x0f;
	if(temp!=0x0f)
	{
		delayms(5);
		temp=P3;
		temp=temp&0x0f;
		if(temp!=0x0f)
		{
			temp=P3;
			switch(temp)
			{
				case 0xbe:num=1;flag=1;  break;
				case 0xbd:num=4;flag=1; break;
				case 0xbb:num=7;flag=1; break;
				case 0xb7:
					if(shezhi==0)
					{
						shezhi=1;
						ET0=0;EA=0;
						P2=0X80;P0=0XFF;P2=0XA0;P0=0X00;
						yi=10;er=11;san=11;si=11;wu=11;liu=10;qi=11;ba=11;	
					}
					else if(shezhi==1)
					{
						shezhi=0;
						ET0=1;EA=1;
						P2=0X80;P0=0XFF;
						max=er*10+san;
						min=qi*10+ba;
					}
					break;
			}
			while(temp!=0x0f)
			{
				temp=P3;
				temp=temp&0x0f;
			}
		}
	}
	
	P3=0XDF;P44=1;P42=1;
	temp=P3;
	temp=temp&0x0f;
	if(temp!=0x0f)
	{
		delayms(5);
		temp=P3;
		temp=temp&0x0f;
		if(temp!=0x0f)
		{
			temp=P3;
			switch(temp)
			{
				case 0xde:num=2;flag=1;  break;
				case 0xdd:num=5;flag=1;  break;
				case 0xdb:num=8;flag=1;  break;
				case 0xd7:qingchu=1; break;
			}
			while(temp!=0x0f)
			{
				temp=P3;
				temp=temp&0x0f;
			}
		}
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