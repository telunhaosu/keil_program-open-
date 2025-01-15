#include <REGX51.H>
sbit p10 = P1^0;
sbit p13 = P1^3;
sbit p20 = P2^0;
typedef unsigned int u16;    //typedef������������
 void delay(u16 x)
 {
	 u16 i;
	 while(x--)
	 {
		 for(i = 0; i < 123; i++);
	 }
 }
void main()                //������
{
	u16 j;
	unsigned char flow1[4] = {0xe7, 0xdb, 0xbd, 0x7e};	//��->��
	unsigned char flow2[4] = {0xdb, 0xe7, 0x7e, 0xbd };	//��->��
	while(1)
	{
		if (p10 == 1 && p13 == 1)
		{
		for(j=0;j<8;j++)
		{
			P2=~(0x01<<j);	//��->��
			delay(150);
		}
		}
		else if(p10 == 0 && p13 == 1)
		{
		for(j=0;j<8;j++)
		{

			P2=~(0X80>>j);	//��->��
			delay(150);
		}
		}
		else if(p10 == 1 && p13 == 0)
		{
		for(j=0;j<4;j++)
		{
			P2=flow1[j]; //��->��
			delay(150);
		}
		}
		else if(p10 == 0 && p13 == 0)
		{
		for(j=0;j < 4;j++)
		{
			P2=flow2[j];//��->��
			delay(150);
		}
		}
	}
}

