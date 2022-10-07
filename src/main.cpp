// ****************************************************************** 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 

// I, William Ohia, 000791775, I acknowledge that this is my own work and 
// no other person's work has been copied without acknowledgement. 
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

DeviceAddress newSensor;


 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 
   //DS18B20.begin();
   
  

}

void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    //if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  //printTemperature(deviceAddress);
  Serial.println();
}
 
void loop() { 
  float fTemp; 
  String temp;
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 

  

    if(fTemp < 10){
    temp = " cold";
  } else if( fTemp >= 10 && fTemp <= 15){
      temp = "cool";
  } else if( fTemp >= 15 && fTemp <= 25){
    temp = " Perfect";
  } else if( fTemp >= 25 && fTemp <= 30){
    temp = "Warm";
  } else if(fTemp >= 30 && fTemp <= 35){ 
    temp = "Hot";
  }else if(fTemp < 35){
    temp = "Too hot";
  }

  //printAddress(newSensor);
  printData(newSensor);
 
  // print the temp to the USB serial monitor 
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or " + temp); 
 
  // wait 2s (2000ms) before doing this again 
  delay(2000); 

  
} 