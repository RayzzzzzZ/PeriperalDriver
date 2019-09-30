#ifndef __74HC595_H
#define __74HC595_H 

#include <stdint.h>

//DS
#define HC595_DAT_PORT          (GPIOF)
#define HC595_DAT_PIN           (GPIO_Pin_0)
#define HC595_DAT_HIGH()        GPIO_SetBits(HC595_DAT_PORT, HC595_DAT_PIN)
#define HC595_DAT_LOW()         GPIO_ResetBits(HC595_DAT_PORT, HC595_DAT_PIN)
//SH_CP
#define HC595_SCK_PORT          (GPIOD)
#define HC595_SCK_PIN           (GPIO_Pin_6)
#define HC595_SCK_HIGH()        GPIO_SetBits(HC595_SCK_PORT, HC595_SCK_PIN)
#define HC595_SCK_LOW()         GPIO_ResetBits(HC595_SCK_PORT, HC595_SCK_PIN)
//ST_CP
#define HC595_RCK_PORT          (GPIOD)
#define HC595_RCK_PIN           (GPIO_Pin_5)
#define HC595_RCK_HIGH()        GPIO_SetBits(HC595_RCK_PORT, HC595_RCK_PIN)
#define HC595_RCK_LOW()         GPIO_ResetBits(HC595_RCK_PORT, HC595_RCK_PIN)
//OE
#define HC595_EN_PORT          (GPIOD)
#define HC595_EN_PIN           (GPIO_Pin_4)
#define HC595_EN_HIGH()        GPIO_SetBits(HC595_EN_PORT, HC595_EN_PIN)
#define HC595_EN_LOW()         GPIO_ResetBits(HC595_EN_PORT, HC595_EN_PIN)

typedef struct
{
    //hw bsp
    void (*DAT)(uint8_t level);
    void (*SCK)(uint8_t level);
    void (*RCK)(uint8_t level);
    //For user
    void (*Write)(uint8_t dat);
}HC595_INTERFACE;

extern HC595_INTERFACE HC595;


void Bsp_74HC595_IO_Init(void);
void HC595_DAT(uint8_t level);
void HC595_SCK(uint8_t level);
void HC595_RCK(uint8_t level);
void Write_HC595(uint8_t dat);

#endif
