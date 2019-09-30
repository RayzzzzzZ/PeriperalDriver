#include "74hc595.h"

HC595_INTERFACE HC595 = 
{
    HC595_DAT,
    HC595_SCK,
    HC595_RCK,
    Write_HC595;
};

void Write_HC595(uint8_t dat)
{
    uint8_t i;

    HC595.SCK(0);

    for( i = 0; i < 8; i ++)
    {
        if( dat&0x80)
        {
            HC595.DAT(1);
        }
        else
        {
            HC595.DAT(0);
        }

        HC595.SCK(1);
        HC595.SCK(0);
        dat = dat << 1;
    }

    HC595.RCK(0);
    HC595.RCK(1);
    HC595.RCK(0);
}

/*
    Bsp IO
*/
void Bsp_74HC595_IO_Init(void)
{
    GPIO_Init(HC595_DAT_PORT, HC595_DAT_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(HC595_SCK_PORT, HC595_SCK_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(HC595_RCK_PORT, HC595_RCK_PIN, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_Init(HC595_EN_PORT, HC595_EN_PIN, GPIO_Mode_Out_PP_Low_Fast);
}

void HC595_DAT(uint8_t level)
{
    if(level == LOW)
        HC595_DAT_LOW();
    else
        HC595_DAT_HIGH();
}

void HC595_SCK(uint8_t level)
{
    if(level == LOW)
        HC595_SCK_LOW();
    else
        HC595_SCK_HIGH();
}

void HC595_RCK(uint8_t level)
{
    if(level == LOW)
        HC595_RCK_LOW();
    else
        HC595_RCK_HIGH();
}

