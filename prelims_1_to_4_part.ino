// For servo motor
#include <Servo.h>

int number_of_person;
//for all
unsigned long currentT ;

// for OLED
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#include <Wire.h> 
#include <SPI.h> 
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 
String name;

// SERVO
Servo Door; 
#define button1 2
#define PIR 8
int door = 1;

// distance for person
const int trigPin = 5;   
const int echoPin = 6;  
long duration;           
int distance;   
#define led1 13
#define led2 12
#define led3 11
int human ;
int brightness = 0;
int fade = 10;
unsigned long Led3T = 0;
unsigned long Led2T = 0;
unsigned long USsensor = 0;
unsigned long strngT =0;
int strngname = 1;

//for motor
#define motorpoten A0
#define Mled 3
#define motorpin A2
#include "fan.h"
String speedname = "Speed:0";
int fanimage = 0;
unsigned long imageT = 0;
int motorspeed;

//for aircon
float tempvalue = 0;
int tempstate = 0;
float temp ;
String temperature = "";
#define airconbutton 7
#define lm35 A1
#define airconled1 4
#define airconled2 A3
int buttonstate = 0;
unsigned long airconT = 0;
unsigned long airconT2 = 0;

void setup() {
  //For OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { 
    Serial.println(F("SSD1306 allocation failed")); 
    for (;;); } 
  display.clearDisplay(); 
  display.display();
  Serial.begin(9600);

  //for servo and human infrared sensor
  Door.attach(9);
  pinMode(PIR,INPUT);
  pinMode(button1, INPUT_PULLUP);
  Door.write(45); 

  //for Ultrasonic sensor
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
  digitalWrite(trigPin, LOW);

  //for motor
  pinMode(motorpoten, INPUT);
  pinMode(motorpin, OUTPUT);
  pinMode(Mled, OUTPUT);
  digitalWrite(Mled, LOW);

  //for aircon
  pinMode(airconbutton, INPUT_PULLUP);
  pinMode(lm35, INPUT);
  pinMode(airconled1,OUTPUT);
  pinMode(airconled2,OUTPUT);  
}

void loop() { 
  //door
  do{  
    OLED(name,speedname,temperature);
    if (digitalRead(PIR) == 1 ){   
      Firstpart(door);
      door++;
    }
    else{
      Door.write(45);
    }
    currentT = millis();
  }while(door <= 3);

  //human and distance
  currentT = millis();
  if (currentT - USsensor >= 300){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  USsensor = currentT;
  }
  human = (distance >= 100) ? 0 : 
        (distance >= 60) ? 3 : 
        (distance >= 30) ? 2 : 
        (distance >= 10) ? 1 : human;

  name = (distance >= 100) ? "Hi" : 
        (distance >= 60) ? "CAMPAS" : 
        (distance >= 30) ? "VETORES" : 
        (distance >= 10) ? "LIPALAM" : name;

  Ledlights(human);

  //motor speed
  long potenvalue = analogRead(motorpoten);
  motorspeed = map(potenvalue,0,1023,0,4);
  fan(motorspeed);

  //for aircon temp
  if (digitalRead(airconbutton) == 0 && currentT - airconT >= 500){
      buttonstate = !buttonstate;
      airconT = currentT;
    }
  
  if (currentT - airconT2 >= 500){
    tempvalue = analogRead(lm35);
    temp = (tempvalue * (5.0/1023.0) ) * 100.0;
    Airconled(buttonstate,temp);
    Aircon(temp);

    if(temp > 70 ){
    Serial.print(temperature); 
    Serial.println();

    float tempvalue1;
    float temp1 = temp;
    while(temp1 > 70 && tempstate == 0){
      tempvalue1 = analogRead(lm35);
      temp1 = (tempvalue * (5.0/1023.0) ) * 100.0;
  
      if (Serial.available() > 0){
      tempstate = Serial.readStringUntil('\n').toInt();
      }

      Door.write(180);
      delay(50);
      }
    tempstate = 0;
    }
    airconT2 = currentT;
  }

  OLED(name,speedname,temperature);
  

  if (Serial.available() > 0) {
    number_of_person = Serial.readStringUntil('\n').toInt();
    // Print the received temperature to Serial Monitor
    if (number_of_person == 0){
      reset();
    }
  }

}

  
void OLED(String Name ,String speedname, String temp){ 

  display.clearDisplay(); 
  display.setTextSize(1); 
  display.setTextColor(WHITE); 

  display.drawRect(1,1, 127,31 , WHITE); 
  display.setCursor(4, 6); 
  display.println("GOOD DAY ");  

  if(door == 3 && currentT - strngT >= 1000){
    if(strngname == 1){
      name = "GUERRERO";
    }else{
      name = "VETORES";
    }
  strngT = currentT;
  strngname = !strngname;
  }

  display.setCursor(4, 18); 
  display.print(Name);  

  display.drawRect(1,31, 68,26 , WHITE); 
  display.setCursor(23, 41);
  display.print(speedname);

  if(currentT - imageT >= 20 && speedname != "Speed:0"){
    if( fanimage == 1){
    display.drawBitmap(5, 36, epd_bitmap_fan__2_, 15, 15, WHITE);
    }else{
    display.drawBitmap(5, 36, epd_bitmap_fan__3_, 15, 15, WHITE);
    imageT = currentT;
  }
  fanimage = !fanimage;
  }else{
    display.drawBitmap(5, 36, epd_bitmap_fan__2_, 15, 15, WHITE);
  }

  display.drawRect(68,31, 60, 26 , WHITE); 
  display.setCursor(70, 36);
  display.println("Temp: ");
  display.setCursor(70, 46);
  display.print(temp);
  
  //display.println(message);*/
  display.display();
}


void Firstpart(int door){
  switch(door){
    case 1 :
      Door.write(180);
      name = "LIPALAM";
      delay(2000);
      break;  
    case 2 : 
      Door.write(180);
      name = "GUERRERO";
      delay(2000);
      break;
    case 3 :
      while(digitalRead(button1) != 0){
        Door.write(45);
      }
      name = "CAMPAS";
      Door.write(180);
      Serial.print(3);
      Serial.println();
      OLED(name,speedname,temperature);
      delay(2000);
      break;
  }
}


void Ledlights(int distance){
  
  switch(distance){
  case 1:
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    break;
  case 2:
    currentT = millis();
    digitalWrite(led1,LOW);
    digitalWrite(led3,LOW);
    if (currentT - Led2T >= 250){
    digitalWrite(led2,!digitalRead(led2));
    Led2T = currentT;
    }
    break;
  case 3:
    currentT = millis();
    digitalWrite(led2,LOW);
    digitalWrite(led1,LOW);
    if (currentT - Led3T >= 20){
      analogWrite(led3,brightness);
      brightness += fade;
      Led3T = currentT;
      if (brightness >= 250 || brightness <= 0){
      fade = -fade;
      }
    } 
    break;
  default:
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    break;
 }
}

 void fan(int speed) {
  switch(speed) {
    case 0:
      analogWrite(motorpin, 0);
      digitalWrite(Mled, LOW);  
      speedname = "Speed:0";
      break;
    case 1:
      analogWrite(motorpin,130);
      analogWrite(Mled, (255 / 3));  
      speedname = "Speed:1";
      break;
    case 2:
      analogWrite(motorpin,190);
      analogWrite(Mled, (255 / 3) * 2); 
      speedname = "Speed:2";
      break;
    case 3:
      analogWrite(motorpin,255);
      analogWrite(Mled, 255);  
      speedname = "Speed:3" ;
      break;
  }
}

String Aircon(float temp){
  temperature = ""; 
  temperature += String(temp); 
  temperature += " C"; 
  return temperature;
}


void Airconled(int button , float temperature){
  switch(button){
    case 0:
      if(temperature > 30){
      digitalWrite(airconled1, HIGH);
      digitalWrite(airconled2, LOW);
      }else{
      digitalWrite(airconled2, HIGH);
      digitalWrite(airconled1, LOW);
      }
      break;
    case 1:
      digitalWrite(airconled1,HIGH);
      digitalWrite(airconled2,HIGH);  
      break;
  }
}

void reset(){
  display.clearDisplay(); 
  strngname = 1;
  tempvalue = 0;
  tempstate = 0;
  buttonstate = 0;
  fanimage = 0;
  digitalWrite(airconled1,LOW);
  digitalWrite(airconled2,LOW);
  Ledlights(0);
  fan(0);
  number_of_person = 1;
  door = 1;
  display.display();
}