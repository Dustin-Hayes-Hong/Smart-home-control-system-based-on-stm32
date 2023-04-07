#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
#include "usart1.h"   
//IO��������
#define DHT11_IO_IN()  {GPIOB->CRH&=0XFFFFFFF0;GPIOB->CRH|=8<<0;}
#define DHT11_IO_OUT() {GPIOB->CRH&=0XFFFFFFF0;GPIOB->CRH|=3<<0;}
////IO��������											   
#define	DHT11_DQ_OUT PBout(8) //���ݶ˿�	PB11 
#define	DHT11_DQ_IN  PBin(8)  //���ݶ˿�	PB11 


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *humi,u8 *temp)   ;//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif






