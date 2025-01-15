#include <reg51.h>	//��Ƭ��ͷ�ļ�
//�궨��
#define uint unsigned int	
#define uchar unsigned char
uchar ii;
//λ����
sbit k1=P2^0;
sbit k2=P2^1;
sbit k3=P2^2;
sbit k4=P2^3;
sbit k5=P2^4;
sbit k6=P2^5;
sbit k7=P2^6;
sbit k8=P2^7;
//������
sbit led0=P1^0;
sbit led1=P1^1;
sbit led2=P1^2;
sbit led3=P1^3;
sbit led4=P1^4;
sbit led5=P1^5;
sbit led6=P1^6;
sbit led7=P1^7;
//��������
void Usart_Init(void);
void DelayMs(uint xms);
void Send_Data(uchar Key_val);
void Keyscan(void);

//������
void main()
{
	Usart_Init();
	while(1)	//ѭ��
	{
		 Keyscan();
	}
}

//�����жϳ�ʼ��
void Usart_Init(void)
{
    TMOD=0X20;//��ʱ��1��ʽ2
    TH1=0xF3;         //��������ʼֵ���ã�ע�Ⲩ������4800
    TL1=0xF3;
    TR1=1;//�򿪶�ʱ��
		SM0=0;//���ô��ڹ�����ʽ
    SM1=1;
		REN = 1;
    EA=1;//�����ж�
    ES=1;//�򿪴����ж�
}

//��ʱ����
void DelayMs(uint xms)
{   
	uchar i,j;                        
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

//�������ݺ���
void Send_Data(uchar Key_val)
{
    SBUF=Key_val;      //��Ҫ���͵����ݴ��뷢�ͻ�������
    while(!TI);        //�������жϱ�־λû����1(���ڷ�������)���͵ȴ�
    TI=0;	//��������ɣ�TI�Զ���1�������������
}
 
//��������
void Keyscan(void)
{
	uchar Val;	//����ֲ�����
	if(k1==0)		//�������k1
	{
		DelayMs(10);//����
		if(k1==0)	//ȷ�ϰ���k1
		{
					Val=0;

		}
		while(!k1){};	//�ȴ������ͷ�
		Send_Data(Val);	//���͡�0��
	}
	if(k2==0)		//�������k2
	{
		DelayMs(10);//����
		if(k2==0)	//ȷ�ϰ���k2
		{
				Val=1;
		}
		while(!k2);	//�ȴ������ͷ�
		Send_Data(Val);	//���͡�1��
	}
	if(k3==0)		//�������k3
	{
		DelayMs(10);//����
		if(k3==0)	//ȷ�ϰ���k3
		{
				Val=2;	//���͡�2��
		}
		while(!k3);	//�ȴ������ͷ�
		Send_Data(Val);
	}
	if(k4==0)		//�������k4
	{
		DelayMs(10);//����
		if(k4==0)	//ȷ�ϰ���k4
		{
				Val=3;	//���͡�3��
		}
		while(!k4);	//�ȴ������ͷ�
		Send_Data(Val);
	}
	if(k5==0)		//�������k5
	{
		DelayMs(10);//����
		if(k5==0)	//ȷ�ϰ���k5
		{
				Val=4;
		}
		while(!k5){};	//�ȴ������ͷ�
		Send_Data(Val);	//���͡�4��
	}
	if(k6==0)		//�������k6
	{
		DelayMs(10);//����
		if(k6==0)	//ȷ�ϰ���k6
		{
				Val=5;
		}
		while(!k6);	//�ȴ������ͷ�
		Send_Data(Val);	//���͡�6��
	}
	if(k7==0)		//�������k7
	{
		DelayMs(10);//����
		if(k7==0)	//ȷ�ϰ���k7
		{
				Val=6;
		}
		while(!k7);	//�ȴ������ͷ�
		Send_Data(Val);	//���͡�7��
	}
	if(k8==0)		//�������k8
	{
		DelayMs(10);//����
		if(k8==0)	//ȷ�ϰ���k8
		{
				Val=7;
		}
		while(!k8);	//�ȴ������ͷ�
		Send_Data(Val);	//���͡�7��
	}
}
void uart() interrupt 4
{
	if(RI)
	{
			uchar receiveData;
	ii=SBUF;                   
	 switch(ii)
	{
		case 0:	//�յ���0��
			led0=~led0;
			break;
		case 1:	//�յ���1��
			led1=~led1;
			break;
		case 2:	//�յ���2��
			led2=~led2;
			break;
		case 3:	//�յ���3��
			led3=~led3;
			break;
		case 4:	//�յ���4��
			led4=~led4;
			break;
		case 5:	//�յ���5��
			led5=~led5;
			break;
		case 6:	//�յ���6��
			led6=~led6;
			break;
		case 7:	//�յ���7��
			led7=~led7;
			break;
		default:
			break;
	}
	receiveData=SBUF;        //��ȥ���յ�������
	RI=0;                    //��������жϱ�־λ
	}
}

