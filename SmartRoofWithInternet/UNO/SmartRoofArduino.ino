#include "config.h"
#include "stepper_control.h"
#include "sensor.h"
#include "communication.h"

// Global variables
Stepper myStepper(stepsPerRevolution, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);
SoftwareSerial espSerial(ESP_RX, ESP_TX);
unsigned long time_ss = 0;
int command = 0;

void setup() {
  // Khởi tạo Serial giao tiếp với máy tính
  Serial.begin(9600);
  
  // Cài đặt chân input
  pinMode(LIMIT_OPEN, INPUT);
  pinMode(LIMIT_CLOSE, INPUT);
  
  // Khởi tạo giao tiếp với ESP8266
  setupCommunication();
  
  // Khởi tạo động cơ stepper và đóng mái che
  initializeStepper();
}

void loop() {
  // Gửi dữ liệu cảm biến mỗi 2.5 giây
  if ((unsigned long)(millis() - time_ss) > 2500) {
    int sensorValue = readRainSensor();
    sendSensorData(sensorValue);
    time_ss = millis();
  }
  
  // Nhận lệnh từ ESP8266
  command = receiveCommand();
  
  // Xử lý lệnh
  if (command == CMD_OPEN_ROOF) {
    openRoof();
    command = 0;
  }
  else if (command == CMD_CLOSE_ROOF) {
    closeRoof();
    command = 0;
  }
}