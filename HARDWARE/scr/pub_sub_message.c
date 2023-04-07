#include "pub_sub_message.h"
#include "total_wifi.h"
char *star_sp, *end_sp; //������ȡ��ʶ��
char identifier_temp[50];//���ڴ�ű�ʶ��
int identifier_data;//���ڴ���·�������

void  publish_message(void)
{
    //	����:{"method":"thing.service.property.set","id":"2092800572","params":{"CO_MAX":53},"version":"1.0.0"}
    printf("����:%s\r\n", &MQTT_CMDOutPtr[2]);                //���������Ϣ
    if(star_sp = strstr((char *)MQTT_CMDOutPtr + 2, (char *)"params")) //��λ�õ���ʶ��ǰ����ַ� �����������ʶ���ж��
    {
        end_sp = strstr(star_sp + 10, "\":"); //��λ�õ���ʶ��������ַ� �����������ʶ���ж��
        memcpy(identifier_temp, star_sp + 10, (end_sp) - (star_sp + 10)); //����ʶ����ȡ
        identifier_data = atoi((const char *)end_sp + 2); //�õ��·�������
        if(!(strcmp(identifier_temp, ""identifier1""))) //�̵���1
        {
            judge_data_sta(""identifier1"", GPIO_Pin_7); //�жϵ�ƽ״̬��������app
            LED1 = !identifier_data;//���Ƽ̵���
        }
        else if(!(strcmp(identifier_temp, ""identifier2"")))//�̵�����
        {
            judge_data_sta(""identifier2"", GPIO_Pin_8); //�жϵ�ƽ״̬��������app
            LED2 = !identifier_data;//���Ƽ̵���
        }
        else if(!(strcmp(identifier_temp, ""identifier3"")))//�̵�����
        {
            judge_data_sta(""identifier3"", GPIO_Pin_11); //�жϵ�ƽ״̬��������app
            LED3 = !identifier_data;//���Ƽ̵���
        }
        else if(!(strcmp(identifier_temp, ""identifier4"")))//�̵�����
        {
            judge_data_sta(""identifier4"", GPIO_Pin_12); //�жϵ�ƽ״̬��������app
            LED4 = !identifier_data;//���Ƽ̵���
        }
        else if(!(strcmp(identifier_temp, ""identifier5"")))//����
        {
            if(identifier_data)
            {
                data_sta(""identifier5"", 1);
                MotorRun(2048, 0, 5000);
            }
            else
            {
                data_sta(""identifier5"", 0);
                MotorRun(2048, 1, 5000);
            }
        }
        else if(!(strcmp(identifier_temp, ""identifier6"")))//�Զ�ģʽ
        {
            auto_flag = identifier_data;//����ģʽ
        }
        else if(!(strcmp(identifier_temp, ""identifier7"")))//����
        {
            if(identifier_data)
            {
                IR_ctrl_on[3] = 0x02;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_on[i]);
                    send_byte(USART1, IR_ctrl_on[i]);
                }
            }
            else
            {
                IR_ctrl_off[3] = 0x03;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_off[i]);
                    send_byte(USART1, IR_ctrl_off[i]);
                }
            }
        }
        else if(!(strcmp(identifier_temp, ""identifier8"")))//����
        {
            if(identifier_data)
            {
                IR_ctrl_on[3] = 0x04;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_on[i]);
                    send_byte(USART1, IR_ctrl_on[i]);
                }
            }
            else
            {
                IR_ctrl_off[3] = 0x05;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_off[i]);
                    send_byte(USART1, IR_ctrl_off[i]);
                }
            }
        }
        else if(!(strcmp(identifier_temp, ""identifier9"")))//����
        {
            if(identifier_data)
            {
                IR_ctrl_on[3] = 0x06;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_on[i]);
                    send_byte(USART1, IR_ctrl_on[i]);
                }
            }
            else
            {
                IR_ctrl_off[3] = 0x07;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_off[i]);
                    send_byte(USART1, IR_ctrl_off[i]);
                }
            }
        }
        else if(!(strcmp(identifier_temp, ""identifier12"")))//����
        {
            if(identifier_data)
            {
                IR_ctrl_on[3] = 0x00;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_on[i]);
                    send_byte(USART1, IR_ctrl_on[i]);
                }
            }
            else
            {
                IR_ctrl_off[3] = 0x01;
                for(int i = 0; i < 5; i++)
                {
                    send_byte(USART3, IR_ctrl_off[i]);
                    send_byte(USART1, IR_ctrl_off[i]);
                }
            }
        }
        else if(!(strcmp(identifier_temp, ""identifier15""))) //��������
            PPM_MAX = identifier_data; //�����ݸ�ֵ
        else if(!(strcmp(identifier_temp, ""identifier16""))) //һ����̼����
            co_MAX = identifier_data; //�����ݸ�ֵ
        memset(identifier_temp, 0, 50);
    }
    MQTT_CMDOutPtr += CBUFF_UNIT;                             	 //ָ������
    if(MQTT_CMDOutPtr == MQTT_CMDEndPtr)           	           //���ָ�뵽������β����
        MQTT_CMDOutPtr = MQTT_CMDBuf[0];          	             //ָ���λ����������ͷ
}
/*-------------------------------------------------*/
/*����������ʱ�ϴ��������ݵ�����                   */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
extern unsigned int SystemTimer ;
extern unsigned int TEHUTimer ;
void Data_State(void)
{
    char temp[500];             //������
    if((SystemTimer - TEHUTimer) >= 6)                                    //ȫ��ʱ�� �� ��ʱʱ�����ٲ�1s������if
    {
        TEHUTimer = SystemTimer;                                           //�ѵ�ǰ��ȫ��ʱ�䣬��¼����ʪ�ȼ�ʱ����
        sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\""identifier18"\":%d,\""identifier19"\":%d,\""identifier17"\":%d,\""identifier13"\":%d,\""identifier14"\":%d,\""identifier20"\":%d},\"version\":\"1.0.0\"}", tem, hum, light, co, ppm, people); //��������
        MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                //������ݵ����ͻ�����
    }
}
void init_State(void)
{

    char temp[600];             //������
    sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\""identifier18"\":%d,\""identifier19"\":%d,\""identifier17"\":%d,\""identifier13"\":%d,\""identifier14"\":%d,\""identifier15"\":%d,\
	\""identifier16"\":%d,\""identifier1"\":0,\""identifier2"\":0,\""identifier3"\":0,\""identifier4"\":0},\"version\":\"1.0.0\"}", tem, hum, light, co, ppm, PPM_MAX, co_MAX); //��������
    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp));                //������ݵ����ͻ�����

}



	/*-------------------------------------------------*/
	/*���������������ص�״̬��������                   */
	/*��  ������                                       */
	/*����ֵ����                                       */
	/*-------------------------------------------------*/
	void data_sta(void *str, int cmd)
	{
			char temp[TBUFF_UNIT];                   //����һ����ʱ������
			memset(temp, 0, TBUFF_UNIT);
			sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"%s\":%d},\"version\":\"1.0.0\"}", str, cmd); //���LED2�Ǹߵ�ƽ��˵����Ϩ��״̬����Ҫ�ظ��ر�״̬��������
			MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp)); //������ݣ�������������
	}
	/*-------------------------------------------------*/
	/*�������������жϿ��ص�״̬��������                   */
	/*��  ������                                       */
	/*����ֵ����                                       */
	/*-------------------------------------------------*/
	void judge_data_sta(void *str, uint16_t GPIO_Pin)
	{
			char temp[TBUFF_UNIT];                   //����һ����ʱ������
			memset(temp, 0, TBUFF_UNIT);
			if( GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin))//�ж�io�ĵ�ƽ
					sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"%s\":1},\"version\":\"1.0.0\"}", str); //���LED2�Ǹߵ�ƽ��˵����Ϩ��״̬����Ҫ�ظ��ر�״̬��������
			else
					sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"%s\":0},\"version\":\"1.0.0\"}", str); //���LED2�Ǹߵ�ƽ��˵����Ϩ��״̬����Ҫ�ظ��ر�״̬��������
			MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp)); //������ݣ�������������
	}


