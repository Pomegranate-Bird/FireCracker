#include "SparkFun_BMV080_Arduino_Library.h" // CTRL+Click here to get the library: http://librarymanager/All#SparkFun_BMV080
#include <Wire.h>

SparkFunBMV080 bmv080; // Create an instance of the BMV080 class
#define BMV080_ADDR 0x57  // SparkFun BMV080 Breakout defaults to 0x57

// Some Dev boards have their QWIIC connector on Wire or Wire1
// This #ifdef will help this sketch work across more products

#ifdef ARDUINO_SPARKFUN_THINGPLUS_RP2040
#define wirePort Wire1
#else
#define wirePort Wire
#endif

void initializePM25()
{
    
    // while (!Serial)
    //   delay(10); // Wait for Serial to become available.
    // // // Necessary for boards with native USB (like the SAMD51 Thing+).
    // // // For a final version of a project that does not need serial debug (or a USB cable plugged in),
    // // // Comment out this while loop, or it will prevent the remaining code from running.

    // Serial.println();
    // Serial.println("BMV080 Example 1 - Basic Readings");

    wirePort.begin();

    if (bmv080.begin(BMV080_ADDR, wirePort) == false)
    {
        Serial.println(
            "BMV080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
        while (1)
            ;
    }
    // Serial.println("BMV080 found!");

    // wirePort.setClock(400000); //Increase I2C data rate to 400kHz

    /* Initialize the Sensor (read driver, open, reset, id etc.)*/
    bmv080.init();

    /* Set the sensor mode to continuous mode */
    if (bmv080.setMode(SF_BMV080_MODE_CONTINUOUS) == true)
    {
        // Serial.println("BMV080 set to continuous mode");
    }
    // else
    // {
    //     Serial.println("Error setting BMV080 mode");
    // }
}

void gather_pm25_data()
{
    if (bmv080.readSensor())
    {
      air_quality_reading = bmv080.PM25();
    }
}