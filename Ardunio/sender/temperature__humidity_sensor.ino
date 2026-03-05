/*************************************************** 
  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/
 
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#define dev true // Usefule for non-ESP32-Wroom32e boards wihout dedicated I2C ports

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void initialize_temp_sensor() {

  if(dev)
    Wire.begin(8,9); // SDA, SCL

  while (!Serial)
    delay(10);     // will pause Zerountil serial console opens

  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
}


void gather_temp() {
    //Temperature is in celcius 
    temp = sht31.readTemperature();
    hum = sht31.readHumidity();

  // // isnan == is not a number 
  // if (! isnan(temp)) {  // check if 'is not a number' 
  //   Serial.print("Temp *C = "); Serial.print(temp); Serial.print("\t\t");
  // } else { 
  //   Serial.println("Failed to read temperature");
  // }
  
  // if (! isnan(hum)) {  // check if 'is not a number'
  //   Serial.print("Hum. % = "); Serial.println(hum);
  // } else { 
  //   Serial.println("Failed to read humidity");
  // }
}
