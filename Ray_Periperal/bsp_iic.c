#include "bsp_iic.h"

static uint8_t iic_speed = 1;

/*
    IIC IO Init
*/
void Bsp_IOIIC_Init(void)
{
    GPIO_Init(SCL_PORT, SCL_PIN, GPIO_Mode_Out_OD_Hiz_Fast);        //IIC CLK
    GPIO_Init(SDA_PORT, SDA_PIN, GPIO_Mode_Out_OD_Hiz_Fast);        //IIC DATA
}

/*
    IIC Set Speed
*/
void IIC_SetSpeed(uint8_t t)
{
    iic_speed = t;
}

/*
    IIC Start
*/
void IIC_Start(void)
{
    SDA_H;
    SCL_L;
    IIC_DELAY_US(iic_speed);

    SDA_L;
    IIC_DELAY_US(iic_speed);
    SCL_L;
}

/*
    IIC Stop
*/
void IIC_Stop(void)
{
    SDA_L;
    SCL_L;
    IIC_DELAY_US(iic_speed);

    SCL_H;
    SDA_H;
    IIC_DELAY_US(iic_speed);
}

/*
    IIC Wait ack
*/
bool IIC_WaitAck(uint16_t timeOut)
{
    SDA_H;IIC_DELAY_US(iic_speed);
    SCL_H;IIC_DELAY_US(iic_speed);

    while(SDA_IN)
    {
        if(!(--timeOut))
        {
            IIC_Stop();
            return FALSE;
        }
    }

    SCL_L;

    return TRUE;
}

/*
    IIC Nack
*/
void IIC_Nack(void)
{
    SCL_L;
    SDA_H;
    IIC_DELAY_US(iic_speed);
    SCL_H;
    IIC_DELAY_US(iic_speed);
    SCL_L;
}

/*
    IIC SendByte
*/
void IIC_SendByte(uint8_t byte)
{
    unsigned char count = 0;

    SCL_L;
    for(; count < 8; count ++)
    {
        if(byte & 0x80)
            SDA_H;
        else
            SDA_L;
        byte <<= 1;

        IIC_DELAY_US(iic_speed);
        SCL_H;
        IIC_DELAY_US(iic_speed);
        SCL_L;
    }
}

/*
    IIC Read byte
*/
uint8_t IIC_RecvByte(void)
{
    uint8_t count = 0, receive = 0;

    SDA_H;

    for(; count < 8; count ++)
    {
        SCL_L;
        IIC_DELAY_US(iic_speed);
        SCL_H;

        receive <<= 1;

        if(SDA_IN)
            receive ++;
        
        IIC_DELAY_US(iic_speed);
    }

    return receive;
}

/*
    I2C Write a byte
*/
vool I2C_WriteByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t *byte)
{
    uint8_t addr = 0;

    addr = slaveAddr;

    IIC_Start();

    IIC_SendByte(addr);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;
    
    IIC_SendByte(regAddr);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;
    
    if(byte)
    {
        IIC_SendByte(*byte);
        if(IIC_WaitAck(5000) == FALSE)
            return FALSE;
    }

    IIC_Stop();

    return TRUE;
}

/*
    I2C Read a byte
*/
bool I2C_ReadByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t *val)
{
    uint8_t addr = 0;

    addr = slaveAddr;

    IIC_Start();

    IIC_SendByte(addr);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;
    
    IIC_SendByte(regAddr);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;

    IIC_Start();

    IIC_SendByte(addr + 1);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;
    
    *val = IIC_RecvByte();
    IIC_Nack();

    IIC_Stop();

    return FALSE;
}

bool I2C_WriteByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t *buf, uint8_t num)
{
    uint8_t addr = 0;

    addr = slaveAddr;

    IIC_Start();

    IIC_SendByte(addr);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;

    IIC_SendByte(regAddr);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;

    while(num--)
    {
        IIC_SendByte(*buf);
        if(IIC_WaitAck(5000) == FALSE)
            return FALSE;
        buf ++;
        IIC_DELAY_US(10);
    }

    IIC_Stop();

    return TRUE;
}

/*
    I2C Read some bytes
*/
bool I2C_ReadNByte(uint8_t slaveAddr, uint8_t *buf, uint8_t num)
{
    uint8_t addr = 0;

    addr = slaveAddr;

    IIC_Start();

    IIC_SendByte(addr);
    if(IIC_WaitAck(5000) == FALSE)
        return FALSE;

    while(num --)
    {
        *buf = IIC_RecvByte();
        buf ++;

        if(num == 0)
        {
            IIC_Nack();
        }
        else
        {
            IIC_Ack();
        }
    }

    IIC_Stop();

    return TRUE;
}

