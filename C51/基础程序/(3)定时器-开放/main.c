#include <REGX51.H>
typedef unsigned char u8;
unsigned char led[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
u8 i = 0;

void Delay(unsigned int i);
u8 MatrixKey(void);
void Display(u8 num);

void main()
{
	u8 ret = 0;
	u8 m,n, tmp = 99;
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xD0;		//���ö�ʱ��ֵ
	TH0 = 0x6F;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	EA = 1; 	//���жϴ�
	ET0 = 1;	//����T0�ж�
	TR0 = 0;
	while(1)
	{
		ret = MatrixKey();
		if (ret)
		{
			
			tmp = ret;
			P3_2 = 0;
			TR0 = 1;
			m = tmp /10;	//ȡʮλ
			n = tmp % 10;	//ȡ��λ
		}
		if(tmp)
		{
			if (tmp == 99)		//Ĭ����ʾ
			{
				P0 = 0xfd; 		//ʮλ
				P2 = 0xbf;
				Delay(15);
				
				P0 = 0xfe;	//��λ
				P2 = 0xbf;	
				Delay(15);
			}
		else
		{
			P0 = 0xfd; 		//ʮλ
			P2 = ~led[m];
			Delay(15);
			
			P0 = 0xfe;	//��λ
			P2 = ~led[n];	
			Delay(15);
		}
		}
	}
}


unsigned char MatrixKey()
{
	unsigned char KeyNumber=0;
	
	P1=0xFF;// 1111 1111 ȫ���øߵ�ƽĬ��
	P1_3=0; // ���󰴼���һ��ɨ��
	if(P1_7==0){Delay(15);KeyNumber=1; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=5; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=9; while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=13;while(!P1_4);}
										 
	P1=0xFF;           
	P1_2=0; // ���󰴼���
	if(P1_7==0){Delay(15);KeyNumber=2; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=6; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=10;while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=14;while(!P1_4);}
										 
	P1=0xFF;           
	P1_1=0; // ���󰴼���
	if(P1_7==0){Delay(15);KeyNumber=3; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=7; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=11;while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=15;while(!P1_4);}
										 
	P1=0xFF;           
	P1_0=0; // ���󰴼���
	if(P1_7==0){Delay(15);KeyNumber=4; while(!P1_7);}
	if(P1_6==0){Delay(15);KeyNumber=8; while(!P1_6);}
	if(P1_5==0){Delay(15);KeyNumber=12;while(!P1_5);}
	if(P1_4==0){Delay(15);KeyNumber=16;while(!P1_4);}
	
	return KeyNumber;
}

void Delay(unsigned int i)
{
	unsigned int j;
	for (; i >0; i--)
	{
		for (j = 124; j > 0; j--);
	}
}	

void timer0() interrupt 1
{	
	TL0 = 0xD0;		//���ö�ʱ��ֵ
	TH0 = 0x5F;		//���ö�ʱ��ֵ
	i++;
	if(i == 12)	//һ��
	{
		P3_2 = 1;
		i = 0;
	}
}