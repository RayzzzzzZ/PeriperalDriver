#ifndef __DAC7512_H
#define __DAC7512_H

#include <stdint.h>


#define NORMAL_OPERATION        (0x0000)
#define OUTPUT_1K               (0x1000)
#define OUTPUT_10K              (0x2000)
#define HIGH_Z                  (0x3000)

#define DAC_MODE                (NORMAL_OPERATION)

typedef struct
{
    //Hw bsp
    void (*MO)(uint8_t level);
    void (*SCK)(uint8_t level);
    void (*CS)(uint8_t level);
    //For user
    void (*SendData)(uint16_t data);
}DAC7512_INTERFACE;

extern DAC7512_INTERFACE Dac7512;



void Dac7512_Output(uint16_t data);

#endif

