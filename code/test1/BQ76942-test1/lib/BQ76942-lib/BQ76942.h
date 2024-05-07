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

// subcommands
#define subcommand_lower 0x3E
#define subcommand_upper 0x3F
#define subcommand_buffer 0x40


public:
// Temperature measurement
#define Internal_Temperature 0x68
#define CFETOFF_Temperature 0x6A
#define DFETOFF_Temperature 0x6C
#define ALERT_Temperature 0x6E
#define TS1_Temperature 0x70
#define TS2_Temperature 0x72
#define TS3_Temperature 0x74
#define HDQ_Temperature 0x76
#define DCHG_Temperature 0x78
#define DDSG_Temperature 0x7A

    BQ76942(byte address = 0x10); // default as 0x10 (write), 0x11 (read)

    // begin the Wire with default settings: I2C_SCL = GPIO22, I2C_SDA = GPIO21
    void begin();
    // begin the Wire using SDA, SCL and frequency
    void begin(int SDA, int SCL, int frequency);

    uint16_t getCellVoltage(byte cellNr);

    // inefficient method to read and validate subcommand buffer, 32Byte array buffer
    byte getSubCommandBuffer(byte scl, byte scu, byte *buffer);

    uint16_t getTemperature(byte temperatureName);
};

#endif