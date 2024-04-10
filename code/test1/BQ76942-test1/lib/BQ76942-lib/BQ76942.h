#ifndef BQ76942_lib
#define BQ76924_lib

#include <Arduino.h>

class BQ76942
{
private:
    byte address; // 7Bit I2C Slave address
    uint16_t get16BitRegister(byte registerNr);

// cell voltage register measured in mV 16 Bit
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

    byte cellToRegisterMap[10] = {cell1Voltage, cell2Voltage, cell3Voltage, cell4Voltage, cell5Voltage, cell6Voltage, cell7Voltage, cell8Voltage, cell9Voltage, cell10Voltage};

// stack, pack and LD pin Voltages in userV 16 Bit
#define stackCV10Voltage 0x34
#define packPinVoltage 0x36
#define LDPinVoltage 0x38

public:
    BQ76942(byte address = 0b0000000); // TODO set the right address for the chip

    // begin the Wire with default settings: I2C_SCL = GPIO22, I2C_SDA = GPIO21
    void begin();
    // begin the Wire using SDA, SCL and frequency
    void begin(int SDA, int SCL, int frequency);

    uint16_t getCellVoltage(byte cellNr);
};

#endif