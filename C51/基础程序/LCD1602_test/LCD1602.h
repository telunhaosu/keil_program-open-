/*************************************************
File name: LCD1602.h
Author: Dong
Date: 2023.4.18 22:04
**************************************************/

#ifndef __LCD1602_H__ 
#define __LCD1602_H__
#include <reg51.h>


#define LCD1602_DB P0


//IO�ӿ����� LCD1602_DB P0
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_EN = P2^7;

//LCD1602ָ��

//��ʾģʽ����ָ��
#define LCD_MODE_PIN8 	0x38	//8λ���ݿڣ����У�5*8����
#define LCD_MODE_PIN4 	0x28	//4λ����λ�����У�5*8����
#define LCD_SCREEN_CLR 	0x01	//����
#define LCD_SCREEN_RST 	0x02	//��긴λ

//��ʾ����ָ��
#define LCD_DIS_CUR_BLK_ON 0x0F	//��ʾ������ʾ��꣬�����˸
#define LCD_DIS_CUR_ON		 0x0E //��ʾ������ʾ��꣬��겻��˸
#define LCD_DIS_ON				 0x0C	//��ʾ��������ʾ��꣬��겻��˸
#define LCD_DIS_OFF				 0x08	//��ʾ�أ����أ���겻��˸

//��ʾģʽ����(���뷽ʽ����)
#define LCD_CUR_RIGHT			 0x06	//������ƣ���ʾ���ƶ�
#define LCD_CUR_LEFT			 0x04	//������ƣ�����ʾ���ƶ���
#define LCD_DIS_MODE_ADD	 0x07 //������AC(��ַָ��)��1������ƽ��
#define LCD_DIS_MODE_DECADE  0x05	//������AC�Լ�������ƽ��

//�����λָ��
#define	LCD_CUR_MOVE_LEFT  0x10	//�������
#define	LCD_CUR_MOVE_RIGHT 0x14	//�������
#define LCD_DIS_MOVE_LEFT	 0x18	//��ʾ����
#define LCD_DIS_MOVE_RIGHT 0x1C	//�������

//��������
void DelayMS(unsigned char x);
//д��ָ��(æ���)
void LCDWriteCmd(unsigned char cmd);
void LCDWriteDate(unsigned char date);
void LCDInit();
void LCDShowStr(unsigned char x, unsigned char y, unsigned char *Str);
#endif