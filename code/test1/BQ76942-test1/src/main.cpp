#include <Arduino.h>
#include <BQ76942.h>

BQ76942 battery1; // create a BQ76942 object with the default I2C address

void setup()
{
    Serial.begin(115200); //setup the serial monitor with 115200 Baud

    battery1.begin(); // initialise the I2C communication
}

void loop()
{
    Serial.println("Voltages: ");
    for (byte i = 1; i <= 10; i++) // loop through every cell Number
    {
        Serial.print("Cell Nr."); Serial.print(i); Serial.print(": ");
        Serial.print(battery1.getCellVoltage(i)); // print the read cell voltages to the Serial Monitor
    }

    Serial.println(battery1.getTemperature(Internal_Temperature));
    
    delay(5000); // wait 5s
}
