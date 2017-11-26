char keypadPin = A3;
int analog[17] = {928, 910, 893, 876, 852, 837, 823, 808, 788, 775, 762, 750, 732, 721, 710, 699, 0};
char key[17] =  {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D', 'N'}; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(keypadPin);
  /*Serial.println(value);
  delay(100);*/   
  for(int i=0; i<16; i++){
    if(abs(value - analog[i]) < 5){
      Serial.println(key[i]);
      while(analogRead(keypadPin) > 0){
        delay(100);  
      }
    } 
  }
}
