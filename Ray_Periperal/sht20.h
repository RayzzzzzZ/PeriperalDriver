#ifndef __SHT20_H
#define __SHT20_H

#include <stdint.h>

#define SHT20_ADDRESS               0x80
#define SHT20_Measurement_RH_HM     0xe5
#define SHT20_Measurement_T_HM      0xe3
//#define SHT20_Measurement_RH_NHM    0xf5
//#define SHT20_Measurement_T_NHM     0xf3
//#define SHT20_READ_REG              0xe7
//#define SHT20_WRITE_REG             0xe6
//#define SHT20_SHOFT_RESET           0xfe
#define RE_MASK                     0x01
#define WR_MASK                     0x00

typedef struct
{
    //Hardware interface
    void (*i2c_start)(void);
    void (*i2c_stop)(void);
    void (*i2c_waitAck)(uint16_t);
    void (*i2c_ack)(void);
    void (*i2c_nack)(void);
    void (*i2c_sendByte)(uint8_t);
    uint8_t (*i2c_recvByte)(void);
    void (*delayms)(uint16_t);

    //For user
    bool (*Get_14BitTemperature)(uint16_t *);
    bool (*Get_12BitHumidity)(uint16_t *);
}SHT20_INTERFACE;

extern SHT20_INTERFACE Sht20;

//º¯ÊýÉùÃ÷
bool Get_Sht20_Temperature( uint16_t *pMeasurand);
bool Get_Sht20_Humidity( uint16_t *pMeasurand);

#endif

