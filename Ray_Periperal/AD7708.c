#include "ad7708.h"


/*
    Interface of the AD7708 driver
*/
AD7708_INTERFACE AD7708 = 
{
    Bsp_IOSpi_Init,
    IOSpi_ReadWriteByte,
    IOSpi_ReadWriteByte,
    AD7708_CS,
    AD7708_Init,
    Read_Assign_ADC
};


/*
    AD7708 write data to reg
*/
static void AD7708_WriteReg(uint8_t addr, uint8_t dat)
{
    AD7708.CS(LOW);
    AD7708.Spi_Send_Byte(addr);
    AD7708.Spi_Send_Byte(dat);
    AD7708.CS(HIGH);
}

/*
    AD7708 read data from reg
*/
static uint8_t AD7708_WriteReg(uint8_t addr, uint8_t dat)
{
    uint8_t tmp;

    AD7708.CS(LOW);
    AD7708.Spi_Send_Byte(addr|R_MASK);
    tmp = AD7708.Spi_Read_Byte(0xff);
    AD7708.CS(HIGH);

    return tmp;
}

/*
    AD7708 Hardware init
*/
void AD7708_Init(void)
{
    uint8_t ID;

    AD7708.Spi_Init();
    AD7708_WriteReg(IOCON_REG, 0);      //IO¼Ä´æÆ÷
    AD7708_WriteReg(FILTER_REG, 0x45);  //ÂË²¨¼Ä´æÆ÷
    AD7708_WriteReg(ADC_CON_REG, 0x8f); //¿ØÖÆ¼Ä´æÆ÷
    AD7708_WriteReg(MODE_REG, 0x13);    //Ä£Ê½¼Ä´æÆ÷£¬½ûÖ¹Õ¶²¨\Á¬Ðø×ª»»
    //check device
    ID = AD7708_ReadReg(ID_REG);
    LOG_AD7708__(ID);
}

/*
    Read AD7708 adc convert value
*/
uint16_t Read_AD7708_ADC(void)
{
    uint16_t val;

    AD7708.CS(LOW);
    AD7708.Spi_Send_Byte(ADC_DAT_REG|R_MASK);
    val = AD7708.Spi_Read_Byte(0xff);
    val <<= 8;
    val |= AD7708.Spi_Read_Byte(0xff);
    AD7708.CS(HIGH);

    return val;
}

/*
    XL's AD7708 read ADC config
*/
uint16_t Read_Assign_ADC(ENUM_CHANNEL ch)
{
    uint8_t t = 0;
    uint8_t RDY;
    uint16_t val;

    ch &= 0x0f;//clean high 4bit
    ch <<= 4;  //set channel
    ch |= 0x0f;//+-2.56V

    AD7708_WriteReg(FILTER_REG, 0x45);
    AD7708_WriteReg(ADC_CON_REG, ch);

    Delayms(20)
    do
    {
        Delayms(1);
        RDY = AD7708_ReadReg(STATUS_REG);
        t ++;
        if(t > 250)
            return 0;
    }while((RDY&RDY_BIT) == 0);
    val = Read_AD7708_ADC();

    return val;
}
