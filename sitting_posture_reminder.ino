#include <SevenSegmentTM1637.h>

SevenSegmentTM1637  display(2, 3);

volatile int item;

float checkdistance_A1_A0() {
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  float distance = pulseIn(A0, HIGH) / 58.00;
//    delay(10);
  return distance;
}


void setup() {
  display.begin();
  item = 0;
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(4, OUTPUT); 


void loop() {
  item = checkdistance_A1_A0();

  if (item > 100) {
    item = 100;
  }
  Serial.write(item);
//    delay(item*5);

  if (item >= 0 && item <= 99) {
    display.print(String((item / 10)) + String(((long) (item) % (long) (10))) + "CM" );
  } else {
    display.print("    ");
    delay(10);
    display.clear();
  }

  if (item <= 40) {
    digitalWrite(4, HIGH);
    delay(item * 5);
    digitalWrite(4, LOW);
    delay(item * 5);
    
    //    tone(4, 3000 / item, item*7);
    //    digitalWrite(4,LOW);
    //    delay(item*10);
  } else {
    digitalWrite(4, LOW);
  }
}
