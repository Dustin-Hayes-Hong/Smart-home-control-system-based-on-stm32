#ifndef __USART1_H
#define __USART1_H
#include "total_wifi.h"
#include "stdio.h"      //������Ҫ��ͷ�ļ�
#include "stdarg.h"		//������Ҫ��ͷ�ļ� 
#include "string.h"     //������Ҫ��ͷ�ļ�
#define USART1_RX_ENABLE  1
void Usart1_Init(unsigned int);     //����1 ��ʼ������
void send_str_len(USART_TypeDef* USARTx,u8 *str,u8 len);
extern char Usart1_Rx_ok ;            //����һ������ 0����ʾ����δ��� 1����ʾ�������
extern u8 Usart_Receive_Buff[255];
void voice_ctrl(void);
void send_byte(USART_TypeDef *USARTx, u8 byte);
extern int IR_ctrl_on[5]; 
extern int IR_ctrl_off[5] ; 

#endif


