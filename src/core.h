#ifndef CORE_H
#define CORE_H

#include "prototype.h"
#include "config.h"
#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>

#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>         //https://github.com/tzapu/WiFiManager

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

AsyncWebServer server(80);
DNSServer dns;
std::vector<coreCallback_f> _coreCallback;

void _coreCallbackCommand(coreCallbackCommand_e command);
void _coreWiFiConfig();
void _coreInit();

#endif //CORE_H