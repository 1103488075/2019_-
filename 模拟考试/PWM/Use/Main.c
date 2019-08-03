 #include "Head.h"
#include "Display.h"
#include "Key.h" 
#include "iic.h"

void InitAll();
 void Timer1Init(void);
  
float AD = 0;
uint Pulse = 10;

uchar PWMSta = 0x00;
bit flag = 0;
void main()
{

	 InitAll();
	 Timer1Init();
 	  ET1 = 1;EA = 1;
 
	 while(1)
	 {
 		 // P2 = 0xc0; P0 = 0xff;
 		  yi = 1,er = 2,san = 3,si = 4,wu = 5,liu = 6,qi = 7,ba = 8;

 		 	P2 = 0x80; P0 = 0xff;
		 Key16();
	   Display1(yi,er);
	   Display2(san,si);
	   Display3(wu,liu);
	   Display4(qi,ba);
	   }
}

void Time1() interrupt 3
{
	static uint PWM;  

	TL1 = 0xF7;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ

	PWM++;

	PWM %= 101;	//�����ж�ֵ����
 	P2 = (P2 & 0x1F) | 0x80;
	if(PWM >= Pulse)
    {
	 
	  	//P2 = 0x80;
		 P0 = 0xff;
	} 
	else 
 	{
	 
 		//P2 = 0x80;
		 P0 = PWMSta;
 
 	}
	 P2 &= 0x1F;
}


void Timer1Init(void)		//10΢��@11.0592MHz
{
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xF7;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;
}

void InitAll()
{
	P2 = 0xa0; P0 = 0x00;
	P2 = 0x80; P0 = 0xff;
	P2 = 0xc0; P0 = 0xff;
	P2 = 0xff; P0 = 0xff;
				 	
}