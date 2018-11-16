// Read analog temperature sensor and turn external fan on and off dependent on some predefined setpoint, using ATmega32u4 micro controller
// Additionaly, prints current temperature out to LCD screan, with options to add a user defined setpoint(futur development)
#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>

const int led = 13; // Pin 32 on chip.

// Sets the pin number for the sensor at analog pin 41.
  const int Temp_Sensor = A5; // Pin 41 on chip

// Sets the input pin to increase or decrease the threshold temperature and change unit 
  const int Dwn_Btn_Pin = 2; // Pin 19 on chip;
  const int Up_Btn_Pin = 0; // Pin 20 on chip;
  const int Unit_Btn_Pin = 1; // Pin 21 on chip;

// Sets output pins for fan and LCD, and initialize LCD pins
  const int Fan_Control = 5; // Pin 31 on chip
  const int rs = 4; // Pin 25 on chip
  const int en = 12; // Pin 26 on chip
  const int d4 = 6; // Pin 27 on chip
  const int d5 = 8; // Pin 28 on chip
  const int d6 = 9; // Pin 29 on chip
  const int d7 = 10; // Pin 30 on chip
  LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// Initialize user interface
  int Dwn_Btn_State = 0;
  int Up_Btn_State = 0;
  int Unit_Btn_State = 0;
  int Dwn_Btn_LastState = 0;
  int Up_Btn_LastState = 0;
  int Last_Unit_Btn_State = 0;

// Initializes the variable temperature, to store the analog temperature from the sensor
  int Temperature;

// Sets the intial threshold value to 23 degrees C
  int Set_Temp = 35;

// Sets the initial temperature units to C
  char units = 'C';

// create a character variable for outputing temperature to LCD screen
  char LCD_Output[10] = {} ;

// Create variables for fahrenheit temperature outputs
  int Set_Temp_F = 0;
  int Convert_Temp_F = 0;

  void setup() {
// Setup serial port to opperate at 9600 bits per second
  Serial.begin(19200);

// Initialize input pins 
  pinMode(Temp_Sensor, INPUT) ; 
  pinMode(Dwn_Btn_Pin, INPUT);
  pinMode(Up_Btn_Pin, INPUT);
  pinMode(Unit_Btn_Pin, INPUT);

// Initialize fan control pin and test led
  pinMode(Fan_Control, OUTPUT);
  pinMode(led, OUTPUT);
//pinMode(LCD_0, OUTPUT);
//pinMode(LCD_1, OUTPUT);
//pinMode(LCD_2, OUTPUT);
//pinMode(LCD_3, OUTPUT);
//pinMode(LCD_4, OUTPUT);
//pinMode(LCD_5, OUTPUT);
//pinMode(LCD_6, OUTPUT);
//pinMode(LCD_7, OUTPUT);

// Set the LCD's number of columns and rows
  lcd.begin(16, 2);

// Prints the, constant, header of the LCD
  lcd.print("Current Desired");

}

  void loop() {
// read the value from the sensor at pin 41 and store as a 16bit integer 
  Temperature = analogRead(Temp_Sensor);
  Temperature = Temperature/2 - 13;
  
// Mapping output voltage from temperature sensor to corresponding temperature in degrees C 
  //int Convert_Temp = map(Temperature, -490, 1500, -55, 150);
  
// read the input pin for user buttons
  Dwn_Btn_State = digitalRead(Dwn_Btn_Pin);
  Up_Btn_State = digitalRead(Up_Btn_Pin);
  Unit_Btn_State = digitalRead(Unit_Btn_Pin);

// check if user has pressed the down button
  if (Dwn_Btn_State == HIGH){
  // Decrement set temp.
    Set_Temp = Set_Temp - 1;
  }

// Check if user has pressed the up button
  if (Up_Btn_State == HIGH){
  // Increment set temp
    Set_Temp = Set_Temp + 1;
  }
  
// Check if the user wantes degrees F or C
  if (Unit_Btn_State == HIGH){
    if(Unit_Btn_State != Last_Unit_Btn_State){
  // Sets the temperature unit as  degrees F
    units = 'F';

    digitalWrite(led, HIGH);

  // Convert threshold and sensor temperature to degrees F
    Set_Temp_F = (Set_Temp * (9/5)) + 32;
  //  Convert_Temp_F = (Convert_Temp * (9/5)) + 32;
  Convert_Temp_F = (Temperature * (9/5)) + 32;

  // Check the temperature and turn the fan off or on
     if (Convert_Temp_F >= Set_Temp_F){
      digitalWrite(Fan_Control, HIGH); 
     }
     else{
      digitalWrite(Fan_Control, LOW);
     }
  
  // Set the Cursor loaction of the LCD for room temperature 
    lcd.setCursor(0, 1);

  // Create message to be printed to LCD
    sprintf(LCD_Output, "%3d %c    %3d %c", Convert_Temp_F, units, Set_Temp_F, units);

  // Print Temperatures to LCD
    lcd.print(LCD_Output);

  // Sets current and last state equal for futur use 
     Last_Unit_Btn_State = Unit_Btn_State;

    }
    else{
  // sets the temperature unit as degrees C
    units = 'C';
    
  // Check the temperature and turn the fan off or on
  //  if (Convert_Temp >= Set_Temp){
      if (Temperature >= Set_Temp){
      digitalWrite(Fan_Control, HIGH); 
     }
     else{
      digitalWrite(Fan_Control, LOW);
     }

  // Set the Cursor loaction of the LCD for room temperature 
    lcd.setCursor(0, 1);

  // Create message to be printed to LCD
  // sprintf(LCD_Output, "%3d %c    %3d %c", Convert_Temp,units, Set_Temp, units);
  sprintf(LCD_Output, "%3d %c    %3d %c", Temperature, units, Set_Temp, units);

  // Print Temperatures to LCD
    lcd.print(LCD_Output);

  // Sets current and last state equal for futur use 
    Last_Unit_Btn_State = Unit_Btn_State + 1;
    }
    delay(2000);
  }
}
