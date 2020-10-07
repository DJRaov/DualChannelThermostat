//the russian thermometer lib
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

//define both analog thermometers
TroykaThermometer temp1(A0);
TroykaThermometer temp2(A1);

//define all possible DHTs
DHT dht11_1(DHTPIN, DHT11);
DHT dht11_2(DHTPIN2, DHT11);
DHT dht21_1(DHTPIN, DHT21);
DHT dht21_2(DHTPIN2, DHT21);
DHT dht22_1(DHTPIN, DHT22);
DHT dht22_2(DHTPIN2, DHT22);

//finally figured it out
int dht_ch1_type;
int dht_ch2_type;
bool dht_ch1_present;
bool dht_ch2_present;
int t;
int t2;
int h;
int h2;

void setup()
{
  //open up serial for debug
  Serial.begin(9600);
  Serial.println("Welcome to the shitfest. I don't know how you entered here, but you did. Now witness debug info.");    //yes


  //set data line pins to pullup, since we want that shit to be reliable
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  Serial.println("Pins 11 and 12 put up as INPUT_PULLUP");

  //init LCD
  lcd.begin(16, 2);
  Serial.println("LCD Init");

  //create degree character
  lcd.createChar(0, degree);

  //try to init all DHTs
  dht11_1.begin();
  dht11_2.begin();
  dht21_1.begin();
  dht21_2.begin();
  dht22_1.begin();
  dht22_2.begin();
  Serial.println("DHT Init");

  /*   even i dont know what happens beyond this point   *
                  beware ye who enter here
  */
  Serial.println("Check for DHT11 on CH1");
  if (isnan(dht11_1.readTemperature()) != 1)
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT11 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 1");
    dht_ch1_type = 0;
    dht_ch1_present = 1;
    delay(750);
    lcd.clear();
  }
  Serial.println("Check for DHT11 on CH2");
  if (isnan(dht11_2.readTemperature()) != 1)
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT11 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 2");
    dht_ch1_type = 0;
    dht_ch2_present = 1;
    delay(750);
    lcd.clear();
  }

  Serial.println("Check for DHT21 on CH1");
  if (isnan(dht21_1.readTemperature()) != 1)
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT21 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 1");
    dht_ch1_type = 1;
    dht_ch1_present = 1;
    delay(750);
    lcd.clear();
  }

  Serial.println("Check for DHT21 on CH2");
  if (isnan(dht21_2.readTemperature()) != 1)
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT21 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 2");
    dht_ch1_type = 1;
    dht_ch2_present = 1;
    delay(750);
    lcd.clear();
  }

  Serial.println("Check for DHT22 on CH1");
  if (isnan(dht22_1.readTemperature()) != 1)
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT22 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 1");
    lcd.clear();
    dht_ch1_type = 2;
    dht_ch1_present = 1;
    delay(750);
    lcd.clear();
  }

  Serial.println("Check for DHT22 on CH2");
  if (isnan(dht22_2.readTemperature()) != 1)
  {
    lcd.setCursor(1, 0);
    lcd.print("DHT22 Detected");
    lcd.setCursor(2, 1);
    lcd.print("on Channel 2");
    dht_ch1_type = 2;
    dht_ch2_present = 1;
    delay(750);
    lcd.clear();
  }

  Serial.println("----- Check if any DHTs were found -----");
  if (dht_ch1_present && dht_ch2_present == 0)
  {
    Serial.println("No DHTs found, calling TroykaTherm");
    TroykaTherm();
  }
  else
  {
    if (dht_ch1_present == 0)
    {
      Serial.println("DHTs on CH1 not present, displaying");
      lcd.setCursor(1, 0);
      lcd.print("Channel 1 DHT");
      lcd.setCursor(2, 1);
      lcd.print("not present!");
      delay(2500);
      lcd.clear();
    }
    if (dht_ch2_present == 0)
    {
      Serial.println("DHTs on CH2 not present, displaying");
      lcd.setCursor(1, 0);
      lcd.print("Channel 2 DHT");
      lcd.setCursor(2, 1);
      lcd.print("not present!");
      delay(2500);
      lcd.clear();
    }
    Serial.println("At least one DHT was found, calling DHTxx");
    DHTxx();
  }
}


void loop()
{
  if (dht_ch1_present && dht_ch2_present == 0)
  {
    Serial.println("----- Calling TroykaTherm -----");
    TroykaTherm();
  }
  else
  {
    Serial.println("----- Calling DHTxx -----");
    DHTxx();
  }
}

void DHTxx() {
  Serial.println("----- DHTxx was called -----");
  Serial.println("  ---   LCD CH1 Begin  ---  ");
  //Main DHT
  Serial.println("Was a DHT on CH1 found?");
  if (dht_ch1_present == 1)
  {
    Serial.println("Yep, checking which type");
    switch (dht_ch1_type)
    {
      case 0:
        Serial.println("The type is DHT11");
        t = dht11_1.readTemperature();
        h = dht11_1.readHumidity();
        break;
      case 1:
        Serial.println("The type is DHT21");
        t = dht21_1.readTemperature();
        h = dht21_1.readHumidity();
        break;
      case 2:
        Serial.println("The type is DHT22");
        t = dht22_1.readTemperature();
        h = dht22_1.readHumidity();
        break;
    }
    Serial.println("  ---   LCD CH1 Draw    --- ");
    Serial.println("LCD cursor set to 0,0");
    lcd.setCursor(0, 0);
    Serial.println("Printing CH1");
    lcd.print("CH1");
    Serial.println("LCD cursor set to 6,0");
    lcd.setCursor(6, 0);
    Serial.println("Printing the temperature from the DHT on CH1");
    lcd.print(t);
    Serial.println("Priting the degree symbol");
    lcd.write(byte(0));
    Serial.println("LCD cursor set to 13,0");
    lcd.setCursor(13, 0);
    Serial.println("Printing the humidity from the DHT on CH1");
    lcd.print(h);
    Serial.println("the percent");
    lcd.print("%");
  }
  else {
    Serial.println("DHTs on CH1 were not found, printing blanks");
    lcd.setCursor(0, 0);
    lcd.print("CH1");
    lcd.setCursor(6, 0);
    lcd.print("--.--");
    lcd.write(byte(0));
    lcd.setCursor(13, 0);
    lcd.print("--");
    lcd.print("%");
  }
  Serial.println("  ---    LCD CH1 End   ---  ");

  Serial.println("  ---   LCD CH2 Begin  ---  ");
  //Secondary DHT
  Serial.println("Was a DHT on CH2 found?");
  if (dht_ch2_present == 1)
  {
    Serial.println("Yes, checking which type");
    switch (dht_ch1_type)
    {
      case 0:
        Serial.println("The type is DHT11");
        t2 = dht11_2.readTemperature();
        h2 = dht11_2.readHumidity();
        break;
      case 1:
        Serial.println("The type is DHT21");
        t2 = dht21_2.readTemperature();
        h2 = dht21_2.readHumidity();
        break;
      case 2:
        Serial.println("The type is DHT22");
        t2 = dht22_2.readTemperature();
        h2 = dht22_2.readHumidity();
        break;
    }
    Serial.println("  ---  LCD CH2 Draw   ---  ");
    Serial.println("LCD cursor set to 0,1");
    lcd.setCursor(0, 1);
    Serial.println("Printing CH2");
    lcd.print("CH2");
    Serial.println("LCD cursor set to 6,1");
    lcd.setCursor(6, 1);
    Serial.println("Printing the temperature from the DHT on CH2");
    lcd.print(t2);
    Serial.println("Priting the degree symbol");
    lcd.write(byte(0));
    Serial.println("LCD cursor set to 13,1");
    lcd.setCursor(13, 1);
    Serial.println("Printing the humidity from the DHT on CH2");
    lcd.print(h2);
    Serial.println("the percent");
    lcd.print("%");
  }
  else {
    Serial.println("DHTs on CH2 were not found, printing blanks");
    lcd.setCursor(0, 1);
    lcd.print("CH2");
    lcd.setCursor(6, 1);
    lcd.print("--.--");
    lcd.write(byte(0));
    lcd.setCursor(13, 1);
    lcd.print("--");
    lcd.print("%");
  }
  Serial.println("  ---   LCD CH1 End   ---  ");
  //pcmasterrace 4fps
  delay(250);
  Serial.println("----- Sequence ended. -----");
}


void TroykaTherm() {
  Serial.println("  ----- TroykaTherm was called -----  ");
  Serial.println("    ---     Thermo reading     ---  ");
  //read the thermometers
  Serial.println("Sensor 1 read");
  temp1.read();
  Serial.println("Sensor 2 read");
  temp2.read();

  Serial.println("    ---      LCD CH1 Begin     ---");
  //LCD routine [Temp-only]
  //Main sensor
  Serial.println("LCD cursor set to 0,0");
  lcd.setCursor(0, 0);
  lcd.print("CH1");
  Serial.println("Check if the read temp is >100");
  if (temp1.getTemperatureC() >= 100)
  {
    Serial.println("LCD cursor set 8,0");
    lcd.setCursor(8, 0);
  }
  else
  {
    Serial.println("LCD cursor set 9,0");
    lcd.setCursor(9, 0);
  }
  Serial.println("Print CH1 temperature biased by -17 deg");
  lcd.print(temp1.getTemperatureC() - 17);
  lcd.write(byte(0));
  
  Serial.println("Check if the read temp is <100");
  if (temp1.getTemperatureC() <= 100)                 //double-celcius bugfix
  {
    Serial.println("Inserting blank space ");
    Serial.println("LCD cursor set to 15,0");
    lcd.setCursor(15, 0);
    Serial.println("print that mofo");
    lcd.print(" ");
  }
  Serial.println("    ---       LCD CH1 End      ---");

  Serial.println("    ---      LCD CH2 Begin     ---");
  //Secondary sensor
  Serial.println("LCD cursor set to 0,1");
  lcd.setCursor(0, 1);
  lcd.print("CH1");
  Serial.println("Check if the read temp is >100");
  if (temp2.getTemperatureC() >= 100)
  {
    Serial.println("LCD cursor set 8,1");
    lcd.setCursor(8, 1);
  }
  else
  {
    Serial.println("LCD cursor set 9,1");
    lcd.setCursor(9, 1);
  }
  Serial.println("Print CH2 temperature biased by -17 deg");
  lcd.print(temp2.getTemperatureC() - 17);
  lcd.write(byte(0));
  
  Serial.println("Check if the read temp is <100");
  if (temp1.getTemperatureC() <= 100)                 //double-celcius bugfix
  {
    Serial.println("Inserting blank space ");
    Serial.println("LCD cursor set to 15,1");
    lcd.setCursor(15, 1);
    Serial.println("print that mofo");
    lcd.print(" ");
  }
  Serial.println("Waiting 250ms...");
  delay(250);
  Serial.println("Display cleared");
  lcd.clear();
  Serial.println("----- Sequence ended. -----");
}
