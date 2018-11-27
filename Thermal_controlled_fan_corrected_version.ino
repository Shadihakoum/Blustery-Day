#include <LiquidCrystal.h>
#include <Wire.h>
#include <SPI.h>

const int led = 13; //initialize chip pin 32 as led
const int Temp_Sensor = A5; 
const int Dwn_Btn_Pin = 2;   
const int Up_Btn_Pin = 0; 
const int Unit_Btn_Pin = 1;

const int Fan_Control = 5;
const int rs = 4;
const int en = 12;
const int d4 = 6;
const int d5 = 8;
const int d6 = 9;
const int d7 = 10;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

int Dwn_Btn_State = 0;
int Up_Btn_State = 0;
int Unit_Btn_State = 0;
int Dwn_Btn_LastState = 0;
int Up_Btn_LastState = 0;
int Last_Unit_Btn_State = 0;

int Temperature;

int Set_Temp = 35; //threshold temperature 

char LCD_output[10]={};

int Set_Temp_F = 0;
int Convert_Temp_F = 0;

void setup(){
  Serial.begin(19200);

  pinMode(Temp_Sensor, INPUT);
  pinMode(Dwn_Btn_Pin, INPUT);
  pinMode(Up_Btn_Pin, INPUT);
  pinMode(Unit_Btn_Pin, INPUT);
  pinMode(Fan_Control, OUTPUT);
  pinMode(led, OUTPUT);

  lcd.begin(16,2);
  lcd.print("Current Desired");
  }


void loop(){
  Temperature = analogRead(Temp_Sensor);
  Temperature = Temperature/2 - 13;
  
  if (Unit_Btn_State == HIGH){
    if(Unit_Btn_State != Last_Unit_Btn_State){
      units = 'F';
      Unit_Btn_State = Last_Unit_Btn_State;
      delay(50);
    }
    else{
    units = 'C';
    Last_Unit_Btn_State = Unit_Btn_State + 1;
    delay(50);
    }
  }
  if(units == 'F'){
    unitButtonPress();
    }
  else {
    unitButtonNotPress();
  }

int Last_Unit_Btn_State = 0;

  void unitButtonPress(){
    digitalWrite(led, HIGH);
    Set_Temp_F = (Set_Temp * 9/5) + 32;
    Convert_Temp_F = (Temperature *9/5) +32; 
    lcd.setCursor(0,1);
    sprintf(LCD_Output, "%3d %c    %3d %c", Convert_Temp_F, units, Set_Temp_F)
    lcd.print(LCD_Output);

       if (Convert_Temp_F >= Set_Temp_F){
        digitalWrite(Fan_Control, HIGH);
        }
        else{
          digitalWrite(Fan_Control, LOW);
          }
    }

void unitButtonNotPressed(){
  lcd.setCursor(0, 1);
  sprintf(LCD_Output, "%3d %c    %3d %c", Temperature, units, Set_Temp, units);
  lcd.print(LCD_Output);
 
        if (Temperature >= Set_Temp)
        {
          digitalWrite(Fan_Control, HIGH); 
        }
        else
        {
          digitalWrite(Fan_Control, LOW);
        }
  }

