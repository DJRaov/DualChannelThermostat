//Prerequisite for DHT lib
#include <Adafruit_Sensor.h>

//DHT libs
#include <DHT.h>

//LCD lib
#include <LiquidCrystal.h>

//degree symbol
byte degree[8] =
{
  0b01000,
  0b10100,
  0b01000,
  0b00011,
  0b00100,
  0b00100,
  0b00011,
  0b00000,
};

//define DHT pins and type
#define DHTPIN 11
#define DHTPIN2 12
#define DHTTYPE DHT11

//define the LCD
LiquidCrystal lcd(7, 6, 2, 3, 4, 5);

//define 2 functions for the DHTs so they can de addressed individually
DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);



void setup()
{
  //set data line pins to pullup, since we want that shit to be reliable
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  
  //init both DHTs
  dht.begin();
  dht2.begin();

  //init LCD
  lcd.begin(16, 2);

  //create degree character
  lcd.createChar(0, degree);
}


void loop()
{
  //defined here because fuck syntax
  int h = dht.readHumidity();
  float t = dht.readTemperature();
  int h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

//LCD routine


  //Internal (main) DHT
  lcd.setCursor(0, 0);
  lcd.print("Int");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.write(byte(0));
  lcd.setCursor(13, 0);
  lcd.print(h);
  lcd.print("%");

  //External DHT
  lcd.setCursor(0, 1);
  lcd.print("Ext");
  lcd.setCursor(6, 1);
  lcd.print(t2);
  lcd.write(byte(0));
  lcd.setCursor(13, 1);
  lcd.print(h2);
  lcd.print("%");
  
  //pcmasterrace 60fps
  delay(16);
}
