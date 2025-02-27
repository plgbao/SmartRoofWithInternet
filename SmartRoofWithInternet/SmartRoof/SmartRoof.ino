#include "config.h"
#include "data_structures.h"
#include "webserver.h"
#include "roof_control.h"

// Global variable definitions
ESP8266WebServer server(80);
WiFiClient client;
int rainValue = 0;
bool openState = false;
int blink = 0;
int statusCode;
unsigned long time_ss;

void setup(void) {
  Serial.begin(9600);
  
  // Initialize WiFi
  setupWiFi();
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
  
  // Initialize MDNS
  if (MDNS.begin("esp8266")) { 
    Serial.println("MDNS responder started"); 
  }
  
  // Setup web server
  setupWebServer();
}

void loop(void) {
  // Check for serial data (rain sensor)
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    rainValue = msg.toInt();
  }
  
  // Handle client requests
  server.handleClient();
  MDNS.update();
  
  // 1-second timer
  if ((unsigned long)(millis() - time_ss) > 1000) {
    time_ss = millis();
  }
  
  // ThingSpeak communication timer
  if ((millis() - lastTime) > timerDelay) {
    switch (blink) {
      case 0:
        blink = 1;
        // Read data from ThingSpeak
        int count = ThingSpeak.readIntField(myChannelNumber, 2, myReadAPIKey);
        statusCode = ThingSpeak.getLastReadStatus();
        break;

      case 1:
        blink = 0;
        // Send rain value to ThingSpeak
        statusCode = ThingSpeak.writeField(myChannelNumber, 1, rainValue, myWriteAPIKey);
        break;
        
      case 2:
        blink = 0;
        // Update open state (1) to ThingSpeak
        statusCode = ThingSpeak.writeField(myChannelNumber, 2, 1, myWriteAPIKey);
        break;
        
      case 3:
        blink = 0;
        // Update closed state (0) to ThingSpeak
        statusCode = ThingSpeak.writeField(myChannelNumber, 2, 0, myWriteAPIKey);
        break;
    }

    lastTime = millis();
  }
}