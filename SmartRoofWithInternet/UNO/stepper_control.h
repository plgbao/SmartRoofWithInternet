#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

#include <Stepper.h>
#include "config.h"

extern Stepper myStepper;

// Function declarations
void initializeStepper();
void openRoof();
void closeRoof();

// Function implementations
void initializeStepper() {
  // Set the speed of the stepper motor (rpm)
  myStepper.setSpeed(60);
  
  // Close the roof initially for calibration
  while (digitalRead(LIMIT_CLOSE) == 1) {
    Serial.println("ĐANG ĐÓNG MÁI CHE");
    myStepper.step(stepsPerRevolution);
  }
  Serial.println("ĐÃ ĐÓNG MÁI CHE");
}

void openRoof() {
  while (digitalRead(LIMIT_OPEN) == 1) {
    Serial.println("ĐANG MỞ MÁI CHE");
    myStepper.step(-stepsPerRevolution);
  }
  Serial.println("ĐÃ MỞ MÁI CHE");
}

void closeRoof() {
  while (digitalRead(LIMIT_CLOSE) == 1) {
    Serial.println("ĐANG ĐÓNG MÁI CHE");
    myStepper.step(stepsPerRevolution);
  }
  Serial.println("ĐÃ ĐÓNG MÁI CHE");
}

#endif // STEPPER_CONTROL_H