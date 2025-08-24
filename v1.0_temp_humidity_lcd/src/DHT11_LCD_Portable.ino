// Functions Prototyping
void ReadSensorData(); 
void DisplayTempAndHumid();
void PrintValues();

#include "DHT.h"
#include <LiquidCrystal.h>

// DHT Sensor Setup
#define DHT_Type DHT11
const int DHT_Pin = 12;
DHT dhtSensor(DHT_Pin, DHT_Type);

// LCD Setup
const int RS = 7;
const int EN = 6;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Variables
float humidity = 0.0;
float tempC = 0.0;
float tempF = 0.0;

// Delays
const int initDelay = 500;
const int refreshDelay = 1000;
const int printDelay = 100;

// Debugging
const int Debug = false; // True = Print values to Serial Monitor

void setup() 
{
  Serial.begin(9600);   // Initialize the Serial Monitor
  dhtSensor.begin();    // Initialize the DHT Sensor
  lcd.begin(16, 2);     // Initialize the LCD
  delay(initDelay);
  lcd.clear();
}

void loop() 
{
  ReadSensorData();
  DisplayTempAndHumid();
  delay(refreshDelay);
}

void ReadSensorData() 
{
  humidity = dhtSensor.readHumidity();
  tempC = dhtSensor.readTemperature();     //        Celsius
  tempF = dhtSensor.readTemperature(true); // true = Fahrenheit

  if (isnan(humidity) || isnan(tempC)) 
  {
    Serial.println("Failed to read from DHT sensor!");
  }
}

void DisplayTempAndHumid() 
{
  // Clear display
  lcd.clear;

  // Display Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp (C) = ");
  lcd.print(tempC, 1);
  lcd.print((char)223); // To display "°" symbol

  // Display Humidity
  lcd.setCursor(0, 1);
  lcd.print("Humidity = ");
  lcd.print(humidity, 1);
  lcd.print("%");

  // Print to Serial Monitor
  if(Debug) 
  {
    PrintValues();
  }
  delay(printDelay);
}

  void PrintValues()
  {
    Serial.print("Temperature: ");
    Serial.print(tempF, 2);
    Serial.print("°"); // UTF-8 degree symbol
    Serial.print("F"); 
    Serial.print(" | ");
    Serial.print(tempC, 2);
    Serial.print("°"); 
    Serial.print("C"); 
    Serial.print(", Humidity: ");
    Serial.print(humidity, 2);
    Serial.println(" %");
  }