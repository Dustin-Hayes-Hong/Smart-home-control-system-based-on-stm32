#include "total_wifi.h"
#include "pub_sub_message.h"
#include "DMA_adc.h"
#include "show.h"
#include "time4.h"
#include "usart3.h"
#include "infrared.h"
#include "dht11.h"
#include "motorrun.h"        //������Ҫ��ͷ�ļ�
void data_caiji(void);
void ctrl_auto(void);
extern char SubcribePack_flag;   //���ı���״̬      1�����ı��ĳɹ�
unsigned int SystemTimer = 0;   //����ȫ�ּ�ʱ�ı���           ��λ��
unsigned int TEHUTimer = 0;     //������ʪ�Ȳɼ��ļ�ʱ�ı���   ��λ��
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

int Learn_IR_ctrl[5] = {0xFA, 0xFD, 0x01, 0x00, 0xDF};//����ѧϰң�ص�ָ��

int IR_ctrl_on[5] = {0xFA, 0xFD, 0x02, 0x00, 0xDF};//���Ϳ��Ƶ�ָ��
int IR_ctrl_off[5] = {0xFA, 0xFD, 0x02, 0x01, 0xDF };//���Ϳ��Ƶ�ָ��

u8 light, ppm, co;//������������
u16 adc_light, adc_ppm, adc_co;//�ɼ�����ADC��ֵ
u8 tem, hum, people;//������������
u8 PPM_MAX = 50, co_MAX = 50;//���ݵ�����
int main(void)// A1 F1 01 FA DE         A1 F1 02 F6 FD    A1 F1 01 59 DE
{
    Delay_Init();                   //��ʱ���ܳ�ʼ��
    Usart1_Init(9600);              //����1���ܳ�ʼ����������9600
    uart3_init(9600);
 
    //LED��ʼ��
    KEY_Init();                     //������ʼ��
    KEY_Exti_Init();//�ⲿ�жϳ�ʼ��
    ADCx_Init();//adc�ɼ���ʼ
    OLED_Init();//oled��ʾ��ʼ��
    WiFi_ResetIO_Init();            //��ʼ��WiFi�ĸ�λIO
    AliIoT_Parameter_Init();	    //��ʼ�����Ӱ�����IoTƽ̨MQTT�������Ĳ���
    LED_Init();
    MOTOR_Init();//���������ʼ��
    DHT11_Init();//��ʪ�ȳ�ʼ
    TIM2_ENABLE_200MS();//��ʱ�ϴ��Ķ�ʱ����ʼ��
    while(1)                      //��ѭ��
    { 
        Connect_server();//���ӷ������ĺ���
        if(SubcribePack_flag)//�����������Ž���
        {
						data_caiji();//�ɼ����ݺ���
            ctrl_auto();//�Զ����Ƶĺ���
            Cut_screen();//��������       
            voice_ctrl();//��������
        }
    }
}
u8 people_num_sta,people_num;//�����ж������Ƿ����ӵ�
void data_caiji(void)
{
    if(IO_A5_IN_STA)//�ж��Ƿ�ߵ�ƽ �ߵ�ƽ������
    {
			printf("1");
			people_num=1;		
			if(people_num!=people_num_sta)
			{
				people_num_sta=people_num;
				people++;//��⵽������++
			}
    }
		else 
		{	printf("0");
			people_num_sta=0;//��״̬���� �����´�ʹ��
		}
    adc_light = Get_Adc_Average(0, 10); //ADCʪ�Ȼ�ȡ
    if(adc_light > 4000)adc_light = 4000;
    light = (100 - (adc_light / 40));

    /***************����ɼ�***********************/
    adc_ppm = Get_Adc_Average(1, 10); //��ȡͨ��7��ADֵ��20ms��ȡһ��    2335   2730
    ppm = adc_ppm * 99 / 4096; //12λAD����ADֵת���ɰٷֱ�0~99
    ppm = ppm >= 99 ? 99 : ppm; //���ֵ���ܳ���99
    /***************����ɼ�***********************/
    /***************����ɼ�***********************/
    adc_co = Get_Adc_Average(2, 10); //��ȡͨ��7��ADֵ��20ms��ȡһ��    2335   2730
    co = adc_co * 99 / 4096; //12λAD����ADֵת���ɰٷֱ�0~99
    co = co >= 99 ? 99 : co; //���ֵ���ܳ���99
    /***************����ɼ�***********************/
    DHT11_Read_Data(&hum, &tem);
}
u8 auto_flag ;//�Զ���־λ
u8 ppm_beep, ppm_beep_sta;//�����ı�־λ �ͱ�����־λ��һ�ε�״̬
u8 co_beep, co_beep_sta;//�����ı�־λ �ͱ�����־λ��һ�ε�״̬
void ctrl_auto(void)
{
    char temp[500];
    if(auto_flag)//�Զ�ģʽ��λ
    {
        if(ppm > PPM_MAX)//�ж��Ƿ��������
        {
            BEEP = !BEEP;//����������
            ppm_beep = 1;//������־λ��λ  �����ϴ�app����
						Delay_Ms(30);
            if(ppm_beep != ppm_beep_sta)//�ж��Ƿ���Ҫ�ϴ�����
            {
                show_num = 4;//��ת��ʾ������Ϣ����Ļ
                ppm_beep_sta = ppm_beep;//��������־��¼ ��ֹһֱ�����ϴ�����
                if(SubcribePack_flag)//�����������Ž���
                {
                    sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\""identifier10"\":1},\"version\":\"1.0.0\"}");
                    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp)); //������ݣ�������������
                }
            }
        }
        else if(ppm < PPM_MAX)
        {
            BEEP = 1;//������ȡ������
            ppm_beep = 0;//������־λȡ����λ  �����ϴ�app����
            if(ppm_beep != ppm_beep_sta)//�ж��Ƿ���Ҫ�ϴ�����
            {
                show_num = 0;//��ת��ʾ������Ļ
                ppm_beep_sta = ppm_beep;//��������־��¼ ��ֹһֱ�����ϴ�����
                if(SubcribePack_flag)//�����������Ž���
                {
                    sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\""identifier10"\":0},\"version\":\"1.0.0\"}");
                    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp)); //������ݣ�������������
                }
            }
        }
        if(co > co_MAX)
        {
            BEEP = !BEEP;
						Delay_Ms(30);
            co_beep = 1;
            show_num = 4;//��ת��ʾ������Ϣ����Ļ
            if(co_beep != co_beep_sta)//�ж��Ƿ���Ҫ�ϴ�����
            {
                co_beep_sta = co_beep;//��������־��¼ ��ֹһֱ�����ϴ�����
                if(SubcribePack_flag)//�����������Ž���
                {
                    sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\""identifier11"\":1},\"version\":\"1.0.0\"}");
                    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp)); //������ݣ�������������
                }
            }
        }
        else if(co < co_MAX)
        {
            BEEP = 1;
            co_beep = 0;
            if(co_beep != co_beep_sta)//�ж��Ƿ���Ҫ�ϴ�����
            {
                show_num = 0;//��ת��ʾ������Ļ
                co_beep_sta = co_beep;
                if(SubcribePack_flag)//�����������Ž���
                {
                    sprintf(temp, "{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\""identifier11"\":0},\"version\":\"1.0.0\"}");
                    MQTT_PublishQs0(P_TOPIC_NAME, temp, strlen(temp)); //������ݣ�������������
                }
            }
        }
    }

}





