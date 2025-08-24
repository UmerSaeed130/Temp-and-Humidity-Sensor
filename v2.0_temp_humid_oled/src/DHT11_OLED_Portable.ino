// Functions Prototyping
void ReadSensorData(); 
void DisplayTempAndHumid();
void PrintValues();

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>  
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET 4
//Adafruit_SH1106 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);  

// DHT Sensor Setup 
#define DHT_Type    DHT11     
const int DHT_Pin = 2;
DHT dhtSensor(DHT_Pin, DHT_Type);

// Variables
float humidity = 0.0;
float tempC = 0.0;

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
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the OLED
  delay(initDelay);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() 
{
  ReadSensorData();
  DisplayTempAndHumid();
  delay(refreshDelay);
}

void ReadSensorData() 
{
  tempC = dhtSensor.readTemperature();
  humidity = dhtSensor.readHumidity();

    if (isnan(humidity) || isnan(tempC)) 
  {
    Serial.println("Hello World!");
  }
}

void DisplayTempAndHumid()
{
  // Clear display
  display.clearDisplay();

  // Display Temperature
  display.setTextSize(1);
  display.setCursor(2,2);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(25,15);
  display.print(tempC);
  display.print(" ");
  display.setTextSize(2);
  display.cp437(true);
  display.write(248);
  display.setTextSize(2);
  display.print("C");
  
  // Display Humidity
  display.setTextSize(1);
  display.setCursor(2, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(25, 48);
  display.print(humidity);
  display.print("  %"); 
  
  display.display(); 

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
    Serial.print(tempC, 2);
    Serial.print("°"); 
    Serial.print("C"); 
    Serial.print(", Humidity: ");
    Serial.print(humidity, 2);
    Serial.println(" %");
  }
