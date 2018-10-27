// Read analog temperature sensor and turn external fan on and off dependent on some predefined setpoint, using ATmega32u4 micro controller
// Additionaly, prints current temperature out to LCD screan, with options to add a user defined setpoint(futur development)
#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>

// Sets the pin number for the sensor at analog pin 41.
const int Temp_Sensor = 41;

// Sets the input pin to increase or decrease the threshold temperature
const int Dwn_Btn = 8
const int Up_Btn = 9

void setup() {
// Setup serial port to opperate at 9600 bits per second
  Serial.begin(9600);

// Initialize pins 41, 8,1 
pinMode(Temp_Sensor, INPUT) ; 
pinMode(Dwn_Btn, INPUT);
pinMode(Up_Btn, INPUT);
}

void loop() {
// read the value from the sensor at pin 41 and store as a 16bit integer 
  uint16_t  Temp = analogRead(Temp_Sensor);

  

// Mapping output voltage from temperature sensor to corresponding temperature in degrees C 
  Convt_Temp = map(Temp_Sensor, -490, 1500, -55, 150)

}
