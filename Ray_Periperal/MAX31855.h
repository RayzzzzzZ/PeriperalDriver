#ifndef __MAX31855_H
#define __MAX31855_H


#include <stdint.h>

typedef struct
{
    uint32_t OC:1;      //Open Circuit
    uint32_t SCG:1;     //Short to GND
    uint32_t SCV:1;     //Short to Vcc
    uint32_t Res_D3:1;
    uint32_t In_Dat:11;
    uint32_t In_Sigh:1; //Internal
    uint32_t Fault:1;   //Fault flag
    uint32_t Res_D17:1;
    uint32_t RDO_Dat:13;//Thermocouple
    uint32_t RDO_Sigh:1;
}MAX_DAT_STRUCT;

typedef struct
{
    //Hw bsp
    uint8_t (*SO)(void);
    void (*SCK)(uint8_t level);
    void (*CS)(uint8_t level);
    void (*delay)(uint8_t time);//50ns
    //For user
    bool (*Read_Data)(int16_t *tc_temp, int16_t *in_temp);
}MAX31855_INTERFACE;

extern MAX31855_INTERFACE Max31855;

bool Max_Read_Data(int16_t *tc_temp, int16_t *in_temp);

#endif

