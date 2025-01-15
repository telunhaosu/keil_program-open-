#include <reg51.h>
#include <intrins.h>
sbit crot1 = P3^0;
sbit crot2 = P3^1;
char i = 0;
char j = 0;
unsigned char tmp1 = ~0x3f; 
unsigned char tmp2 = ~0x3f; 
unsigned char led[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void delay(unsigned int i)
{
	unsigned int j;
	for (; i >0; i--)
	{
		for (j = 124; j > 0; j--);
	}
}	

void main()
{
	//��ʱ����ʼ��
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xD0;		//���ö�ʱ��ֵ
	TH0 = 0x6F;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	EA = 1; 	//���жϴ�
	ET0 = 1;	//����T0�ж�
	TR0 = 1;	//������ʱ��T0
	
	// /INT0��ʼ��
	IT0 = 1;
	EX0 = 1;
	// /INT1��ʼ��
	IT1 = 1;
	EX1 = 1;
	
	EA = 1;	//�ж��ܿ���
	while(1)
	{
		P3 = 0xfd;
		P2 = tmp2;
		delay(15);
		P3 = 0xfe;
		P2 = tmp1;	
		delay(15);
	};
}

void timer0() interrupt 1
{	
	TR0 = 0;
	TL0 = 0xD0;		//���ö�ʱ��ֵ
	TH0 = 0x5F;		//���ö�ʱ��ֵ
	i++;
	if(i == 20)	//һ��
	{
		
		tmp1 = ~led[(j+1) % 10];
		j++;
		tmp2 = ~led[j / 10];
		if (j == 60)
		{
			 j = 0;
		}
		i = 0;
	}
	TR0 = 1;
}
void int0_int() interrupt 0
{
	TR0 = ~TR0;
}

void int1_int() interrupt 2
{
	TR0 = 0;			//�ض�ʱ��
	TL0 = 0xD0;		//���ö�ʱ��ֵ
	TH0 = 0x5F;		//���ö�ʱ��ֵ
	TF0 = 0;
	//��ʾ����
	tmp1 = ~0x3f; 
	tmp2 = ~0x3f;
	i = 0;
	j = 0;
}