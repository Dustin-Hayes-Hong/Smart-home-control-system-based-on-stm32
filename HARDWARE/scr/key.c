#include "key.h"
#include "stm32f10x_exti.h"
/*-------------------------------------------------*/
/*����������ʼ��KEY��������                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                       //����һ������IO�Ľṹ��

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);     //ʹ��PA�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_4;           //׼������PB5,PB6,PB7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   		   //�������룬Ĭ��״̬�ǵ͵�ƽ
    GPIO_Init(GPIOB, &GPIO_InitStructure);            		   //����PA0
}

/*-------------------------------------------------*/
/*�������������ⲿ�жϳ�ʼ������.                  */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void KEY_Exti_Init(void)
{
    NVIC_InitTypeDef   NVIC_InitStructure; //����һ������IO�Ľṹ��
    EXTI_InitTypeDef   EXTI_InitStructure; //����һ�������жϵĽṹ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	         //ʹ��GPIO���ù���ʱ��
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4);   //����KEY1-PB55�ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);   //����KEY1-PB55�ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);   //����KEY2-PB6�ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7);   //����KEY3-PB7�ж���

    EXTI_InitStructure.EXTI_Line = EXTI_Line4;	                  //׼�������ⲿ5�ж���
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //�ⲿ�ж�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;        //�½��ش����ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��
    EXTI_Init(&EXTI_InitStructure);	 	                          //�����ⲿ�ж�5��

    EXTI_InitStructure.EXTI_Line = EXTI_Line5;	                  //׼�������ⲿ5�ж���
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //�ⲿ�ж�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;        //�½��ش����ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��
    EXTI_Init(&EXTI_InitStructure);	 	                          //�����ⲿ�ж�5��

    EXTI_InitStructure.EXTI_Line = EXTI_Line6;	                  //׼�������ⲿ6�ж���
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //�ⲿ�ж�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;        //�½��ش����ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��
    EXTI_Init(&EXTI_InitStructure);	 	                          //�����ⲿ�ж�6��

    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	          //�ⲿ�ж�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;       //�½��ش����ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //ʹ��
    EXTI_Init(&EXTI_InitStructure);	 	                          //�����ⲿ�ж�7��



    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			  //׼�������ⲿ�ж�5
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;     //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		      //�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //ʹ���ⲿ�ж�1ͨ��
    NVIC_Init(&NVIC_InitStructure);                               //�����ⲿ�ж�4

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			  //׼�������ⲿ�ж�5
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;     //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		      //�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				  //ʹ���ⲿ�ж�1ͨ��
    NVIC_Init(&NVIC_InitStructure);                               //�����ⲿ�ж�4

}

u8 choose;//ѡ����Ҫ�ı������
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)//ȷ�ϰ���
{
    Delay_Ms(10);//����
    if(!KEY0_IN_STA)
    {
        if(show_num != 0)
        {
            show_num = 0;
            choose_show = 0;
        }
        else	if(choose_show == 0) show_num = 1;
        else	if(choose_show == 1)
        {
            show_num = 2;
            choose_show = 0;
        }
        else	if(choose_show == 2) show_num = 3;

    }
    EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE5�ϵ��жϱ�־λ
}

//�ⲿ�ж�5-6-7�������
void EXTI9_5_IRQHandler(void)
{
    Delay_Ms(10);//����

    if(KEY1_IN_STA == 0) //����������Ӱ����ٴ��жϿ���KEY1��IO�����ƽ���Ƿ��ǵ͵�ƽ������ǽ���if��˵������������
    {

        if(show_num == 0) //�ڵ�һ��Ļѡ��
        {
            choose_show++;
            choose_show %= 3;
            set_show();//��ʾ��ͷ��ѡ����Ļ��
        }
        if(show_num == 2) //�ڵڶ���Ļѡ��
        {
            choose_show++;
            choose_show %= 3;
            set_show();//��ʾ��ͷ��ѡ����Ļ��
        }
        if(show_num == 1) //��������ʾ����Ļ
            next_data = !next_data;
        if(show_num == 3) //�ں���ѧϰ��ʾ����Ļ
            next_data = !next_data;
    }
    if(KEY2_IN_STA == 0) //����������Ӱ����ٴ��жϿ��� KEY2 ��IO�����ƽ���Ƿ��ǵ͵�ƽ������ǽ���if��˵������������
    {
        if(show_num == 2) //����ֵ�޸���ʾ����Ļ
        {
            if(choose_show == 1)
            {
                if(PPM_MAX < 99)PPM_MAX++;
            }
            else if(choose_show == 0 && co_MAX < 99)co_MAX++;
        }
        if(show_num == 3) //��ѧϰң����ʾ����Ļ
        {
            Learn_instruction();//ѧϰң�صĺ���
        }

    }
    if(KEY3_IN_STA == 0) //����������Ӱ����ٴ��жϿ��� KEY3 ��IO�����ƽ���Ƿ��ǵ͵�ƽ������ǽ���if��˵������������
    {
        if(show_num == 2) //����ֵ�޸���ʾ����Ļ
        {
            if(choose_show == 1)
            {
                if(PPM_MAX > 1)PPM_MAX--;
            }
            else if(choose_show == 0 && co_MAX > 1)co_MAX--;
        }
				if(show_num ==0)
				{
					auto_flag=!auto_flag;
				}
    }
    admin_sub();
    EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE5�ϵ��жϱ�־λ
    EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE6�ϵ��жϱ�־λ
    EXTI_ClearITPendingBit(EXTI_Line7);  //���LINE7�ϵ��жϱ�־λ
}
/***********************************************************
*@fuction	:admin_pub
*@brief		:��������ϱ��������º�ı��ֵ
*@param		:--
*@return	:void
*@author	:--
*@date		:2022-12-06
***********************************************************/
void admin_sub(void)
{
    char temp[256];             //������
    sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\""identifier15"\":%d,\""identifier16"\":%d,\""identifier6"\":%d},\"version\":\"1.0.0\"}", (int)PPM_MAX, co_MAX,auto_flag);  //��������
    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                //������ݵ����ͻ�����
}
/***********************************************************
*@fuction	:Learn_instruction
*@brief		ѧϰң�ص�ָ���ѧϰָ���ӡ������һ��ʾ
*@param		:����ģ�������˵������ѧϰָ��״̬
*@return	:void
*@author	:--
*@date		:2022-12-06
***********************************************************/
void Learn_instruction(void)
{
    if(!Learn_on_ok1)//ѧ��һ��ָ��  //�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;
    }
    else if(!Learn_off_ok1)//ѧ�ڶ���ָ��//�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;//��ѧϰͨ��++ ƫ����һ��ͨ����ѧϰ
    }
    else if(!Learn_on_ok2)//ѧ������ָ��//�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;//��ѧϰͨ��++ ƫ����һ��ͨ����ѧϰ
    }
    else if(!Learn_off_ok2)//ѧ������ָ��//�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;//��ѧϰͨ��++ ƫ����һ��ͨ����ѧϰ
    }
    else if(!Learn_on_ok3)//ѧ������ָ��//�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;//��ѧϰͨ��++ ƫ����һ��ͨ����ѧϰ
    }    else if(!Learn_off_ok3)//ѧ������ָ��//�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;//��ѧϰͨ��++ ƫ����һ��ͨ����ѧϰ
    }    else if(!Learn_on_ok4)//ѧ������ָ��//�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;//��ѧϰͨ��++ ƫ����һ��ͨ����ѧϰ
    }    else if(!Learn_off_ok4)//ѧ�ڰ���ָ��//�����ж���ʾδѧϰ������ѧϰ
    {
        for(int i = 0; i < 5; i++)
        {
            send_byte(USART3, Learn_IR_ctrl[i]);
            send_byte(USART1, Learn_IR_ctrl[i]);//��ӡ������һ
        }
        Learn_IR_ctrl[3] += 0x01;//��ѧϰͨ��++ ƫ����һ��ͨ����ѧϰ
    }
}


