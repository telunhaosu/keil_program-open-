/*-----------------------------------------------
Function: �ý����PWM�ź�ʵ��LED������
Description: LED�ɰ��𽥱������������𽥱䰵ѭ��
Author: Zhang Kaizhou
Date: 2019-6-11 17:47:35
-----------------------------------------------*/

#include <REGX52.H>
#include <INTRINS.H>
#define uchar unsigned char
#define uint unsigned int
#define PERIOD 500
/*ȫ�ֱ�������*/
uint low = 0;
	
/*�˿ڶ���*/
//sbit led = P2^7;

/*��������*/
void delay(uint xus);

/*������*/
void main(){
	while(1){
		P2 = 0xFF;
			delay(5000);
		for(low = 0; low < PERIOD; low++){
			P2 = 0x00;
			delay(low);
			P2 = 0xFF;
			delay(PERIOD - low);
		}
		P2 = 0x00;
			delay(5000);
		for(low = PERIOD - 1; low > 0; low--){
			P2 = 0x00;
			delay(low);
			P2 = 0xFF;
			delay(PERIOD - low);
		}
	}
}

/*��ʱ����*/
void delay(uint xus){ // ��ʱ9.766us * x + 8.682us(����������)
	while(xus--);
}



