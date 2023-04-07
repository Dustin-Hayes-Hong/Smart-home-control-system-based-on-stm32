#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"
#include "show.h"
#include "usart1.h"

void  uart3_init(u32 baud);
extern char Usart3_RxCompleted ;            //����һ������ 0����ʾ����δ��� 1����ʾ�������
extern unsigned int Usart3_RxCounter ;      //����һ����������¼����2�ܹ������˶����ֽڵ�����
extern char Usart3_RxBuff[500]; //����һ�����飬���ڱ��洮��2���յ�������
extern u8 Usart3_Receive;

extern u8 Learn_on_ok1;
extern u8 Learn_off_ok1;
extern u8 Learn_on_ok2;
extern u8 Learn_off_ok2;

extern u8 Learn_on_ok3;
extern u8 Learn_off_ok3;
extern u8 Learn_on_ok4;
extern u8 Learn_off_ok4;

extern int Learn_IR_ctrl_on[5];
extern int Learn_IR_ctrl_off[5];
void u3_printf(char* fmt,...) ;		
void  Learn_instruction(void);
#endif
