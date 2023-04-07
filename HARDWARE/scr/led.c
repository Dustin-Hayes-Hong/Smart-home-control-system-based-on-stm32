#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "led.h"        //������Ҫ��ͷ�ļ�

/*-------------------------------------------------*/
/*����������ʼ��LED����                            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                     //����һ������GPIO�ı���

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);                                //ʹ��GPIOA�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_5;                                     //׼������PA5
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                     //IO����50Mhz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   		                              //��¥�����ʽ
    GPIO_Init(GPIOA, &GPIO_InitStructure);            		                              //����PA5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            		                              //����PA5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   		                              //��¥�����ʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;                                     //IO����50Mhz
    GPIO_Init(GPIOA, &GPIO_InitStructure);            		                              //����PA5
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    BEEP = 1;

}





