#include "dac7512.h"

DAC7512_INTERFACE Dac7512 = 
{
    IO_MO,
    IO_SCK,
    RDO_CS1,
    Dac7512_Output
};

/*
    DAC7512 output voltage
    data Range: 0~4095
*/
void Dac7512_Output(uint16_t data)
{
    uint8_t i;
    uint16_t tmp = 0;

    Dac7512.SCK(HIGH);
    Dac7512.CS(LOW);

    tmp = (DAC_MODE | (data&0x0fff));
    for(i = 0; i < 16; i ++)
    {
        Dac7512.SCK(HIGH);

        if(tmp & 0x8000)
            Dac7512.MO(HIGH);
        else
            Dac7512.MO(LOW);
        tmp <<= 1;
        Dac7512.SCK(LOW);
    }

    Dac7512.SCK(HIGH);  //Set high when idle
    Dac7512.CS(HIGH);
}

