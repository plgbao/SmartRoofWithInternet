#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "data_structures.h"

extern ESP8266WebServer server;

// HTML generation for the main page
String generateHTML() {
  String html = "<html><head>";
  html += "<meta http-equiv='refresh' content='3.5'>";  // Auto refresh every 3.5 seconds
  html += "<link href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css' rel='stylesheet'>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; background-color: #f4f4f9; color: #333; text-align: center; margin-top: 50px;}";
  html += "h1 { color: #4CAF50; font-size: 48px; }";                               // Increase h1 font size
  html += "p { font-size: 28px; }";                                                // Increase paragraph font size
  html += "p.rain-value { font-size: 48px; font-weight: bold; color: #FF5722; }";  // Bigger font for Rain Sensor Value
  html += "button { font-size: 28px; padding: 15px 30px; background-color: #4CAF50; color: white; border: none; border-radius: 10px; cursor: pointer; margin: 10px;}";
  html += "button:hover { background-color: #45a049; }";
  html += "p.icon { font-size: 60px; color: #ff6347; }";  // Increase icon size
  html += "</style>";
  html += "</head><body>";

  html += "<h1>SMART ROOF</h1>";
  html += "<p class='rain-value'>Rain Sensor Value: " + String(rainValue) + "</p>";  // Bigger font for Rain Sensor Value
  if (rainValue > 35) {
    html += "<p class='icon'><i class='fas fa-cloud-rain'></i> Warning: Rain detected</p>";
  } else {
    html += "<p class='icon'><i class='fas fa-sun'></i> No rain</p>";
  }

  // Display IP address
  html += "<p>ESP8266 IP address: " + WiFi.localIP().toString() + "</p>";

  // Roof control buttons with icons
  html += "<p><a href='/open'><button><i class='fas fa-arrow-up'></i> Open Roof</button></a></p>";
  html += "<p><a href='/close'><button><i class='fas fa-arrow-down'></i> Close Roof</button></a></p>";

  html += "</body></html>";
  
  return html;
}

// Web server route handlers
void handleRoot() {
  server.send(200, "text/html", generateHTML());
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { 
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; 
  }
  server.send(404, "text/plain", message);
}

// Setup web server routes
void setupWebServer() {
  server.on("/", handleRoot);
  
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  
  server.on("/open", HTTP_GET, openRoof);
  server.on("/close", HTTP_GET, closeRoof);
  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

#endif // WEBSERVER_H