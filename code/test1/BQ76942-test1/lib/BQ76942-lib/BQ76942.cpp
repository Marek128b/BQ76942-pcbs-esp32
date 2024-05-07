#include <Arduino.h>
#include <Wire.h>
#include "BQ76942.h"

BQ76942::BQ76942(byte address)
{
    this->address = address;
}
//------------------------------------------------------------------------------Begin------------------------------------------------------------------------------------------------------------
void BQ76942::begin()
{
    Wire.begin();
}

void BQ76942::begin(int SDA, int SCL, int frequency)
{
    Wire.begin(SDA, SCL, frequency);
}

//------------------------------------------------------------------------------General Functions-----------------------------------------------------------------------------------------------------
uint16_t BQ76942::get16BitRegister(byte registerNr)
{
    uint16_t output;

    Wire.beginTransmission(this->address); // write to Address
    Wire.write(0x11);                      // reading data to I2C device address
    Wire.write(registerNr);                // register address
    Wire.endTransmission();                // end Transmission I2C

    Wire.requestFrom(registerNr, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = (Wire.read() << 8 | Wire.read()) >> 4;
    }

    return output;
}

//------------------------------------------------------------------------------read Cells------------------------------------------------------------------------------------------------------------
// reads the cells at index 1 - 10 returns a 16 Bit int
uint16_t BQ76942::getCellVoltage(byte cellNr)
{
    get16BitRegister(cellToRegisterMap[cellNr - 1]);
}

//------------------------------------------------------------------------------read sub command buffer-----------------------------------------------------------------------------------------------
// inefficient method to read and validate subcommand buffer, 32Byte array buffer, returns buffer status
byte BQ76942::getSubCommandBuffer(byte scl, byte scu, byte *buffer)
{
    // TODO Method
    Wire.beginTransmission(this->address); // write to Address
    Wire.write(0x11);                      // writing data to I2C device address ??
    Wire.write(subcommand_lower);          // register address 1
    Wire.write(scl);                       // write lower subcommand
    Wire.write(subcommand_upper);          // register address 2
    Wire.write(scu);                       // write upper subcommand
    Wire.endTransmission();                // end Transmission I2C

    Wire.requestFrom(subcommand_buffer, 34); // requesting 32 + 2 bytes from the I2C address

    if (Wire.available() >= 1)
    {
        Wire.readBytes(buffer, 34); // TODO checksum and length
        return 1;
    }

    return 0;
}

uint16_t BQ76942::getTemperature(byte temperatureName){
    uint16_t output;
    Wire.beginTransmission(this->address);
    Wire.write(0x11);
    Wire.write(temperatureName);
    Wire.endTransmission();                // end Transmission I2C

    Wire.requestFrom(temperatureName, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = (Wire.read() << 8 | Wire.read()) >> 4;
    }

    return output;
}