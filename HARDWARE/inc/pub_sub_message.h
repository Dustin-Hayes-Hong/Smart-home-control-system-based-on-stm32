#ifndef __PUN_SUB_MESSAGE_H
#define __PUN_SUB_MESSAGE_H
#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "main.h"       //������Ҫ��ͷ�ļ�
#include "delay.h"      //������Ҫ��ͷ�ļ�
#include "usart1.h"     //������Ҫ��ͷ�ļ�
#include "usart2.h"     //������Ҫ��ͷ�ļ�
#include "timer3_ping.h"     //������Ҫ��ͷ�ļ�
#include "led.h"        //������Ҫ��ͷ�ļ�
#include "key.h"        //������Ҫ��ͷ�ļ�
#include "motorrun.h"        //������Ҫ��ͷ�ļ�
extern u8 auto_flag;

#define identifier1 "powerstate"//�̵���1
#define identifier2 "powerstate1"//�̵���2
#define identifier3 "powerstate2"//�̵���3
#define identifier4 "powerstate3"//�̵���4
#define identifier5 "powerstate4"//��������
#define identifier6 "powerstate5"//�Զ�ģʽ
#define identifier7 "powerstate6"//����
#define identifier8 "powerstate7"//�յ�2
#define identifier9 "powerstate8"//����2
#define identifier10 "powerstate9"//������
#define identifier11 "powerstate10"//һ����̼����
#define identifier12 "VehACSwitch"//�յ�
#define identifier13 "CO"//һ����̼
#define identifier14 "PPM"//����
#define identifier15 "PPM_MAX"//��������
#define identifier16 "CO_MAX"//һ����̼����
#define identifier17 "LightLux"//����
#define identifier18 "tem"//�¶�
#define identifier19 "hum"//ʪ��
#define identifier20 "pp"//����
/*                       ״̬�ϱ�                           */
void Data_State(void);
void init_State(void);
void judge_data_sta(void *str, uint16_t GPIO_Pin);
void data_sta(void * str,int cmd);
/*                       ״̬�ϱ�                           */
#endif
