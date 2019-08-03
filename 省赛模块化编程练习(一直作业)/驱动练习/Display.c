#include "Display.h"
uchar yi = 11,er = 11,san = 11,si = 11,wu = 11,liu = 11,qi = 11,ba = 11;
uchar duanxuan[]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90,0XBF,0XFF};	
void Display1(uchar yi,uchar er)
{
	P2 = 0xc0; P0 = 0x01;
	P2 = 0xff; P0 = duanxuan[yi];
	Delay2ms();
	P2 = 0xc0; P0 = 0x02;
	P2 = 0xff; P0 = duanxuan[er];
	Delay2ms();
}
void Display2(uchar san,uchar si)
{	
	P2 = 0xc0; P0 = 0x04;
	P2 = 0xff; P0 = duanxuan[san];
	Delay2ms();
	P2 = 0xc0; P0 = 0x08;
	P2 = 0xff; P0 = duanxuan[si];
	Delay2ms();
}
void Display3(uchar wu,uchar liu)
{
	P2 = 0xc0; P0 = 0x10;
	P2 = 0xff; P0 = duanxuan[wu];
	Delay2ms();
	P2 = 0xc0; P0 = 0x20;
	P2 = 0xff; P0 = duanxuan[liu];
	Delay2ms();
}
void Display4(uchar qi,uchar ba)
{
	P2 = 0xc0; P0 = 0x40;
	P2 = 0xff; P0 = duanxuan[qi];
	Delay2ms();
	P2 = 0xc0; P0 = 0x80;
	P2 = 0xff; P0 = duanxuan[ba];
	Delay2ms();
}
void Delay2ms()
{
	uchar i = 22,j = 128;
	_nop_();_nop_();
	do
	{
	  while(--j);

	}while(--i);
}




