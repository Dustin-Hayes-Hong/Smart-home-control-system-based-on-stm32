#include "time4.h"
/*-------------------------------------------------*/
/*����������ʱ��4ʹ��10uS��ʱ                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM4_ENABLE_10uS(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;            //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                          //����һ�������жϵı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);           //ʹ��TIM2ʱ��	
	TIM_DeInit(TIM4);                                             //��ʱ��2�Ĵ����ָ�Ĭ��ֵ	
	TIM_TimeBaseInitStructure.TIM_Period = 1; 	              //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=360;              //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //1��Ƶ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);            //����TIM2
	
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);                      //ʹ��TIM2����ж�    
	TIM_Cmd(TIM4,ENABLE);                                         //��TIM2                          
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;                 //����TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;       //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;              //�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                               //�����ж�
}

/*-------------------------------------------------*/
/*����������ʱ��2�жϷ�����                      */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM4_IRQHandler(void)
{	

	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){  //���TIM_IT_Update��λ����ʾTIM2����жϣ�����if	

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);     //���TIM2����жϱ�־ 	
	}
}



