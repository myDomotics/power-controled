// Projet Alimentation
// janvier 2018
// Alim-01 : test des fonction d'affichage
// Alim-02 : lecture temperature
// Alim-03 : vitesse ventilateur + lecture courant - PROD 21 JAN 2018

#include <Arduino.h>
#include <OneWire.h>
#include "TM1637Display.h"
// display
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);
const uint8_t A_CHARACTER[]={0b01110111};
const uint8_t T_CHARACTER[]={0b01111000};
#define DISPLAY_DELAY 5000

// One wire DS1820 temperature
int oneWirePin=4;
OneWire ds(oneWirePin);

byte temperatureAddr[8];
byte temperatureData[12];

// Fan Pin
#define FAN_PIN_1 9
#define FAN_PIN_2 10
#define FAN_PIN_3 11
#define FAN_PIN_4 12

#define LED_PIN 13

//current sensor pin
#define CURRENT_SENSOR_PIN A0

float current;
float temperature;

void setup() {
  Serial.begin(9600);
  // display
  display.setBrightness(0x05);
  // get DS1820 address
  getDSAddr();

}

void loop() {

  pinMode(FAN_PIN_1,OUTPUT);
  pinMode(FAN_PIN_2,OUTPUT);
  pinMode(FAN_PIN_3,OUTPUT);
  pinMode(FAN_PIN_4,OUTPUT);
  #ifdef TEST_FAN
  pinMode(LED_PIN,OUTPUT);
  testFanSpeed();
  #else
  clearDisplay();
  current=getCurrent();
  displayCurrent(current);
  delay(DISPLAY_DELAY);
  
  temperature=getTemperature();
  clearDisplay();
  displayTemperature(temperature);
  delay(DISPLAY_DELAY);
  fanSpeed(temperature);
  #endif
}
void clearDisplay(){
  uint8_t data[] ={0x00,0x00,0x00,0x00};
  display.setSegments(data);
}

void displayCurrent(float currentValue) {
  // convert to int and keep 1 digit precision
  int intCurrent=(int) (currentValue*10);
  if (intCurrent<0) intCurrent=0;
  if (intCurrent>999) intCurrent=999;
  display.setSegments(A_CHARACTER,1,0);
  display.showNumberDecEx(intCurrent,0x20,false,3,1);
}

void displayTemperature(float temperatureValue){
  // converto to int and keep 1 digit precision
  int intTemp=(int)temperatureValue;
  if (intTemp<0) intTemp=0;
  if (intTemp>999) intTemp=999;
  display.setSegments(T_CHARACTER,1,0);
  display.showNumberDecEx(intTemp,0x00,false,3,1);
}

void getDSAddr(){
  // get the address of the DS1820
  ds.reset_search();
  delay(250);
  if (!ds.search(temperatureAddr))
  {
    Serial.println('no OneWire address found');
  }


}
float getTemperature(){
  //return (float)random(500)/10;
  float temp=0;
  ds.reset();
  ds.select(temperatureAddr);
  ds.write(0x44,1);
  delay(1000);
  ds.reset();
  ds.select(temperatureAddr);
  ds.write(0xBE);
  for (byte i = 0; i < 9; i++)
  {
    temperatureData[i]=ds.read();
  }
  temp = ((temperatureData[1] << 8) | temperatureData[0]) * 0.5;
  return temp;
}
float getCurrent(){
  int rawData=analogRead(CURRENT_SENSOR_PIN);
  float current=((float) rawData*5.0/1024.0*36.7/5.0)-18.3;
  return current;
}

void fanSpeed(float temp){
  int speed;
  // calculate speed
  speed=tempToSpeed(temp);
  setFanSpeed(speed);
}

int tempToSpeed(float temp){
  if(temp<25.0) {return 1;}
  else{
    if(temp<30.0) {return 2;}
    else{
      if(temp<35.0){return 3;}
      else{
        if(temp<40.0){return 4;}
      }
    }
  }
  return 5;
}

void setFanSpeed(int speed){
  if(speed==4) {digitalWrite(FAN_PIN_1,LOW);}
  else {digitalWrite(FAN_PIN_1,HIGH);}

  if(speed==3){digitalWrite(FAN_PIN_2,LOW);}
  else {digitalWrite(FAN_PIN_2,HIGH);}

  if(speed==2){digitalWrite(FAN_PIN_3,LOW);}
  else {digitalWrite(FAN_PIN_3,HIGH);}

  if(speed==1){digitalWrite(FAN_PIN_4,LOW);}
  else {digitalWrite(FAN_PIN_4,HIGH);}
}

void testFanSpeed(){
 
  for (int i=1;i<=5;i++){
    for(int j=1;j<=i;j++){
      digitalWrite(LED_PIN,HIGH);
      delay(200);
      digitalWrite(LED_PIN,LOW);
      delay(200);
    }
    setFanSpeed(i);
    delay(5000);
    }
    
  
}

