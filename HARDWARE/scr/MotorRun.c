#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "motorrun.h"        //������Ҫ��ͷ�ļ�

/*���ߣ�
				�������				��Ƭ��
					A��		------	P1^0
					AA��		------	P1^1
					B��		------	P1^2
					BB��		------	P1^3
*/

void MOTOR_Init()
{
  GPIO_InitTypeDef GPIO_MOTOR;                     //����һ������GPIO�ı���
                             //ʹ��GPIOA�˿�ʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);                                //ʹ��GPIOB�˿�ʱ��
	

	GPIO_MOTOR.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_1|GPIO_Pin_0 ;                //׼������PB12 PB13 PB14
	GPIO_MOTOR.GPIO_Speed = GPIO_Speed_50MHz;                                     //IO����50Mhz
	GPIO_MOTOR.GPIO_Mode = GPIO_Mode_Out_PP;   		                              //���������ʽ
	GPIO_Init(GPIOB, &GPIO_MOTOR);   
  	
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void delay_10us(unsigned int  time)//��ʱtime*10 us
{
	while(time--)
	{Delay10us();}
}

/*
angle���Ƕȣ���Χ[0,360]
drct����ת����0��˳ʱ�룬1����ʱ��
speed��ת�٣���Χ[1,100]
*/
u8 MotorRun_flag;//������ʾ�����Ĵ򿪺͹ر�
void MotorRun(unsigned int nangle,unsigned int drct,unsigned int  speed)					//nangle=4096ΪһȦ						 speedת��75`400
{
	unsigned int  step;
	step=0;
	if(drct==0)
	{
		MotorRun_flag=1;
		while(nangle--)
		{
			
			if(MQTT_TxDataOutPtr != MQTT_TxDataInPtr){                    //if�����Ļ���˵�����ͻ�������������
				//3������ɽ���if
				//��1�֣�0x10 ���ӱ���
				//��2�֣�0x82 ���ı��ģ���ConnectPack_flag��λ����ʾ���ӱ��ĳɹ�
				//��3�֣�SubcribePack_flag��λ��˵�����ӺͶ��ľ��ɹ����������Ŀɷ�
				if((DMA_flag==0)&&((MQTT_TxDataOutPtr[2]==0x10)||((MQTT_TxDataOutPtr[2]==0x82)&&(ConnectPack_flag==1))||(SubcribePack_flag==1))){    
					if(MQTT_TxDataOutPtr[2]==0xc0)
					printf("����ping����:0x%x\r\n",MQTT_TxDataOutPtr[2]);  //������ʾ��Ϣ
					else 					printf("��������:0x%x\r\n",MQTT_TxDataOutPtr[2]);  //������ʾ��Ϣ
					MQTT_TxData(MQTT_TxDataOutPtr);                       //��������
					MQTT_TxDataOutPtr += TBUFF_UNIT;                      //ָ������
					if(MQTT_TxDataOutPtr==MQTT_TxDataEndPtr)              //���ָ�뵽������β����
						MQTT_TxDataOutPtr = MQTT_TxDataBuf[0];            //ָ���λ����������ͷ
				} 				
			}//�����ͻ��������ݵ�else if��֧��β
			switch(step)//8�ķ�ʽ����
			{
				case 0:A=1;AA=0;B=0;BB=0;break;
				case 1:A=1;AA=1;B=0;BB=0;break;
				case 2:A=0;AA=1;B=0;BB=0;break;
				case 3:A=0;AA=1;B=1;BB=0;break;
				case 4:A=0;AA=0;B=1;BB=0;break;
				case 5:A=0;AA=0;B=1;BB=1;break;
				case 6:A=0;AA=0;B=0;BB=1;break;
				case 7:A=1;AA=0;B=0;BB=1;break;
			}
			if(step==7)step=0;
			else step++;
			delay_10us(speed);
		}
	}
	else
	{
			MotorRun_flag=0;
		while(nangle--)
		{
			switch(step)
			{
				case 0:A=1;AA=0;B=0;BB=1;break;
				case 1:A=0;AA=0;B=0;BB=1;break;
				case 2:A=0;AA=0;B=1;BB=1;break;
				case 3:A=0;AA=0;B=1;BB=0;break;
				case 4:A=0;AA=1;B=1;BB=0;break;
				case 5:A=0;AA=1;B=0;BB=0;break;
				case 6:A=1;AA=1;B=0;BB=0;break;
				case 7:A=1;AA=0;B=0;BB=0;break;
			}
			if(step==7)step=0;
			else step++;
			delay_10us(speed);
		}
	}
	A=0;AA=0;B=0;BB=0;
						printf("%MotorRun_flag %d\r\n",MotorRun_flag);
}

void MotorStop() //����ֹͣ
{
	A=0;AA=0;B=0;BB=0;
}


