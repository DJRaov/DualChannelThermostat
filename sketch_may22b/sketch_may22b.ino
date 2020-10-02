//the fucking russian thermometer lib
//the thing is also analog smh smh
#include <TroykaThermometer.h>

//real thermometers lib
#include <Adafruit_Sensor.h>
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
//define DHT pins
#define DHTPIN 11
#define DHTPIN2 12

//define the LCD
LiquidCrystal lcd(7, 6, 2, 3, 4, 5);

//define both thermometers
TroykaThermometer temp1(A0);
TroykaThermometer temp2(A1);

//uncomment if using actual digital thermometers
/*
  //define 2 functions for the DHTs so they can de addressed individually
  DHT dht(DHTPIN, DHTTYPE);
  DHT dht2(DHTPIN2, DHTTYPE);
*/

DHT dht11_1(DHTPIN, DHT11);
DHT dht11_2(DHTPIN2, DHT11);
DHT dht21_1(DHTPIN, DHT21);
DHT dht21_2(DHTPIN2, DHT21);
DHT dht22_1(DHTPIN, DHT22);
DHT dht22_2(DHTPIN2, DHT22);

void setup()
{
  //set data line pins to pullup, since we want that shit to be reliable
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  //declare and init as blank
  int t = 0;
  int h = 0;
  
  //try to init all DHTs
  dht11_1.begin();
  dht11_2.begin();
  dht21_1.begin();
  dht21_2.begin();
  dht22_1.begin();
  dht22_2.begin();

  /*   if/else chain pain orgy begins from this point   *
   *              beware ye who enter here              *
  */
  if (isnan(dht11_1.readTemperature()))
  {
    
  }
  else
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT11 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 1");
    int t = dht11_1.readTemperature();
    int h = dht11_1.readHumidity();
    delay(750);
  }
  if (isnan(dht11_2.readTemperature()))
  {
    
  }
  else
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT11 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 2");
    int t = dht11_2.readTemperature();
    int h = dht11_2.readHumidity();
    delay(750);
  }
  if (isnan(dht21_1.readTemperature()))
  {
    
  }
  else
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT21 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 1");
    int t = dht21_1.readTemperature();
    int h = dht21_1.readHumidity();
    delay(750);
  }
  if (isnan(dht21_2.readTemperature()))
  {
    
  }
  else
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT21 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 2");
    int t = dht21_2.readTemperature();
    delay(750);
  }
  if (isnan(dht22_1.readTemperature()))
  {
    
  }
  else
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT22 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 1");
    int t = dht22_1.readTemperature();
    delay(750);
  }
  if (isnan(dht22_2.readTemperature()))
  {

  }
  else
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT22 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 2");
    int t = dht22_2.readTemperature();
    delay(750);
  }

  //init LCD
  lcd.begin(16, 2);

  //create degree character
  lcd.createChar(0, degree);
}


void loop()
{
  if (isnan(h) and isnan(h2))
  {
    void TroykaTherm()
  }
  else if (isnan(h))
  {
    lcd.setCursor(1, 0);
    lcd.print("Channel 1 DHT");
    lcd.setCursor(2, 1);
    lcd.print("not present!");
    delay(2500);
    void DHTxx()
  }
  if (isnan(h2))
  {
    lcd.setCursor(1, 0);
    lcd.print("Channel 2 DHT");
    lcd.setCursor(2, 1);
    lcd.print("not present!");
    delay(2500);
    void DHTxx()
  }
}

void TroykaTherm() {
  //read the thermometers
  temp1.read();
  temp2.read();

  //LCD routine [Temp-only]
  //Main sensor
  lcd.setCursor(0, 0);
  lcd.print("CH1");

  if (temp1.getTemperatureC() >= 100)
  {
    lcd.setCursor(8, 0);
  }
  else
  {
    lcd.setCursor(9, 0);
  }
  lcd.print(temp1.getTemperatureC() - 17);
  lcd.write(byte(0));

  if (temp1.getTemperatureC() >= 100)                 //double-celcius bugfix
  {
    lcd.setCursor(15, 0);
    lcd.print(" ");
  }


  //Secondary sensor
  lcd.setCursor(0, 1);
  lcd.print("CH2");
  if (temp2.getTemperatureC() >= 100)
  {
    lcd.setCursor(8, 1);
  }
  else
  {
    lcd.setCursor(9, 1);
  }

  lcd.print(temp2.getTemperatureC() - 17);
  lcd.write(byte(0));

  if (temp2.getTemperatureC() >= 100)                 //double-celcius bugfix
  {
    lcd.setCursor(15, 1);
    lcd.print(" ");
  }
}

void DHTxx() {
  //Main DHT
  lcd.setCursor(0, 0);
  lcd.print("CH1");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.write(byte(0));
  lcd.setCursor(13, 0);
  lcd.print(h);
  lcd.print("%");

  //Secondary DHT
  lcd.setCursor(0, 1);
  lcd.print("CH2");
  lcd.setCursor(6, 1);
  lcd.print(t2);
  lcd.write(byte(0));
  lcd.setCursor(13, 1);
  lcd.print(h2);
  lcd.print("%");

  //pcmasterrace 4fps
  delay(250);
}
