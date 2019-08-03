/*******************************************************************************  
* �ļ����ƣ����������ʵ��
* ʵ��Ŀ�ģ�1.���ճ��������ԭ��
*           2.����15��Ƭ����ʱ������ģʽ�����÷���
* ����˵���������ʱ��������Ҫ���ݵ�Ƭ����ʱ��Ƶ�ʽ��е���,����������11.0592MHz
* Ӳ��˵����IAP15F2K61S2@11.0592MHz
* ���ڰ汾��2017-1-30
*******************************************************************************/

#include<STC15F2K60S2.H>
#include "intrins.h"

#define uchar unsigned char 
#define uint unsigned int	

#define somenop {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); _nop_();}
sbit TX = P1^0;  //��������
sbit RX = P1^1;  //��������

uchar code tab[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};
uchar yi,er,san,si,wu ,liu,qi,ba;

unsigned int intr = 0;
bit s_flag;
unsigned int t = 0;

void send_wave(void);
void Timer0Init(void)	;
void Timer1Init(void);

void delayms(int ms);
void allinit();
void display1(uchar yi,uchar er);
void display2(uchar san,uchar si);
void display3(uchar wu,uchar liu);
void display4(uchar qi,uchar ba);

void main()
{
	unsigned int distance;
	
	Timer0Init();
  	Timer1Init();

	EA = 1;
	ET0 = 1;  //�򿪶�ʱ��0�ж�
	
	allinit();
	yi=11;er=11;san=11;si=11;wu=11;liu=0;qi=0;ba=0;
	
	while(1)
	{
		if(s_flag) // 200�������һ������ 
		{
			s_flag = 0;
			send_wave();  //���ͷ����ź�
			TR1 = 1;  //������ʱ
			while((RX == 1) && (TF1 == 0));  //�ȴ��յ�����
			TR1 = 0;  //�رռ�ʱ		
			
			if(TF1 == 1)//�������
			{
				TF1 = 0;
				distance = 9999;  //�޷���
			}
			else
			{		
				t = TH1;// ����ʱ��  
				t <<= 8;
				t |= TL1;
				distance = (unsigned int)(t*0.017);  //�������	
				distance = distance/12;
				//t*340   // t/1000000*340/2*100
			}
			TH1 = 0;
			TL1 = 0;
		}
		
		//���ݴ���  						 
		liu = distance/100;
		qi = distance%100/10;
		ba = distance%10; 
		
		display1(yi,er);
		display2(san,si);
		display3(wu,liu);
		display4(qi,ba);
	}
}

void Timer0Init(void)		//2����@11.0592MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x9A;		//���ö�ʱ��ֵ
	TH0 = 0xA9;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void Timer1Init(void)		//2����@11.0592MHz
{
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
}

//��ʱ��0�жϷ�����
void isr_timer_0(void)  interrupt 1  //Ĭ���ж����ȼ� 1
{
	TL0 = 0x9A;		//���ö�ʱ��ֵ
	TH0 = 0xA9;		//���ö�ʱ��ֵ

	if(++intr == 100)
	{
		s_flag = 1;
		intr = 0;
  }
}

//TX���ŷ���40KHz�����ź���������������̽ͷ
//ʹ�������ʱע��RC����Ƶ��
void send_wave(void)
{
	unsigned char i = 8;  //����8������
	
	do
	{
		TX = 1;
		somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;		
		TX = 0;
		somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;somenop;		
	}
	while(i--);
}


void delayms(int ms)
{
	int i,j;
	for(i=ms;i>0;i--)
		for(j=845;j>0;j--);
}

void allinit()
{
	P2=0XA0;
	P0=0X00;//�رշ��������̵���
	
	P2=0X80;
	P0=0XFF;//�ر�LED��
	
	P2=0XC0;
	P0=0XFF;//ѡ�����������
	P2=0XFF;
	P0=0XFF;//�ر����������
}

void display1(uchar yi,uchar er)
{
		P2=0XC0;//��λѡ573   U8
		P0=0X01;//ѡ���һ�������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[yi];
		delayms(1);
		
		P2=0XC0;//��λѡ573   U8
		P0=0X02;//ѡ��ڶ��������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[er];
		delayms(1);
}	

void display2(uchar san,uchar si)
{
		P2=0XC0;//��λѡ573   U8
		P0=0X04;//ѡ������������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[san];
		delayms(1);
		
		P2=0XC0;//��λѡ573   U8
		P0=0X08;//ѡ����ĸ������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[si];
		delayms(1);
}

void display3(uchar wu,uchar liu)
{
		P2=0XC0;//��λѡ573   U8
		P0=0X10;//ѡ���һ�������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[wu];
		delayms(1);
		
		P2=0XC0;//��λѡ573   U8
		P0=0X20;//ѡ���һ�������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[liu];
		delayms(1);
}

void display4(uchar qi,uchar ba)
{
		P2=0XC0;//��λѡ573   U8
		P0=0X40;//ѡ���һ�������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[qi];
		delayms(1);
		
		P2=0XC0;//��λѡ573   U8
		P0=0X80;//ѡ���һ�������
		P2=0XFF;//�򿪶�ѡ573   U7
		P0=tab[ba];
		delayms(1);
}























