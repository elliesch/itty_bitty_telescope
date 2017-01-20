/*
  Ellianna Schwab - Advanced Lab 1 - Professor Mark Shattuck - Final Project Part C
  This code runs two stepper motors from a single ITEAD bridge.
*/

//initialize pins to drive the motors
int dirPin1 = 3;
int stepperPin1 = 2;
int dirPin2 = 7;
int stepperPin2 = 6;

boolean obs_val = false;
char read_val = 0;

//specify parameters for the observation
const int obs_time = 15000; // 15s in millis, 1.8e6 for 30 minutes
const int Degrees_Az = 25;
const int Degrees_Alt = 10;

void setup() {
  pinMode(dirPin1, OUTPUT);
  pinMode(stepperPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepperPin2, OUTPUT);
}

void Az_step(boolean dir, int steps) {
  digitalWrite(dirPin2, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin2, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepperPin2, LOW);
    delayMicroseconds(100);
  }
}

void Alt_step(boolean dir, int steps) {
  digitalWrite(dirPin1, dir);
  delay(50);
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepperPin1, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepperPin1, LOW);
    delayMicroseconds(100);
  }
}

void loop() {

  if (Serial.available() > 0) { //this code requires that I type 1 into serial monitor when I'm ready to start
    read_val = Serial.read();
    Serial.println(read_val);
    if (read_val == '1') {
      obs_val = !obs_val;
    }
  }

  //the following code steps the telescope forward
  Az_step(true, 19 * Degrees_Az);
  delay(500);
  Az_step(false, 19 * Degrees_Az);
  delay(500);

  Alt_step(true, 13 * Degrees_Alt); //this should have been more like 8.3, so not exact
  delay(500);
  Alt_step(false, 13 * Degrees_Alt);
  delay(500);

  delay(obs_time);

  //the following code steps the telescope backward
  Az_step(true, -19 * Degrees_Az);
  delay(500);
  Az_step(false, -19 * Degrees_Az);
  delay(500);

  Alt_step(true, -13 * Degrees_Alt); //this should have been more like 8.3, so not exact
  delay(500);
  Alt_step(false, -13 * Degrees_Alt);
  delay(500);

  obs_val = !obs_val; //this ends the code after one observation

}




