#ifndef __BSP_IIC_H
#define __BSP_IIC_H


#include <stdint.h>

#define SCL_PORT    GPIOE
#define SCL_PIN     GPIO_Pin_3

#define SDA_PORT    GPIOB
#define SDA_PIN     GPIO_Pin_1

//SDA PIN
#define SDA_H       GPIO_SetBits( SDA_PORT, SDA_PIN)
#define SDA_L       GPIO_ResetBits( SDA_PORT, SDA_PIN)
#define SDA_IN      GPIO_ReadInputDataBit( SDA_PORT, SDA_PIN)
#define SDA_AS_OUT  GPIO_Init( SDA_PORT, SDA_PIN, GPIO_Mode_Out_OD_Hiz_Fast)
#define SDA_AS_IN   GPIO_Init( SDA_PORT, SDA_PIN, GPIO_Mode_Out_In_FL_No_IT)
//SCL PIN
#define SCL_H       GPIO_SetBits( SCL_PORT, SCL_PIN)
#define SCL_L       GPIO_ResetBits( SCL_PORT, SCL_PIN)
//Delay us
#define IIC_DELAY_US(X)     DelayNus(X)

//函数声明
void Bsp_IOIIC_Init(void);
void IIC_SetSpeed(uint8_t t);
//通信基础函数
void IIC_Start(void);
void IIC_Stop(void);
bool IIC_WaitAck(uint16_t timeout);
void IIC_Ack(void);
void IIC_Nack(void);
void IIC_SendByte(uint8_t byte);
uint8_t IIC_RecvByte(void);
bool I2C_WriteByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t *byte);
bool I2C_ReadByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t *val);
bool I2C_WriteNByte(uint8_t slaveAddr, uint8_t regAddr, uint8_t *buf, uint8_t num);
bool I2C_ReadNByte(uint8_t slaveAddr, uint8_t *buf, uint8_t num);

#endif
