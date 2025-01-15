#include <REGX51.H>
#include <intrins.h>
unsigned char m = 0;
unsigned char n = 0;
unsigned char tmp1;
unsigned char tmp2;
void EX0_Init(void);
void EX1_Init(void);
void Delay300ms();
void main()
{
	EX0_Init();
	EX1_Init();
	EA = 1;
	while(1)
	{
		P2 = 0xff;
	}
}

//�ⲿ�ж�0��ʼ��
void EX0_Init(void)
{

	//���ô�����ʽ �ⲿ�ж�0
	IT0 = 1; //�½��ش��� ���IE0��1
	EX0 = 1; // �ӿ��� IE:�ж�����Ĵ��� 
	PX0 = 0; //�ж����ȼ�-��
}
//�ⲿ�ж�1��ʼ��
void EX1_Init(void)
{

	//���ô�����ʽ �ⲿ�ж�0
	IT1 = 1;	//�½��ش��� ���IE0��1
	EX1 = 1;	// �ӿ��� IE:�ж�����Ĵ���  
	PX1 = 1;	//�ж����ȼ�-��
}

/*
1.�жϷ�����һ����һ��û�з���ֵ�ĺ���
2.�жϷ�����һ����һ��û�в����ĺ���
3.�жϷ���������������ؼ��� interrupt
4.interrupt n 0-4	8*n + 0013H = �ж�������ڵ�ַ
5.�жϷ��������ܱ����������������������
6.n ��� sing m(0-3)�����Ĵ�����
*/
void EX0_ISR(void) interrupt 0
{
	tmp1 = 0x55;
	for ( m = 0; m < 8; m++)
	{
		tmp1 = _cror_(tmp1, 1);
		P2 = tmp1;
		Delay300ms();
	}
}
void EX1_ISR(void) interrupt 2
{
	tmp2 = 0xfe;
		for ( n = 0; n < 8; n++)
	{
		tmp2 = _cror_(tmp2, 1);
		P2 = tmp2;
		Delay300ms();
	}
}

void Delay300ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 3;
	j = 72;
	k = 161;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

