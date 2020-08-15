#ifndef CORE_H
#define CORE_H

#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

struct _core_t{
    union {
        struct {
			bool taskInit :1;
        };
        uint8_t flag = 0U;
    };
	uint32_t timer1minute = 0U;
	uint32_t timer15second = 0U;
	uint32_t timer10second = 0U;
	// uint32_t timer10minute;
} _core;

void _coreInit();

#endif //CORE_H