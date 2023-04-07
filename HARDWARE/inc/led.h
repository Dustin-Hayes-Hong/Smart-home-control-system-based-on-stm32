#ifndef __LED_H
#define __LED_H
#include "sys.h"

#define IO_A7_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_7)  //PA7  ����LED1,��ȡ��ƽ״̬�������ж�LED1�ǵ�������Ϩ��
#define IO_A8_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8)  //PA8  ����LED2,��ȡ��ƽ״̬�������ж�LED2�ǵ�������Ϩ��
#define IO_A12_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12) //PA12 ����LED3,��ȡ��ƽ״̬�������ж�LED3�ǵ�������Ϩ��
#define IO_A11_IN_STA   GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) //PA11 ����LED4,��ȡ��ƽ״̬�������ж�LED4�ǵ�������Ϩ��
#define IO_A5_IN_STA   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) //PA11 ����LED4,��ȡ��ƽ״̬�������ж�LED4�ǵ�������Ϩ��

#define BEEP    			PBout(9) //SCL
#define LED1    			PAout(7) //SCL
#define LED2    			PAout(8) //SCL
#define LED3    			PAout(11) //SCL
#define LED4    			PAout(12) //SCL
void LED_Init(void);               //��ʼ��	
void LED_AllOn(void);              //��������LED
void LED_AllOff(void);             //Ϩ������LED

#endif
