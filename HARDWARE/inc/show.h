#ifndef __SHOW_H
#define __SHOW_H
#include "sys.h"
#include "oled.h"
#include "led.h"        //������Ҫ��ͷ�ļ�
#include "usart3.h"        //������Ҫ��ͷ�ļ�
#include "motorrun.h"        //������Ҫ��ͷ�ļ�
void	Cut_screen(void);
void  main_sreen(void);//����Ļ
void data_show(void);
void show_Learn_instruction(void);//ѧϰָ����ʾ����
void set_show(void); //ѡ����Ļ
void show_admin(void);
	void show_beep(void);

extern u8 light,ppm,co;
extern u16 adc_light,adc_ppm,adc_co;
extern u8 tem,hum,people;
extern char show_num;//��Ļ��
extern char next_data;//��ʾ���ݵĵڶ���Ļ
extern unsigned char choose_show;//ѡ����ʾ����Ļ
extern unsigned char choose_admin;//ѡ���޸ĵ����ݵ���Ļ
extern u8 PPM_MAX,co_MAX;
extern u8 ppm_beep,ppm_beep_sta;
extern u8 co_beep,co_beep_sta;


#endif
