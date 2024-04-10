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

//------------------------------------------------------------------------------General Functions------------------------------------------------------------------------------------------------------------
uint16_t BQ76942::get16BitRegister(byte registerNr)
{
    uint16_t output;

    Wire.beginTransmission(this->address); // write to Address
    Wire.write(0b000010000);  // reading data to I2C device address
    Wire.write(registerNr);   // register address
    Wire.endTransmission();   // end Transmission I2C

    Wire.requestFrom(registerNr, 2); // requesting two bytes from the I2C address
    if (Wire.available() >= 2)
    {
        output = (Wire.read() << 8 | Wire.read()) >> 4;
    }

    return output;
}

//------------------------------------------------------------------------------read Cells------------------------------------------------------------------------------------------------------------
//reads the cells at index 1 - 10 returns a 16 Bit int
uint16_t BQ76942::getCellVoltage(byte cellNr)
{
    get16BitRegister(cellToRegisterMap[cellNr-1]);
}