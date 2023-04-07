#include "usart3.h"
#include "stdio.h"      //������Ҫ��ͷ�ļ�
#include "stdarg.h"		//������Ҫ��ͷ�ļ� 
#include "string.h"     //������Ҫ��ͷ�ļ�
void  uart3_init(u32 baud)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��USART1��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART1��GPIOAʱ��

    USART_DeInit(USART3);  //��λ����1
    //USART1_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PA9

    //USART1_RX	  PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB10

    //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2 ; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

    //USART ��ʼ������

    USART_InitStructure.USART_BaudRate = baud;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART3, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//�����ж�
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
}

char Usart3_RxCompleted = 0;            //����һ������ 0����ʾ����δ��� 1����ʾ�������
unsigned int Usart3_RxCounter = 0;      //����һ����������¼����2�ܹ������˶����ֽڵ�����
char Usart3_RxBuff[500]; //����һ�����飬���ڱ��洮��2���յ�������
u8 Usart3_Receive = 0;

/*-------------------------------------------------*/
/*������������3�����жϺ���                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
u8 Learn_on_ok1;
u8 Learn_off_ok1;
u8 Learn_on_ok2;
u8 Learn_off_ok2;
u8 Learn_on_ok3;
u8 Learn_off_ok3;
u8 Learn_on_ok4;
u8 Learn_off_ok4;
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE))
    {
        Usart3_RxBuff[Usart3_RxCounter] = USART_ReceiveData(USART3); //�������ݽ����ݴ浽����
        Usart3_RxCounter++;
        USART_ClearITPendingBit(USART3, USART_IT_RXNE); //��������жϱ�־λ
    }
    if(USART_GetITStatus(USART3, USART_IT_IDLE))
    {
        USART3->DR;//�����־λ
        USART3->SR;
        Usart3_RxCounter = 0;
        Usart3_Receive = 1;
        for(int i = 0; i < 5; i++)//�����յ������ݴ�ӡ����
            send_byte(USART1, Usart3_RxBuff[i]);
	/*---------------------------------------*/				
        if(!Learn_on_ok1)
        {
            if(Usart3_RxBuff[0] == 0xa2)
                Learn_on_ok1 = 1; //���յ�ѧϰ�յ���ɵ�ָ��
        }
        else if(!Learn_off_ok1)
				{
					            if(Usart3_RxBuff[0] == 0xa2)
                Learn_off_ok1 = 1; //���յ�ѧϰ�յ���ɵ�ָ��
				}
	/*---------------------------------------*/			
        else if(!Learn_on_ok2)
				{
					       if(Usart3_RxBuff[0] == 0xa2)
                Learn_on_ok2 = 1; //���յ�ѧϰ������ɵ�ָ��
				}	
        else if(!Learn_off_ok2)
				{
					       if(Usart3_RxBuff[0] == 0xa2)
                Learn_off_ok2 = 1; //���յ�ѧϰ������ɵ�ָ��
				}	
	/*---------------------------------------*/			
				   else if(!Learn_on_ok3)
				{
					       if(Usart3_RxBuff[0] == 0xa2)
                Learn_on_ok3 = 1; //���յ�ѧϰ�յ�2��ɵ�ָ��
				}					
        else if(!Learn_off_ok3)
				{
					       if(Usart3_RxBuff[0] == 0xa2)
                Learn_off_ok3 = 1; //���յ�ѧϰ�յ�2��ɵ�ָ��
				}	

		/*---------------------------------------*/					
							        else if(!Learn_on_ok4)
				{
					       if(Usart3_RxBuff[0] == 0xa2)
                Learn_on_ok4 = 1; //���յ�ѧϰ����2��ɵ�ָ��
				}				
				else if(!Learn_off_ok4)
				{
					       if(Usart3_RxBuff[0] == 0xa2)
                Learn_off_ok4 = 1; //���յ�ѧϰ����2��ɵ�ָ��
				}	
	
					/*---------------------------------------*/		
			 memset(Usart3_RxBuff, 0, sizeof(Usart3_RxBuff));			
    }
}


