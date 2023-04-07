#include "show.h"
char show_num;//��Ļ��
char show_num_sta = 0; //��Ļ��״̬
char next_data;//��ʾ���ݵĵڶ���Ļ
unsigned char choose_show;//ѡ����ʾ����Ļ
unsigned char choose_admin;//ѡ���޸ĵ����ݵ���Ļ
/*********************************************************************************************************
* �� �� �� : void	Cut_screen()
* ����˵�� : ��Ļ����
* ��    �� : ��
* �� �� ֵ : ��
* ��    ע : 2022-11-28
*********************************************************************************************************/
void	Cut_screen(void)
{
    OLED_Refresh();//�����Դ�--����ʾ�����ݷ����ı�ʱ�����
    if(show_num != show_num_sta) ////��ֵ�����ı�--���ڼ��ֵ�Ƿ����ı�
    {
        show_num_sta = show_num; //���浱ǰֵ
        OLED_Clear();//����
    }
    if(auto_flag)
        OLED_show_str(120, 48, "A");
    else  OLED_show_str(120, 48, "W");
    switch (show_num)
    {
    case 0:
        main_sreen();//����Ļ
        set_show();//ѡ����Ļ
        break;
    case 1:
        data_show();//��ʾ�豸״̬��Ļ
        break;
    case 2:
        show_admin();//��ʾ��ֵ�޸���Ļ
        break;
    case 3:
        show_Learn_instruction();//��ʾѧϰָ����Ļ
        break;
    case 4:
        show_beep();//��ʾ������Ļ
        break;
    }
}
void  main_sreen(void)//����Ļ
{
    OLED_show_str(20, 0, "���ܼҾ�");
    OLED_show_str(16, 16, "������ʾ");
    OLED_show_str(16, 32, "��ֵ�޸�");
    OLED_show_str(16, 48, "ѧϰָ��");
}
u8 next_data_sta;
void data_show(void)
{
    if(next_data != next_data_sta) ////��ֵ�����ı�--���ڼ��ֵ�Ƿ����ı�
    {
        next_data_sta = next_data; //���浱ǰֵ
        OLED_Clear();//����
    }
    if(next_data == 0)
    {
        OLED_show_str(0, 0, "�¶�");
        OLED_ShowNum(16 * 2 + 8, 0, tem, 2, 16);

        OLED_show_str(0, 16, "ʪ��");
        OLED_ShowNum(16 * 2 + 8, 16, hum, 2, 16);

        OLED_show_str(0, 32, "����");
        OLED_ShowNum(16 * 2 + 8, 32, light, 2, 16);
        OLED_show_str(0, 48, "C  O");
        OLED_ShowNum(16 * 2 + 8, 48, co, 2, 16);
    }
    else
    {
        OLED_show_str(0, 0, "����");
        OLED_ShowNum(16 * 2 + 8, 0, ppm, 2, 16);
        OLED_show_str(0, 16, "����");
        OLED_ShowNum(16 * 2 + 8, 16, people, 2, 16);
        OLED_show_str(0, 32, "����");
        if(MotorRun_flag) OLED_show_str(16 + 16 + 16, 32, "on");
        else 							OLED_show_str(16 + 16 + 16, 32, "of");
        OLED_show_str(0, 48, "1:");
        if(IO_A7_IN_STA == 0)				OLED_show_str(16, 48, "on");
        else												OLED_show_str(16, 48, "of");
        OLED_show_str(16 + 16, 48, "2:");
        if(IO_A8_IN_STA == 0)				OLED_show_str(16 + 16 + 16, 48, "on");
        else												OLED_show_str(16 + 16 + 16, 48, "of");
        OLED_show_str(16 + 16 + 16 + 16, 48, "3:");
        if(IO_A12_IN_STA == 0)				OLED_show_str(16 + 16 + 16 + 16 + 16, 48, "on");
        else													OLED_show_str(16 + 16 + 16 + 16 + 16, 48, "of");
        OLED_show_str(16 + 16 + 16 + 16 + 16 + 16, 48, "4:");
        if(IO_A11_IN_STA == 0)				OLED_show_str(16 + 16 + 16 + 16 + 16 + 16 + 16, 48, "on");
        else													OLED_show_str(16 + 16 + 16 + 16 + 16 + 16 + 16, 48, "of");
    }
}
void show_beep(void)
{
    if(ppm_beep)
    {
        OLED_show_str(0, 0, "����");
        OLED_ShowNum(16 * 2 + 8, 0, ppm, 2, 16);
        OLED_show_str(16, 32, "ppm_h!!!");
        OLED_ShowNum(16 * 4 + 16, 48, PPM_MAX, 2, 16);
    }
    else if(co_beep)
    {
        OLED_show_str(0, 0, "C O");
        OLED_ShowNum(16 * 2 + 8, 0, co, 2, 16);
        OLED_show_str(16, 32, "co_h!!!");
        OLED_ShowNum(16 * 4 + 16, 48, co_MAX, 2, 16);
    }
}
void show_admin(void)//��ֵ��ʾ����
{
    OLED_show_str(16, 32, "��������");
    OLED_ShowNum(16 * 4 + 16, 32, PPM_MAX, 2, 16);
    OLED_show_str(16, 16, "C O ����");
    OLED_ShowNum(16 * 4 + 16, 16, co_MAX, 2, 16);
}

void show_Learn_instruction(void)//ѧϰָ����ʾ����
{
    if(next_data != next_data_sta) ////��ֵ�����ı�--���ڼ��ֵ�Ƿ����ı�
    {
        next_data_sta = next_data; //���浱ǰֵ
        OLED_Clear();//����
    }
    if(next_data == 0)
    {
        OLED_show_str(0, 0, "���յ�1");
        if(Learn_on_ok1) OLED_show_str(16 * 4, 0, "��ѧϰ");
        else OLED_show_str(16 * 4, 0, "δѧϰ");
        OLED_show_str(0, 16, "�ؿյ�1");
        if(Learn_off_ok1) OLED_show_str(16 * 4, 16, "��ѧϰ");
        else OLED_show_str(16 * 4, 16, "δѧϰ");

        OLED_show_str(0, 32, "������");
        if(Learn_on_ok2) OLED_show_str(16 * 4, 32, "��ѧϰ");
        else OLED_show_str(16 * 4, 32, "δѧϰ");
        OLED_show_str(0, 48, "�ص���");
        if(Learn_off_ok2) OLED_show_str(16 * 4, 48, "��ѧϰ");
        else OLED_show_str(16 * 4, 48, "δѧϰ");
    }
    else
    {
        OLED_show_str(0, 0, "���յ�2");
        if(Learn_on_ok3) OLED_show_str(16 * 4, 0, "��ѧϰ");
        else OLED_show_str(16 * 4, 0, "δѧϰ");
        OLED_show_str(0, 16, "�ؿյ�2");
        if(Learn_off_ok3) OLED_show_str(16 * 4, 16, "��ѧϰ");
        else OLED_show_str(16 * 4, 16, "δѧϰ");

        OLED_show_str(0, 32, "������2");
        if(Learn_on_ok4) OLED_show_str(16 * 4, 32, "��ѧϰ");
        else OLED_show_str(16 * 4, 32, "δѧϰ");
        OLED_show_str(0, 48, "�ص���2");
        if(Learn_off_ok4) OLED_show_str(16 * 4, 48, "��ѧϰ");
        else OLED_show_str(16 * 4, 48, "δѧϰ");
    }

}
void set_show(void) //ѡ����Ļ
{
    switch (choose_show)
    {
    case 0:
        OLED_ShowString (0, 16, "->", 16);
        OLED_ShowString (0, 32, "  ", 16);
        OLED_ShowString (0, 48, "  ", 16);
        break;
    case 1:
        OLED_ShowString (0, 16, "  ", 16);
        OLED_ShowString (0, 32, "->", 16);
        OLED_ShowString (0, 48, "  ", 16);
        break;
    case 2:
        if(show_num == 0)
        {
            OLED_ShowString (0, 16, "  ", 16);
            OLED_ShowString (0, 32, "  ", 16);
            OLED_ShowString (0, 48, "->", 16);
        }
        if(show_num == 2)
        {
            OLED_ShowString (0, 16, "  ", 16);
            OLED_ShowString (0, 32, "  ", 16);
            OLED_ShowString (0, 48, "  ", 16);
        }
        break;
    }
}





