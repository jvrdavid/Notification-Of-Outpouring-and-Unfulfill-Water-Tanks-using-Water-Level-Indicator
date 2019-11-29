/***************************************************************************************
*    Credits for making this project
*    
*    Title: Detecting Obstacles and Warning - Arduino and Ultrasonic
*    Author: Ammar Atef Ali
*    Date: February 12, 2016
*    Availability: https://create.arduino.cc/projecthub/ammaratef45/detecting-obstacles-and-warning-arduino-and-ultrasonic-13e5ea
*    
*    Title: How to control a character I2C LCD with Arduino
*    Author:Benne de Bakker 
*    Date: 2019 
*    Availability:https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/
*    
*    Title: HOW TO SET UP THE DHT11 HUMIDITY SENSOR ON AN ARDUINO
*    Author:Circuit Basics
*    Date: 2019 
*    Availability:http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
*    
*    Title: Blinking the LED
*    Author: Simon Monk
*    Date: Nov 17, 2019.
*    Availability:https://learn.adafruit.com/adafruit-arduino-lesson-2-leds/blinking-the-led
*    
*    Title: ACTIVE BUZZER WITH ARDUINO UNO R3
*    Author: primerobotics
*    Date: 2019 
*    Availability:https://www.instructables.com/id/ACTIVE-BUZZER-WITH-ARDUINO-UNO-R3/
*    
***************************************************************************************/
#include <dht.h> //library for Humidity and Temperature Sensor
#include <LiquidCrystal_I2C.h> // library for  LCD
#include <Wire.h> // library for communicating the  II2C to LCD

dht DHT;

#define trigPin 12 //
#define echoPin 13//
#define DHT11_PIN 11 //pin for Humidity and Temperature Sensor
int Buzzer = 8; // Connect Buzzer pin to 8
int ledPin= 6;  //Connect LED pin to 6
int duration , cm; //to measure the distance and time taken.
LiquidCrystal_I2C lcd(0x27,20,4); //access LCD 16 pins from II2C 4 pins

void setup() {
        Serial.begin (9600); 
        pinMode(trigPin, OUTPUT); 
        pinMode(echoPin, INPUT);
        pinMode(Buzzer, OUTPUT);
        pinMode(ledPin, OUTPUT); 
        lcd.init();          // Print a message to the LCD.           
        lcd.backlight();   //Lights On
}

void loop() {

   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   delayMicroseconds(10);
   duration = pulseIn(echoPin, HIGH);
   cm = (duration/2) / 29.1; //calculation to find the height of a container
   Serial.print(" cm "); 
   Serial.println(cm); 
 
 
 int chk = DHT.read11(DHT11_PIN); // read the D11 pin to access the H&T sensor component
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);



//if the height of a water is reaching 3cm,the buzzer and led light will On,and make a message display in lcd. 
 if (cm <= 3 ){
        lcd.setCursor(0,0);
        lcd.print("H2O level:100%"); 
        lcd.setCursor(0,1);
        lcd.print("cm:");
        lcd.print("0");
        lcd.print(cm);
        lcd.setCursor(7,1);
        lcd.print("Tmp:");
        lcd.print(DHT.temperature);
        digitalWrite(Buzzer,HIGH);
        digitalWrite(ledPin,HIGH);
        }
 //if the height of a water is reaching 7cm to 4cm ,the  led light will On with a blink of 1s continuously, and make a message display in lcd. 
  else if (cm <= 7){
        lcd.setCursor(0,0);
        lcd.print("H2O level:75% "); 
        lcd.setCursor(0,1);
        lcd.print("cm:");
        lcd.print("0");
        lcd.print(cm);
        lcd.setCursor(7,1);
        lcd.print("Temp:");
        lcd.print(DHT.temperature);
        digitalWrite(ledPin,HIGH);
        delay(1000);
        digitalWrite(ledPin,LOW);
    }

    //if the height of a water is reaching 9cm to 12cm ,the  led light will On with a blink of 50ms continuously, and make a message display in lcd. 
   else if (cm <= 9){
        lcd.setCursor(0,0);
        lcd.print("H2O level:50% "); 
        lcd.setCursor(0,1);
        lcd.print("cm:");
        lcd.print("0");
        lcd.print(cm);
        lcd.setCursor(7,1);
        lcd.print("Temp:");
        lcd.print(DHT.temperature);
        delay(100);
        digitalWrite(ledPin,HIGH);
        delay(500);
        digitalWrite(ledPin,LOW);
    }

    //if the height of a water is reaching 13cm to 10cm ,the  led light will On with a blink of 50ms continuously, and make a message display in lcd. 
     else if (cm <= 13){
        lcd.setCursor(0,0);
        lcd.print("H2O level:25% "); 
        lcd.setCursor(0,1);
        lcd.print("cm:");
        lcd.print(cm);
        lcd.setCursor(7,1);
        lcd.print("Temp:");
        lcd.print(DHT.temperature);
        digitalWrite(ledPin,HIGH);
        delay(50);
        digitalWrite(ledPin,LOW);
    }

  //if the height of a water is reaching 14cm to 16cm ,the buzzer will On with a delay of 1s continuously, and make a message display in lcd. 
  else{                           
       lcd.setCursor(0,0);
       lcd.print("H2O level:0%  ");
       lcd.setCursor(0,1);
       lcd.print("cm:");
       lcd.print(cm);
       lcd.setCursor(7,1);
       lcd.print("Temp:");
       lcd.print(DHT.temperature);
       digitalWrite(Buzzer,HIGH);
       delay(500);
       digitalWrite(Buzzer,LOW);
       
  } 
  delay(50);
  
}

 // i use the ruler to determine the distance of a miniature.Instead of using 1.5 L of bottle, i use the jar of stick 0 
 // also the ruler i used is mm,so i divisible by 10 and i got the constant value for cm.
    
 //it detects the remaining space of a tank, if this value meet the height of a water,it will ring and make the led light
 //duration = travel time , 2 = twice the distance 29.1 = speed of sound//
  
 // I make a way to prevent the overlapping of a value in a LCD 
 //so i decide to make a lcdprint for the 1 digit only in this format 
 //(01,02,...,09) then the other number will print 2 or more digits,
 //but the maximum height of a miniature that we provide will be estimated of 18 cm or 17cm
 
 //Also the height that detect the ultrasonic sensor is from 3cm to 15 cm only

 
//still there's need to improve....Stay tuned//
