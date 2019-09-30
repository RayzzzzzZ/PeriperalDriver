#ifndef __AD7708_H
#define __AD7708_H

#include <stdint.h>

#define LOG_AD7708__(var)   if((var&0xf0) == 0x50){\
                                LOG__("AD7708 Init:OK\r\n");\
                            }\
                            else{\
                                LOG__("AD7708 Init:Error"\r\n);\
                            }

#define COMMUNICATE_REG     (0x00)
#define STATUS_REG          (0x00)
#define MODE_REG            (0x01)
#define ADC_CON_REG         (0x02)
#define FILTER_REG          (0x03)
#define ADC_DAT_REG         (0x04)
#define ADC_OFFS_REG        (0x05)
#define ADC_GAIN_REG        (0x06)
#define IOCON_REG           (0x07)
#define TEXT1_REG           (0x0c)
#define TEXT2_REG           (0x0d)
#define ID_REG              (0x0f)
#define R_MASK              (0x40)
#define RDY_BIT             (0x80)

/*
    In CHCON is 1.
*/
typedef enum
{
    SINGLE_1 = 0,
    SINGLE_2,
    SINGLE_3,
    SINGLE_4,
    SINGLE_5,
    SINGLE_6,
    SINGLE_7,
    SINGLE_8,
    DIFF_12,
    DIFF_34,
    DIFF_56,
    DIFF_78,
    DIFF_910,
    DIFF_COM,
    SINGLE_9,
    SINGLE_10
}ENUM_CHANNEL;

/*
    AD7708 SPI Hardware Interface
*/
typedef struct
{
    //Spi hw bsp
    void (*Spi_Init)(void);
    uint8_t (*Spi_Send_Byte)(uint8_t dat);
    uint8_t (*Spi_Read_Byte)(uint8_t dat);
    void (*CS)(uint8_t level);
    //For user
    void (*Init)(void);
    uint16_t (*Assign_ADC)(ENUM_CHANNEL ch);
}AD7708_INTERFACE;

extern AD7708_INTERFACE AD7708;

void AD7708_Init(void);
void AD7708_WriteReg(uint8_t addr, uint8_t dat);
uint8_t AD7708_ReadReg(uint8_t addr);
uint16_t Read_Assign_ADC(ENUM_CHANNEL ch);

#endif
