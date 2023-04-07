
#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "usart1.h"     //������Ҫ��ͷ�ļ�

#if  USART1_RX_ENABLE                   //���ʹ�ܽ��չ���

unsigned int Usart1_RxCounter = 0;      //����һ����������¼����1�ܹ������˶����ֽڵ�����
char Usart1_RxBuff[255]; //����һ�����飬���ڱ��洮��1���յ�������
#endif
char Usart1_Rx_ok = 0;            //����һ������ 0����ʾ����δ��� 1����ʾ�������
/*-------------------------------------------------*/
/*����������ʼ������1���͹���                      */
/*��  ����bound��������                            */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void Usart1_Init(unsigned int bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;     //����һ������GPIO���ܵı���
    USART_InitTypeDef USART_InitStructure;   //����һ�����ô��ڹ��ܵı���
#if USART1_RX_ENABLE                         //���ʹ�ܽ��չ���
    NVIC_InitTypeDef NVIC_InitStructure;     //���ʹ�ܽ��չ��ܣ�����һ�������жϵı���
#endif

#if USART1_RX_ENABLE                                 //���ʹ�ܽ��չ���
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3
#endif

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //ʹ�ܴ���1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;              //׼������PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //IO����50M
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	       //����������������ڴ���1�ķ���
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //����PA9

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //׼������PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //�������룬���ڴ���1�Ľ���
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //����PA10

    USART_InitStructure.USART_BaudRate = bound;                                    //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //8������λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //1��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
#if USART1_RX_ENABLE               												   //���ʹ�ܽ���ģʽ
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	               //�շ�ģʽ
#else                                                                              //�����ʹ�ܽ���ģʽ
    USART_InitStructure.USART_Mode = USART_Mode_Tx ;	                           //ֻ��ģʽ
#endif
    USART_Init(USART1, &USART_InitStructure);                                      //���ô���1

#if USART1_RX_ENABLE  	         					        //���ʹ�ܽ���ģʽ
    USART_ClearFlag(USART1, USART_FLAG_RXNE);	            //������ձ�־λ
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);          //���������ж�
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);          //���������ж�
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;       //���ô���1�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//�ж�ͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	                        //���ô���1�ж�
#endif

    USART_Cmd(USART1, ENABLE);                              //ʹ�ܴ���1
}
char Usart_buff[1024];
int fputc(int ch, FILE *p) //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
{
    USART_SendData(USART1, (u8)ch);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
}

/***************************************************************************
* �� �� ����void send_byte(USART_TypeDef* USARTx,u8 byte)
* ����˵��������1����һ���ַ�
* ��    �Σ�USARTx��ʹ�õĴ��ڣ�byte�����͵��ַ�
* �� �� ֵ����
* ��    ע��2022-9-21
****************************************************************************/
void send_byte(USART_TypeDef *USARTx, u8 byte)
{
    while(!(USART_GetFlagStatus(USARTx, USART_FLAG_TC))); //����--��tc-������ɺ�txe���ͼĴ���Ϊ��

    USART_SendData(USARTx, byte);
}
/***************************************************************************
* �� �� ����void send_str(USART_TypeDef* USARTx,u8 *str)
* ����˵��������1����һ���ַ�
* ��    �Σ�USARTx��ʹ�õĴ��ڣ�*str�����͵��ַ���
* �� �� ֵ����
* ��    ע��2022-9-21
****************************************************************************/
void send_str(USART_TypeDef *USARTx, u8 *str)
{
    int len = 0;
    len = strlen((const char *)str);

    while(len--)
        send_byte(USARTx, *str++);
}
/***************************************************************************
* �� �� ����void send_str(USART_TypeDef* USARTx,u8 *str)
* ����˵��������1����һ���ַ�
* ��    �Σ�USARTx��ʹ�õĴ��ڣ�*str�����͵��ַ���,u8 len  ���͵ĳ���
* �� �� ֵ����
* ��    ע��2022-9-21
****************************************************************************/
void send_str_len(USART_TypeDef *USARTx, u8 *str, u8 len)
{
    while(len--)
        send_byte(USARTx, *str++);
}
/***************************************************************************
* �� �� ����void my_printf(USART_TypeDef* USARTx,char *fmt,...)
* ����˵�������ڸ�ʽ�����
* ��    �Σ�USARTx��ʹ�õĴ��ڣ�char *fmt��%%%,...
* �� �� ֵ����
* ��    ע��2022-9-21
****************************************************************************/
void my_printf(USART_TypeDef *USARTx, char *fmt, ...) //���ʣ�ap��ô�ƶ���ȡ������
{
    va_list ap;//������ȡ�����б��еĲ���
    va_start(ap, fmt); //��������ʼ��ap��ָ��fmt
    vsprintf(Usart_buff, fmt, ap); // �Ѳ���ap����fmtָ���ĸ�ʽд��buff
    va_end(ap);//����ap

    send_str(USARTx, (u8 *)Usart_buff);
    memset(Usart_buff, 0, sizeof(Usart_buff));
}
u8 USART_Receive_byte(USART_TypeDef *USARTx, u8 byte)
{
    while(!USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)); //USART_FLAG_RXNE��һʱ���������ݼĴ���������
    return	USART_ReceiveData(USARTx);//���ؽ��յ�������
}
u8 Usart_Receive_Buff[255];
u8 USART_Receive_str(USART_TypeDef *USARTx, u8 *str)
{
    int i = 0;

    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) //USART_FLAG_RXNE��һʱ���������ݼĴ���������
    {
        Usart_Receive_Buff[i] = USART_Receive_byte(USARTx, *str++);
    }
    return 0;

}

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        Usart_Receive_Buff[Usart1_RxCounter++] = USART_ReceiveData(USART1);//������ܵ�������
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
    if(USART_GetITStatus(USART1, USART_IT_IDLE))
    {
        USART1->SR;
        USART1->DR;
        Usart1_Rx_ok = 1;//��ʾ�������
        Usart1_RxCounter = 0;

    }
}
void voice_ctrl(void)//�������ƺ���
{
    if(Usart1_Rx_ok)//���ܵ�����
    {
        if(strstr((const char *)Usart_Receive_Buff, "LEDON")) //�����򿪵�ָ��
        {
					  data_sta("powerstate4",1);
            MotorRun(2048, 0, 5000);
					
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LEDOFF")) //�����رյ�ָ��
        {
					  data_sta("powerstate4",0);
            MotorRun(2048, 1, 5000);
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED1ON")) //�̵���1�򿪵�ָ��
        {
									  data_sta("powerstate",1);
            LED1 = 0;
						
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED1OFF")) //�̵���1�رյ�ָ��
        {
									  data_sta("powerstate",0);
            LED1 = 1;
						
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED2ON"))  //�̵���2�򿪵�ָ��
        {
									  data_sta("powerstate1",1);
            LED2 = 0;
										
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED2OFF")) //�̵���2�رյ�ָ��
        {
									  data_sta("powerstate1",0);
            LED2 = 1;	
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED3ON"))  //�̵���3�򿪵�ָ��
        {
									  data_sta("powerstate2",1);
            LED3 = 0;
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED3OFF"))  //�̵���3�رյ�ָ��
        {
									  data_sta("powerstate2",0);
            LED3 = 1;
        }

        else if(strstr((const char *)Usart_Receive_Buff, "LED4ON"))  //�̵���4�򿪵�ָ��
        {								
					data_sta("powerstate3",1);
            LED4 = 0;
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED4OFF"))  //�̵���4�رյ�ָ��
        {									  data_sta("powerstate3",0);
            LED4 = 1;
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED5ON"))  //ң�ص�ָ��
        {
						IR_ctrl_on[3]=0x00;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_on[i]);
            }
						
					 data_sta("VehACSwitch",1);
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED5OFF"))  //ң�ص�ָ��
        {
						IR_ctrl_off[3]=0x01;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_off[i]);
                send_byte(USART1, IR_ctrl_off[i]);
            }
					 data_sta("VehACSwitch",0);
        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED6ON"))  //ң�ص�ָ��
        {
					IR_ctrl_on[3]=0x02;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_on[i]);
                send_byte(USART1, IR_ctrl_on[i]);
            }

        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED6OFF")) //ң�ص�ָ��
        {
					IR_ctrl_off[3]=0x03;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_off[i]);
                send_byte(USART1, IR_ctrl_off[i]);
            }

        }
				        else if(strstr((const char *)Usart_Receive_Buff, "LED7ON"))  //ң�ص�ָ��
        {
					IR_ctrl_on[3]=0x04;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_on[i]);
                send_byte(USART1, IR_ctrl_on[i]);
            }

        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED7OFF")) //ң�ص�ָ��
        {
					IR_ctrl_off[3]=0x05;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_off[i]);
                send_byte(USART1, IR_ctrl_off[i]);
            }

        }        else if(strstr((const char *)Usart_Receive_Buff, "LED8ON"))  //ң�ص�ָ��
        {
					IR_ctrl_on[3]=0x06;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_on[i]);
                send_byte(USART1, IR_ctrl_on[i]);
            }

        }
        else if(strstr((const char *)Usart_Receive_Buff, "LED8OFF"))  //ң�ص�ָ��
        {
					IR_ctrl_off[3]=0x07;
            for(int i = 0; i < 5; i++)
            {
                send_byte(USART3, IR_ctrl_off[i]);
                send_byte(USART1, IR_ctrl_off[i]);
            }

        }
        Usart1_Rx_ok = 0;
        memset(Usart_Receive_Buff, 0, sizeof(Usart_Receive_Buff));
    }
}







