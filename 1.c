#include<reg52.h>
unsigned char receiveData, flag,i;
unsigned char a,b;
//unsigned char table[];
unsigned char code Seg_Pos[8]={0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
unsigned char code Seg_Code[11]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};
unsigned char Seg_Buf[8]={10,10,10,10,10,10,10,10}; 

void Seg_Display()
{
static unsigned char Seg_Com=0;
P0=0XFF;
P2=Seg_Pos[Seg_Com];
P0=Seg_Code[Seg_Buf[Seg_Com]];
if(++Seg_Com==8)
{
Seg_Com=0;
}
}
void UartInit()
{
SCON=0X50;
TMOD=0X20;
PCON=0X80;
TH1=0XF3;
TL1=0XF3;
TR1=1;
EA=1;
ES=1;
}

void Timer0Init(void)  
{
 TMOD |= 0x01; 
 TL0 = 0x9C;  
 TH0 = 0xFF;  
 TF0 = 0; 
 TR0 = 1; 
 ET0=1;
}

void main()
{
flag=0;
UartInit();
Timer0Init();
while(1)
{
if(flag==1)
{
ES=0;
if(receiveData>47&&receiveData<58)
{
a=receiveData;
b=a-48;
Seg_Buf[7]=b;
}
ES=1;
flag=0;
}
}
}
void Usart() interrupt 4
{
receiveData =SBUF;
RI=0;
flag=1;
}

void timer0() interrupt 1
{
 Seg_Display();
 TL0 = 0x9C;  
 TH0 = 0xFF; 
 }
