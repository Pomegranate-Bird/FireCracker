const int led1 = 18;
const int led2 = 17;

void set_led(){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}


void blink(){
  digitalWrite(led1, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  delay(500);
  digitalWrite(led2, HIGH);
  delay(500);
  digitalWrite(led2, LOW);
  delay(500);
}