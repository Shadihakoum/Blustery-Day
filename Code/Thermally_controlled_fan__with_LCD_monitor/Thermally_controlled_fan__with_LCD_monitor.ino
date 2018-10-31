// Read analog temperature sensor and turn external fan on and off dependent on some predefined setpoint, using ATmega32u4 micro controller
// Additionaly, prints current temperature out to LCD screan, with options to add a user defined setpoint(futur development)
#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>

// Sets the pin number for the sensor at analog pin 41.
const int Temp_Sensor = 41;

// Sets the input pin to increase or decrease the threshold temperature and change unit 
const int Dwn_Btn_pin = 36;
const int Up_Btn_pin = 37;
const int Unit_Btn_Pin = 38

// Sets output pins for fan and LCD, and initialize LCD pins
const int Fan_Control = 31;
const int rs = 25;
const int en = 26;
const int d4 = 27;
const int d5 = 28;
const int d6 = 29;
const int d7 = 30;
LiquidCrystal lcd(rs,en,d4,d5,d6);

// Initialize user interface
int Dwn_Btn_State = 0
int Up_Btn_State = 0
int Unit_Btn_State = 0
int Dwn_Btn_LastState = 0
int Up_Btn_LastState = 0
int Unit_Btn_LastState = 0;

// Sets the intial threshold value to 23 degrees C
int Set_Temp = 23;

// Sets the initial temperature units to C
char units = 'C';

// create a character variable for outputing temperature to LCD screen
char[9] LCD_Output = 'p';

void setup() {
// Setup serial port to opperate at 9600 bits per second
Serial.begin(9600);

// Initialize input pins 41, 8,1 
pinMode(Temp_Sensor, INPUT) ; 
pinMode(Dwn_Btn_Pin, INPUT);
pinMode(Up_Btn_pin, INPUT);
pinMode(Unit_Btn_pin, INPUT);

// Initialize fan output pin
pinMode(Fan_Control, OUTPUT);
//pinMode(LCD_0, OUTPUT);
//pinMode(LCD_1, OUTPUT);
//pinMode(LCD_2, OUTPUT);
//pinMode(LCD_3, OUTPUT);
//pinMode(LCD_4, OUTPUT);
//pinMode(LCD_5, OUTPUT);
//pinMode(LCD_6, OUTPUT);
//pinMode(LCD_7, OUTPUT);

// Set the LCD's number of columns and rows
lcd.begin(, 2)

// Prints the, constant, header of the LCD
lcd.print("Temp. Set Temp.")

}

void loop() {
// read the value from the sensor at pin 41 and store as a 16bit integer 
uint16_t  Temp = analogRead(Temp_Sensor);

// Mapping output voltage from temperature sensor to corresponding temperature in degrees C 
Convert_Temp = map(Temp_Sensor, -490, 1500, -55, 150)
  
// read the input pin for user buttons
Dwn_Btn_State = digitalRead(Dwn_Btn_Pin);
Up_Btn_State = digitalRead(Up_Btn_Pin);
Unit_Btn_State = digitalRead(Unit_Btn_Pin); 

// check if user has pressed the down button
if (Dwn_Btn_State != Dwn_Btn_LastState)
{
  // Decrement set temp.
  Set_Temp--;

  // Delay, to help prevent bouncing
  delay(50);
}
// Update state of Dwn Btn
Dwn_Btn_LastState = Dwn_Btn_Sate;

// Check if user has pressed the up button
if (Up_Btn_State != Up_Btn_LastState)
{
  // Increment set temp
  Set_Temp++;

  // Delay, to help prevent bouncing
  delay(50);
}
// Udate state of Up Btn
Up_Btn_LastState = Up_Btn_State;

// Check if the value is high or low
if (Unit_Btn_State == HIGH)
{
  // Sets the temperature unit as  degrees F
  units = 'F';

  // Convert threshold and sensor temperature to degrees F
  Set_Temp_F = (Set_Temp * (9/5)) + 32;
  Convert_Temp_F = (Convert_Temp * (9/5)) + 32; 
  
  // Set the Cursor loaction of the LCD for room temperature 
  lcd.setCursor(0, 1);

  // Create message to be printed to LCD
  sprintf(LCD_Output, "%3d %3d char(223)%c", Convert_Temp_F, Set_Temp_F, units);

  // Print Temperatures to LCD
  lcd.print(LCD_Output);
  
}
else
{
  // sets the temperature unit as degrees C
  units = 'C';

  // Set the Cursor loaction of the LCD for room temperature 
  lcd.setCursor(0, 1);

  // Create message to be printed to LCD
  sprintf(LCD_Output, "%3d %3d char(223)%c", Convert_Temp, Set_Temp, units);

  // Print Temperatures to LCD
  lcd.print(LCD_Output);  
  
}
  
  // Delay, to help prevent bouncing
  delay(50);
}
// Update state of the Unit button
Unit_Btn_LastState = Unit_Btn_State;

}
