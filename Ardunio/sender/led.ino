const int led1 = 13;

// Pin 13 
void set_led(){
  pinMode(led1, OUTPUT);

}


void blink(){
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  delay(500);

}