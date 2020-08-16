#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include "prototype.h"
#include "config.h"

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  while (!Serial){
    delay(100);
  }
  DateSetup();
  CoreSetup();
  // put your setup code here, to run once:
}

void loop() {
  CoreLoop();
  // put your main code here, to run repeatedly:
}