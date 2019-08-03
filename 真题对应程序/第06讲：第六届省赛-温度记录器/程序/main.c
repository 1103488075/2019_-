/*******************************************************************************  
* �ļ����ƣ����ű���Ƭ��������ʡ��-�¶ȼ�¼��
* ʵ��Ŀ�ģ��¶ȼ�¼�� 
* ����˵���������˽��йر�����������Ƶ���⣬�������������\
*					 ��ӭ�����Ա�������ַ��shop117015787.taobao.com
* ���ڰ汾��2017-12/V1.0
*******************************************************************************/

#include<STC15F2K60S2.H>
#include "DEPUTY.H"

#define uchar unsigned char
#define uint unsigned int
	
uchar code tab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff}; 
uchar yi,er,san,si,wu,liu,qi,ba;
extern unsigned char shijian[]; 
uchar Timec=1;
uchar wendu;
uchar Cai_start=0;
uint tt=0;
uchar Save[10],Save_n=0;
bit fla=0,LED_shan=0;

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
	DS_init();
	Timer0Init();
	yi=11;er=11;san=11;si=11;wu=11;liu=10;qi=0;ba=1;
	while(1)
	{
		wendu=Tempget();
		if(Cai_start==0)
		{
			yi=11;er=11;san=11;si=11;wu=11;liu=10;
			qi=Timec/10;ba=Timec%10;
		}
		else if(Cai_start==1)
		{
			DS_get();
			yi=shijian[2]/10;er=shijian[2]%10;
			si=shijian[1]/10;wu=shijian[1]%10;
			qi=shijian[0]/10;ba=shijian[0]%10;
			
			if(shijian[0]%2==0){san=10;liu=10;}
			else {san=11;liu=11;}			
		}	
		keyscan();
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
	if((tt==Timec*200)&&(Cai_start==1))
	{
		tt=0;
		Save[Save_n]=wendu;
		Save_n++;
		if(Save_n==10)
		{
			Cai_start=2;LED_shan=1;Save_n=0;
			yi=10;er=0;san=0;si=11;wu=11;liu=10;qi=Save[0]/10;ba=Save[0]%10;
		}
	}
	
	if((Cai_start==2)&&(tt==200))
	{
		tt=0;
		if(LED_shan==1)
		{
			if(fla==0){fla=1;P2=0X80;P0=0XFE;}
			else if(fla==1){fla=0;P2=0X80;P0=0XFF;}
		}
		else if(LED_shan==0)
		{
			yi=10;si=11;wu=11;liu=10;
			er=Save_n/10;san=Save_n%10;
			qi=Save[Save_n]/10;ba=Save[Save_n]%10;
			Save_n++;
			if(Save_n==10)
			{
				Save_n=0;
				Cai_start=3;
			}
		}
	}
}

void keyscan(void)
{
	if(P30==0)
	{
		delayms(5);
		if(P30==0)
		{
			if(Cai_start==3)Cai_start=0;			
		}
		while(!P30);
	}
	else if(P31==0)
	{
		delayms(5);
		if(P31==0)
		{
			if(Cai_start==2){LED_shan=0;P2=0X80;P0=0XFF;}
		}
		while(!P31);
	}
	else if(P32==0)
	{
		delayms(5);
		if(P32==0)
		{
			if(Cai_start==0){Cai_start=1;tt=0;}
		}
		while(!P32);
	}
	else if(P33==0)
	{
		delayms(5);
		if(P33==0)
		{
			if(Cai_start==0)
			{
				if(Timec==1)Timec=5;
				else if(Timec==5)Timec=30;
				else if(Timec==30)Timec=60;
				else if(Timec==60)Timec=1;
			}
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