//the fucking russian thermometer lib
//the thing is also analog smh smh
#include <TroykaThermometer.h>

//uncomment if using actual digital thermometers
/*
  #include <Adafruit_Sensor.h>
  #include <DHT.h>
*/

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
//uncommment if using actual digital thermometers
/*
  //define DHT pins and type
  #define DHTPIN 11
  #define DHTPIN2 12
  #define DHTTYPE DHT11
*/
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


void setup()
{
  //uncomment if using actual digital thermometers
  /*
    //set data line pins to pullup, since we want that shit to be reliable
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);

    //init both DHTs
    dht.begin();
    dht2.begin();
  */

  //init LCD
  lcd.begin(16, 2);

  //create degree character
  lcd.createChar(0, degree);
}


void loop()
{
  //uncomment if using actual digital thermometers
  /*
    //defined here because yes
    int h = dht.readHumidity();
    float t = dht.readTemperature();
    int h2 = dht2.readHumidity();
    float t2 = dht2.readTemperature();
  */

  //read the thermometers
  temp1.read();
  temp2.read();

//LCD routine
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


  //pcmasterrace 4fps
  delay(250);
}
