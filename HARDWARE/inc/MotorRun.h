#ifndef __MOTORRUN_H_
#define __MOTORRUN_H_
#include "SYS.h"
#include "pub_sub_message.h"
#include "total_wifi.h"
#include "time4.h"
#define A PBout(0)
#define AA PBout(14)
#define B PBout(15)
#define BB PBout(1)
void MOTOR_Init(void);
void delay_10us(unsigned int  time);//��ʱtime*10 us
void MotorRun(unsigned int nangle,unsigned int drct,unsigned int  speed)			;	//	nangle=4096ΪһȦ��	drct=0Ϊ��ʱ��ת����drct=1Ϊ˳ʱ��ת����  speedת����ʱ750`4000us��
void MotorStop(void);
extern unsigned int nangle;
extern u8 MotorRun_flag;
#endif
