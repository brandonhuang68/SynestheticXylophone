#include <SXMotor.h>


const int cwPin = 12;
const int ccwPin = 11;
const int speedPin = 10;
const int sensorPin = A0;
SXMotor motor(speedPin, cwPin, ccwPin, sensorPin);
int minVal = 1000;
int maxVal = 0;


void setup() {
  Serial.begin(9600);
  motor.calibrate(175); // 9V base
  delay(1000);
}
int i = 0;
void loop() {
    while (i < 5) {
      motor.moveUntilLight(175);
      delay(1000);
      Serial.println("DONE ==========");
      i++;
    }
//  motor.move(175);
// while (i < 1) {
//   motor.move(150);
//   int reading = analogRead(sensorPin);
//   Serial.println(reading);
//   while(reading < 90) {
//    reading = analogRead(sensorPin);
//    Serial.println(reading);
//    motor.move(255);
//   }
//   i++;
// }
// motor.move(0);
}
