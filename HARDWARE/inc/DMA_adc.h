#ifndef __DMA_ADC_H
#define __DMA_ADC_H	
#include "sys.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
void  Adc1_Init(void);
void  Adc2_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
 u16  Get_Adc2(u8 ch); 
u16 Get_Adc2_Average(u8 ch,u8 times); 






// ע�⣺����ADC�ɼ���IO����û�и��ã�����ɼ���ѹ����Ӱ��
/********************ADC1����ͨ�������ţ�����**************************/
#define    ADC_APBxClock_FUN             RCC_APB2PeriphClockCmd
#define    ADC_CLK                       RCC_APB2Periph_ADC1

#define    ADC_GPIO_APBxClock_FUN        RCC_APB2PeriphClockCmd
#define    ADC_GPIO_CLK                  RCC_APB2Periph_GPIOA  
#define    ADC_PORT                      GPIOA

// ע��
// 1-PC0 �ڰԵ�����ӵ��Ƿ�������Ĭ�ϱ�����
// 2-PC0 ��ָ��������ӵ���SPI FLASH�� Ƭѡ��Ĭ�ϱ�����
// ���� PC0 �� ADC ת��ͨ����ʱ�򣬽�����ܻ������

// ת��ͨ������
#define    NOFCHANEL										 3

#define    ADC_PIN0                      GPIO_Pin_0
#define    ADC_CHANNEL0                  ADC_Channel_0


#define    ADC_PIN1                      GPIO_Pin_1
#define    ADC_CHANNEL1                  ADC_Channel_1

#define    ADC_PIN6                      GPIO_Pin_6
#define    ADC_CHANNEL6                  ADC_Channel_6



// ADC1 ��Ӧ DMA1ͨ��1��ADC3��ӦDMA2ͨ��5��ADC2û��DMA����
#define    ADC_x                         ADC1
#define    ADC_DMA_CHANNEL               DMA1_Channel1
#define    ADC_DMA_CLK                   RCC_AHBPeriph_DMA1
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

/**************************��������********************************/
void               ADCx_Init                               (void);
u16 Get_Adc_Average(u8 ch,u8 times);

#endif 
