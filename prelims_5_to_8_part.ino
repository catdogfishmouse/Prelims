#include "outlet.h" // including the file for image used in outlet

unsigned long previousT =0;

//for Oled
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#include <Wire.h> 
#include <SPI.h> 
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// for temperature
float temperature = 0;
String temp= "";
unsigned long currentT;
unsigned long tempT = 0;

//firealarm

#define buzzerpin 6
#define led_alarm 7

// for outlet
unsigned long outletT = 0;
unsigned long maintenanceimageT = 0;
unsigned long outlet_maintenanceT = 0;
#define outlet1 2
#define outlet2 3
#define outlet3 4
#define outletmaintenance 5
#define potentio A0
#define relay1 12
#define relay2 11
#define relay3 10


int outlet1state = 0;
int outlet2state = 0;
int outlet3state = 0;
int outlet_maintenance_state = 0;

bool workingoutlet1 = true;
bool workingoutlet2 = true;
bool workingoutlet3 = true;


// for exit

#define Ldrpin A1
float ldrval = 0;
unsigned long ldrT = 0;
unsigned long servoT = 0;
unsigned long buzzerT = 0;
#include <Servo.h>
Servo Exit_Door;
int person = 0;
  int oldperson = 0;


//for serial comms
int num_people = 0; //for ldr



void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { 
    Serial.println(F("SSD1306 allocation failed")); 
    for (;;); } 
  display.clearDisplay(); 
  display.drawRect(0,7,128,56,WHITE);
  display.drawLine(42, 8 , 42, 61, WHITE);
  display.drawLine(85, 8 , 85, 61, WHITE);
  display.drawBitmap(2, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
  display.drawBitmap(43, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
  display.drawBitmap(84, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
  display.display();

  //for outlet
  pinMode(outlet1,INPUT_PULLUP);
  pinMode(outlet2,INPUT_PULLUP);
  pinMode(outlet3,INPUT_PULLUP);
  pinMode(outletmaintenance,INPUT_PULLUP);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);

  // for firealarm
  pinMode(buzzerpin,OUTPUT);
  pinMode(led_alarm,OUTPUT);
  Serial.begin(9600);

  //for exit
  Exit_Door.attach(9);
  pinMode(Ldrpin,INPUT);
  Exit_Door.write(180);
}

void loop() {

  currentT = millis();


  if (Serial.available() > 0) {
    // Read data until newline
    temp = Serial.readStringUntil('\n');  
    temperature = temp.toFloat();  
    num_people = temp.toInt();
  }
  
  unsigned long ledalarmT = 0;
  int firealarmT = 0; 
  while(temperature > 70){
    currentT = millis();
    display.clearDisplay(); 
    display.setTextSize(1);              
    display.setTextColor(WHITE);
    display.setCursor(0, 26);  
    display.print("TEMPERATURE IS HIGH!");
    display.display();  
    tone(buzzerpin, 2000);
    Exit_Door.write(45);

    if (currentT - ledalarmT >= 500){
      digitalWrite(led_alarm,!digitalRead(led_alarm));
      firealarmT += 500;
      ledalarmT = currentT;

      if(firealarmT > 5000){
      digitalWrite(led_alarm,LOW);
      noTone(buzzerpin);
      num_people = 0;
      person = 0;
      temperature = 0;
      Serial.print(1); //for stop of servo and while loop
      Serial.println();
      delay(500);
      Serial.print(0); // for reset of system  
      Serial.println();
      break;
      }
    }
    
    
  }



  int buttonoutlet1 = digitalRead(outlet1);
  int buttonoutlet2 = digitalRead(outlet2);
  int buttonoutlet3 = digitalRead(outlet3);

  if ((buttonoutlet1 == 0 || buttonoutlet2== 0 || buttonoutlet3 == 0  ) && currentT - outletT >= 500){
  OUTLET(buttonoutlet1,buttonoutlet2,buttonoutlet3);
  outletT = currentT;
  }
  if(digitalRead(outletmaintenance) == 0 && currentT - outlet_maintenanceT >= 500) {
    outlet_maintenance_state = 1;
    int potenval = analogRead(potentio);
    int select = map(potenval,0,1023,0,4);
    Maintenance(select);
    outlet1state = 0;
    outlet2state = 0;
    outlet3state = 0;
    outlet_maintenanceT = currentT;
  }

  digitalWrite(relay1,!outlet1state);
  digitalWrite(relay2,!outlet2state);
  digitalWrite(relay3,!outlet3state);



  //for exit 

  ldrval = analogRead(Ldrpin);
  if(ldrval < 30 && currentT - ldrT >= 2000 && num_people == 3){
    Exit_Door.write(45);
    person++;
    if (person >= 5){
      num_people = 0;
      person = 0;
      Serial.print(0);
      Serial.println();
    }
    for (int i = 0; i < person + 1; i++ ){
      tone(buzzerpin,500);
      delay(50);
      noTone(buzzerpin);
      delay(50);
    }
    ldrT = currentT; 
    delay(2000);
  }else{
    Exit_Door.write(180);
  }
}


void OUTLET(int outletstate1,int outletstate2, int outletstate3){
  display.setTextSize(1); 

  if (outletstate1 == 0 && workingoutlet1) {

    if (outlet1state == 0){
      // on - outlet 1
      display.fillRect(2, 11, 39, 51, BLACK);  // Clear a pixel
      display.display();
      display.drawBitmap(2, 11, epd_bitmap_ONE_OUTLET, 39, 47, WHITE);
    }
    else{
      display.fillRect(2, 11, 39, 51, BLACK);  // Clear a pixel
      display.display();
      // off - outlet 1
      display.drawBitmap(2, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
    }
    outlet1state = !outlet1state;
  }

  if (outletstate2 == 0  && workingoutlet2) {
   
    if (outlet2state == 0) {
      // on - outlet 2
      display.fillRect(43, 11, 39, 51, BLACK);  // Clear a pixel
      display.display();
      display.drawBitmap(43, 11, epd_bitmap_ONE_OUTLET, 39, 47, WHITE);
    }
    else{
      display.fillRect(43, 11, 39, 51, BLACK);  // Clear a pixel
      display.display();
      // off - outlet 2
      display.drawBitmap(43, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
    }
     outlet2state = !outlet2state;
  }

  if (outletstate3 == 0 && workingoutlet3) {

    if (outlet3state == 0){
      display.fillRect(86, 11, 39, 51, BLACK);  // Clear a pixel
      display.display();
      // on - outlet 3
      display.drawBitmap(86, 11, epd_bitmap_ONE_OUTLET, 39, 47, WHITE);
    }
    else{
      display.fillRect(86, 11, 39, 51, BLACK);  // Clear a pixel
      display.display();
      // off - outlet 3
      display.drawBitmap(86, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
    }
    outlet3state = !outlet3state;
  }

  display.display();
}

void Maintenance(int select){

  switch(select){
    case 1:
      display.fillRect(2, 11, 39, 51, BLACK);  
      display.fillRect(43, 11, 39, 51, BLACK);
      display.fillRect(86, 11, 39, 51, BLACK);
      display.display();
      display.drawBitmap(2, 15, epd_bitmap_horizontal__dead_outlet, 39, 47, WHITE);
      display.drawBitmap(43, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.drawBitmap(86, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.display();
      workingoutlet1 = !workingoutlet1;
      workingoutlet2 = true;
      workingoutlet3 = true;
    break;

    case 2:
      display.fillRect(2, 11, 39, 51, BLACK);  
      display.fillRect(43, 11, 39, 51, BLACK);
      display.fillRect(86, 11, 39, 51, BLACK);
      display.display();
      display.drawBitmap(43, 15, epd_bitmap_horizontal__dead_outlet, 39, 47, WHITE);
      display.drawBitmap(2, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.drawBitmap(86, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.display();
      workingoutlet2 = !workingoutlet2;
      workingoutlet1 = true;
      workingoutlet3 = true;
    break;

    case 3:
      display.fillRect(2, 11, 39, 51, BLACK);  
      display.fillRect(43, 11, 39, 51, BLACK);
      display.fillRect(86, 11, 39, 51, BLACK);
      display.display();
      display.drawBitmap(86, 15, epd_bitmap_horizontal__dead_outlet, 39, 47, WHITE);
      display.drawBitmap(2, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.drawBitmap(43, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.display();
      workingoutlet3 = !workingoutlet3;
      workingoutlet2 = true;
      workingoutlet1 = true;
    break;

    default:
      display.clearDisplay();
      //display.display();
      display.drawRect(0,7,128,56,WHITE);
      display.drawLine(42, 8 , 42, 61, WHITE);
      display.drawLine(85, 8 , 85, 61, WHITE);
      display.drawBitmap(2, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.drawBitmap(43, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.drawBitmap(86, 11, epd_bitmap_outlet_off, 39, 47, WHITE);
      display.display();
       workingoutlet3 = true;
      workingoutlet2 = true;
      workingoutlet1 = true;
    break;
  }
}