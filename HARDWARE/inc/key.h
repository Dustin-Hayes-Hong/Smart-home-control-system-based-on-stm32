#ifndef __KEY_H
#define __KEY_H	
#define KEY0_IN_STA  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) //PB5����KEY1,��ȡ��ƽ״̬,�����ж�KEY1�Ƿ���
#define KEY1_IN_STA  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) //PB5����KEY1,��ȡ��ƽ״̬,�����ж�KEY1�Ƿ���
#define KEY2_IN_STA  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) //PB6����KEY2,��ȡ��ƽ״̬,�����ж�KEY2�Ƿ���
#define KEY3_IN_STA  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) //PB7����KEY3,��ȡ��ƽ״̬,�����ж�KEY2�Ƿ���
#include "usart1.h"
#include "show.h"
#include "delay.h"
#include "sys.h"

extern int Learn_IR_ctrl[5] ;

extern int IR_ctrl_on[5] ;
extern int IR_ctrl_off[5] ;

extern int IR_ctrl_on2[5] ;
extern int IR_ctrl_off2[5] ;

void Learn_instruction(void);//ѧϰң�ص�ָ��
void admin_sub(void);
void KEY_Init(void);	   //������ʼ��
void KEY_Exti_Init(void);  //�����ⲿ�жϳ�ʼ������
extern u8 choose;
extern u8 IR;
#endif
