#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions
#define LIMIT_OPEN 2      // Công tắc hành trình khi mái nhà mở hoàn toàn
#define LIMIT_CLOSE 3     // Công tắc hành trình khi mái nhà đóng hoàn toàn
#define SENSOR A5         // Cảm biến mưa

// Stepper motor configuration
const int STEPPER_PIN1 = 9;
const int STEPPER_PIN2 = 10;
const int STEPPER_PIN3 = 11;
const int STEPPER_PIN4 = 12;
const int stepsPerRevolution = 200;  // Số bước cho một vòng quay

// ESP8266 communication pins
#define ESP_RX A4         // Pin kết nối với TX của ESP8266
#define ESP_TX A3         // Pin kết nối với RX của ESP8266

// Command codes
#define CMD_OPEN_ROOF 1123
#define CMD_CLOSE_ROOF 1124

#endif // CONFIG_H