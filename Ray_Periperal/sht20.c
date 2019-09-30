#include "Sht20.h"

SHT20_INTERFACE Sht20 = 
{
    IIC_Start,
    IIC_Stop,
    IIC_Ack,
    IIC_Nack,
    IIC_SendByte,
    IIC_RecvByte,
    Delayms,
    Get_Sht20_Temperature,
    Get_Sht20_Humidity
};


/*
    Crc8 for sht20
*/
#define POLYNOMIAL      (0x131)
static bool SHT2X_CheckCrc(uint8_t data[], uint8_t nbrOfBytes, uint8_t checksum)
{
    uint8_t crc = 0;
    uint8_t bit = 0;
    uint8_t byteCtr = 0;

    //calculates 8-bit checksum with given polynomial
    for(byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
    {
        crc ^= (data[byteCtr]);
        for( bit = 8; bit > 0; --bit)
        {
            if(crc & 0x80) crc = (crc<<1)^POLYNOMIAL;
            else crc = (crc << 1);
        }
    }

    if(crc != checksum)
        return FALSE;
    else
        return TRUE;
}

/*
    Sht20 Measure hold time
*/
static bool SHT20_MeasureHM( uint8_t cmd, uint8_t time, uint16_t *pMeasurand)
{
    uint8_r check_sum = 0;
    uint8_t data[2];

    Sht20.i2c_start();
    Sht20.i2c_sendByte( SHT20_ADDRESS|WR_MASK);
    if( Sht20.i2c_waitAck(60000) == FALSE)          //wait ack
        return FALSE;

    Sht20.i2c_sendByte( cmd);
    if( Sht20.i2c_waitAck(60000) == FALSE)          //wait ack
        return FALSE;

    Sht20.i2c_start();
    Sht20.i2c_sendByte( SHT20_ADDRESS|RE_MASK);
    if( Sht20.i2c_waitAck(60000) == FALSE)          //wait ack
        return FALSE;

    Sht20.delayms(time);    //Sensor change time
    data[0] = Sht20.i2c_recvByte();
    Sht20.i2c_ack();
    data[1] = Sht20.i2c_recvByte();
    Sht20.i2c_ack();
    check_sum = Sht20.i2c_recvByte();
    Sht20.i2c_nack();
    Sht20.i2c_stop();

    if( SHT2X_CheckCrc( data, 2, check_sum) == FALSE)
    {
        return FALSE;
    }

    *pMeasurand = ((uint16_t)data[0]<<8) + data[1];

    return TRUE;
}

/*
    Get Sht20 temperature
    return T*10
*/
bool Get_Sht20_Temperature( uint16_t *pMeasurand)
{
    bool err;
    uint16_t temp;
    float ftemp;

    err = SHT20_MeasureHM( SHT20_Measurement_T_HM, 100, &temp);

    temp &= ~0x0003;
    ftemp = -46.85 + 175.72 / 65536 * (float)temp;  //Temperature Conversion
    *pMeasurand = (uint16_t)(ftemp*10);

    return err;
}

/*
    Get Sht20 humidity
    return RH*10
*/
bool Get_Sht20_Humidity( uint16_t *pMeasurand)
{
    bool err;
    uint16_t temp;
    float ftemp;

    err = SHT20_MeasureHM( SHT20_Measurement_RH_HM, 50, &hum);

    hum &= ~0x0003;
    fhum = -6 + ((float)hum/65536)*125; //Humidity Conversion
    *pMeasurand = (uint16_t)(fhum*10);

    return err;
}

