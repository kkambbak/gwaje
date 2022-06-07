#include <Arduino.h>
#include <Ticker.h>
 
// attach a LED to pPIO 32,33
#define LED_PIN 32
#define LED_PIN 33
 
Ticker blinker1;
Ticker blinker2;
float blinkerPace1 = 0.5;  //seconds
float blinkerPace2 = 1.0;
 
 
void blink1() {
  digitalWrite(LED_PIN1, !digitalRead(LED_PIN1));
}
void blink2() {
  digitalWrite(LED_PIN2, !digitalRead(LED_PIN2));
}
  
void setup() {
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  blinker1.attach(blinkerPace1, blink1);
  blinker2.attach(blinkerPace2, blink2);
}
 
void loop() {
}
 
    
