#include "infrared.h"
uint8_t buf[128], cnt1;
uint16_t bufLen;
void key_IR()
{
	usart1_echo();//����һ����
		switch (IR) 
		{
			case 1:	//����2��������ѧϰ
					bufLen = IR_Learn_Pack(buf, 0x01);//��������ϲ����س���
					send_str_len(USART3,buf,bufLen);//����ָ�������
			
		break;
		case 2:	//��������˫�����ⷢ��
		case 3:
						bufLen = IR_Send_Pack(buf, 0x01);//��������ϲ����س���
						send_str_len(USART3,buf,bufLen);//����ָ�������
		break;
		default:  IR=0;
		break;
	
	}
}
void usart1_echo(void)//����һ����
{
		if(Usart3_Receive)//�����Ľ������
		{	
			Usart3_Receive=0;//�����־λ
			send_str_len(USART1,Usart3_RxBuff,Usart3_RxCompleted);	//������ģ�鷢�ͻ�����������ʾ��pc
			Usart3_RxCompleted = 0;//���������±�����	
 			memset(Usart3_RxBuff,0,sizeof(Usart3_RxBuff));//�����������
		}
}
//��У���
static uint8_t Get_Check(uint8_t *data, uint16_t len) {
	uint8_t sum = 0;
	uint16_t i;
	for (i = 0; i < len; i++) {
		sum += data[i];
	}
	return sum;
}

//��������ѧϰָ�����
uint16_t IR_Learn_Pack(uint8_t *data, uint8_t index) {
	uint8_t *p = data;
	*p++ = FRAME_START;
	*p++ = 0x08;
	*p++ = 0x00;
	*p++ = MODULE_ADDR;
	*p++ = 0x10;
	*p++ = 0x01;

	*p = Get_Check(&data[3], p - data - 3);
	 p++;
	*p++ = FRAME_END;
	return p - data;
}

//�������뷢��ָ�����
uint16_t IR_Send_Pack(uint8_t *data, uint8_t index) {
	uint8_t *p = data;
	*p++ = FRAME_START;
	*p++ = 0x08;
	*p++ = 0x00;
	*p++ = MODULE_ADDR;
	*p++ = 0x12;
	*p++ = index;
	*p = Get_Check(&data[3], p - data - 3);
	p++;
	*p++ = FRAME_END;
	return p - data;
}
