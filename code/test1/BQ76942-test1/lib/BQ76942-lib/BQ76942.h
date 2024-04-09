#ifndef BQ76942_lib
#define BQ76924_lib

#include <Arduino.h>

class BQ76942
{
private:
//cell voltage register measured in mV 16 Bit
#define cell1Voltage 0x14
#define cell2Voltage 0x16
#define cell3Voltage 0x18
#define cell4Voltage 0x1A
#define cell5Voltage 0x1C
#define cell6Voltage 0x1E
#define cell7Voltage 0x20
#define cell8Voltage 0x22
#define cell9Voltage 0x24
#define cell10Voltage 0x26

//stack, pack and LD pin Voltages in userV 16 Bit
#define stackCV10Voltage 0x34
#define packPinVoltage 0x36
#define LDPinVoltage 0x38

public:
    BQ76942();
};

#endif