#include <Wire.h>
#include <AnalogKeypad.h>
//#include <LiquidCrystal_I2C.h>
//#include <Keypad.h>
#define buzzer 4
#define redLed 5
#define trigPin 2
#define echoPin 3
#define COUNTDOWN 12
#define WARNING 12
long duration;
int distance;
int initialDistance; 
int currentDistance; 
int i;
int countdown = 0;
int warning = 0;
int message = 0;
int text = 0;
String password = "1234";
String tempPassword;
boolean activated;
boolean activeAlarm = false;
//boolean passChangeMode = false;
//boolean passChanged = false;
boolean danger;
boolean deactivate = false;
boolean back = false;
boolean activateMessage = false;
boolean warningMessage = false;
boolean alarmMessage = false;
boolean cancelMessage = false;
int ledState = LOW;
unsigned long ledPrevious = 0;
unsigned long ledCurrent;
const long ledInterval = 50;
unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 1000;
char keypressed;
//const byte ROWS = 4;
//const byte COLS = 4;
/*char keyMap[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};*/
//byte rowPins[ROWS] = {13, 12, 11, 10}; 
//byte colPins[COLS] = {9, 8, 7, 6};

//Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS); 
AnalogKeypad analogKeypad(A0);
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

void setup(){ 
  Serial.begin(9600);
  lcd.begin(16,2); 
  pinMode(buzzer, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(redLed, OUTPUT);
}

void loop(){
    keypressed = analogKeypad.analogKeypressed();
    //keypressed = myKeypad.getKey();
    warningMessage = false;
    alarmMessage = false;
    cancelMessage = false; 
    activateMessage = true;
    activeAlarm = true;    
    if (message == 0 ){
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("ACTIVATE ALARM");           
      message = 1;         
    }
    enterPassword();
       
    /*if (keypressed == 'A'){    
      //tone(buzzer, 1000, 200);
      //activateAlarm = true;
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("ACTIVATE");
      warningMessage = false;
      alarmMessage = false;
      cancelMessage = false; 
      activateMessage = true;
      back = false;
      enterPassword();
      if(back == false){
        activateAlarm(); 
      }                
    }*/
  /*delay(300);
  Serial.print(distance);
  Serial.print(" cm ");
  Serial.println();
  delay(100);*/
  //Serial.println(keypressed);
}

void activateAlarm(){
  activeAlarm = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ACTIVATING");
  lcd.setCursor(0,1);
  lcd.print("C - CANCEL");  
  countdown = COUNTDOWN;   
  while (countdown != 0-1){
    currentMillis = millis();
    keypressed = analogKeypad.analogKeypressed(); 
    if(keypressed == 'C'){
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("CANCEL");
      warning = 0-1;
      activateMessage = false;
      warningMessage = false;
      alarmMessage = false;
      cancelMessage = true;       
      back = true;
      deactivate = true; 
      enterPassword();
      return;
    }  
    if (currentMillis - previousMillis >= interval){               
      previousMillis = currentMillis;
      lcd.setCursor(12,0);
      lcd.print(countdown);
      lcd.print(" ");
      tone(buzzer, 700, 100);
      countdown--;   
    } 
  }    
  alarmCheck();
}

void alarmCheck(){ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ALARM ACTIVATED!");
  tone(buzzer, 1000, 100);
  initialDistance = getDistance();
  danger = false;
  back = false;
  while(danger == false){      
    currentDistance = getDistance() + 10;
    if (currentDistance < initialDistance){
      danger = true;
      warning = WARNING;
      while(warning != 0-1){
        if(message == 0){
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print("WARNING");  
          message = 1;
        }
        activateMessage = false;
        alarmMessage = false;
        cancelMessage = false; 
        warningMessage = true; 
        deactivate = true;
        enterPassword();
      }
      alarmActivated();
    }     
  }
}

void alarmActivated(){
  warning = WARNING;
  countdown = COUNTDOWN;
  deactivate = false;
  if(text == 0){
    lcd.clear();
    lcd.setCursor(0,0);      
    lcd.print(" *** ALARM *** ");
    text = 1;       
  }
  tone(buzzer, 1000);
  digitalWrite(redLed, HIGH);
  activateMessage = false;
  warningMessage = false; 
  cancelMessage = false;
  alarmMessage = true;
  enterPassword();
}


// Custom function for the Ultrasonic sensor
long getDistance(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;
  return distance;
}

void ledBlink(){
  ledCurrent = millis();
  if (ledCurrent - ledPrevious >= ledInterval){
    ledPrevious = ledCurrent;
    if (ledState == LOW){
      ledState = HIGH;
    } 
    else{
      ledState = LOW;
    }
    digitalWrite(redLed, ledState);
  }    
} 

void enterPassword(){
  int attempt = 3;
  int k=9;
  tempPassword = "";
  activated = true;
  lcd.setCursor(0,1);
  lcd.print("Password:");
  while(activated){
    while(warning != 0-1 || countdown != 0-1){
      keypressed = analogKeypad.analogKeypressed();
      if(deactivate == true){
        currentMillis = millis();       
        if (currentMillis - previousMillis >= interval){           
          previousMillis = currentMillis;
          if(back == true){
            lcd.setCursor(12,0);
            lcd.print(countdown);
            lcd.print(" ");
            tone(buzzer, 700, 100);       
            countdown--;  
          }
          else{
            ledBlink();
            lcd.setCursor(13,0);
            lcd.print(warning);
            lcd.print(" ");
            tone(buzzer, 700, 100);
            warning--;  
          }   
        }
      }  
      if (keypressed != 'N'){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ){
          tempPassword += keypressed;
          lcd.setCursor(k,1);
          lcd.print("*");
          if(alarmMessage == false){
            tone(buzzer, 500, 100);
          }
          k++;
        }
      }
      if (k > 13 || keypressed == 'C'){
        k=9;
        tempPassword = "";    
        lcd.clear();
        tone(buzzer, 600, 100);
        if(activateMessage == true){
          lcd.setCursor(1,0);
          lcd.print("ACTIVATE ALARM");
        }          
        else if(warningMessage == true){
          lcd.setCursor(4,0);
          lcd.print("WARNING");
        }
        else if(alarmMessage == true){
          lcd.setCursor(0,0);
          lcd.print(" *** ALARM *** ");
        }
        else if(cancelMessage == true){
          lcd.setCursor(5,0);
          lcd.print("CANCEL");
        }
        lcd.setCursor(0,1);
        lcd.print("Password:");
      }
      if (keypressed == '*'){
        if (tempPassword == password){
          deactivate = false;
          activated = false;
          message = 0; 
          text = 0;
          if(activeAlarm == true){
            activateAlarm();        
          }
          else{    
            noTone(buzzer);
            digitalWrite(redLed, LOW);    
            lcd.clear();
            lcd.setCursor(2,0);
            lcd.print("DEACTIVATED");
            delay(2000);
            loop();
            return;
          }
        }
        else if (tempPassword != password){        
          k=9;
          tempPassword = "";
          attempt--;
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print("WRONG!");
          if(activateMessage == false && alarmMessage == false){
            lcd.setCursor(0,1);
            lcd.print("ATTEMPTS:");
            lcd.setCursor(10,1);
            lcd.print(attempt);  
            if(attempt == 0){
              alarmActivated();
            }
          }     
          delay(2000);
          lcd.clear();          
          if(activateMessage == true){
            lcd.setCursor(1,0);
            lcd.print("ACTIVATE ALARM");
          }      
          else if(warningMessage == true){
            lcd.setCursor(4,0);
            lcd.print("WARNING");
          }      
          else if(alarmMessage == true){
            lcd.setCursor(0,0);
            lcd.print(" *** ALARM *** ");
          }
          else if(cancelMessage == true){
            lcd.setCursor(5,0);
            lcd.print("CANCEL");
          }
          lcd.setCursor(0,1);
          lcd.print("Password:");
        }
      }    
    }
    if(back == true){
      alarmCheck();
    }
    else{
      alarmActivated();
    }    
  }
}
