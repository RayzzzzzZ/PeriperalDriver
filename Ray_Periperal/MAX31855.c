#include "Max31855.h"

MAX31855_INTERFACE Max31855 = 
{
    IO_SO,
    IO_SCK,
    RDO_CS1,
    delay_nop,
    Max_Read_Data
};

/*
    Max31855 read 32bit data
    short: -32768----32767
*/

MAX_DAT_STRUCT *pMax;
uint32_t ICdata;
bool Max_Read_Data(int16_t *tc_temp, int16_t *in_temp)
{
    int8_t i;
    ICdata = 0;         //Must clear

    Max31855.SCK(LOW);  //Set low first

    Max31855.CS(LOW);   //Select
    Max31855.delay(2);
    for( i = 31; i >= 0; i --)
    {
        Max31855.SCK(HIGH);
        Max31855.delay(2);
        if(Max31855.SO())
            ICdata |= ((uint32_t)1 << i);
        Max31855.SCK(LOW);
        Max31855.delay(2);
    }
    Max31855.CS(HIGH);

    Max31855.SCK(HIGH);  //Set high when idle

    //��ȡMAX31855����
    pMax = (MAX_DAT_STRUCT *)(&ICdata);
    if(pMax->Fault == 1) //����λ
        return FALSE;
    
    /* ϵ��ת����ֵ */
    //�ȵ�ż
    if(pMax->RDO_Sigh == 0)//��
    {
        *tc_temp = (int16_t)((pMax->RDO_Dat) * 2.5);    //�Ŵ�10������ȡһλС����ԭʼϵ��0.25
    }
    else
    {
        *tc_temp = (int16_t)(( (~(pMax->RDO_Dat-1)) & ((uint32_t)0x00001fff)) * 2.5);
        *tc_temp = 0 - *tc_temp;
    }
    //�ڲ��¶ȣ�����ʹ�ã�����������ѡ�Ƿ��ȡ
    if(in_temp != NULL)
    {
        if(pMax->In_Sigh == 0)
        {
            *in_temp = (int16_t)((pMax->In_Dat)*6.25);//�Ŵ�100����ԭʼϵ��0.0625
        }
        else
        {
            *in_temp = (int16_t)(( (~(pMax->In_Dat-1)) & ((uint32_t)0x000007ff)) * 6.25);
            *in_temp = 0 - *in_temp;
        }
    }

    return TRUE;
}

