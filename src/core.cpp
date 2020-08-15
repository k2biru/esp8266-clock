#include "core.h"
#include "prototype.h"
#include "config.h"

extern "C" {
#include "lwip/opt.h"
#include "lwip/err.h"
#include "lwip/dns.h"
}

std::vector<coreCallback_f> _coreCallback;



void _coreCallbackCommand(coreCallbackCommand_e command){
	if (command != CORE_TASK_LOOP)    DEBUG_CORE(PSTR("cb Command %i"), (uint8_t) command);
	for (uint8_t i = 0; i < _coreCallback.size(); i++) {
    	(_coreCallback[i])(command);
    }
    
	if (command == CORE_TASK_INIT){
		_coreInit();
	}
}

void _coreInit(){
    WiFiManager wifiManager;
    wifiManager.setTimeout(180);
  wifiManager.setDebugOutput(0);
  DEBUG_CORE(PSTR("WIFI_INIT"))
  if(!wifiManager.autoConnect("ESP CLOCK")) {
    DEBUG_CORE(PSTR("WIFI_TIMEOUT"))
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  } 
  dns_setserver(0,IPAddress(1,1,1,1));

}

void CoreRegister(coreCallback_f callback) {
    _coreCallback.push_back(callback);
	DEBUG_CORE(PSTR("add calback %i"),_coreCallback.size());
}

void CoreSetup(){

    
    DEBUG_CORE(PSTR("Ready"));
    if(!_core.taskInit){
        _coreCallbackCommand(CORE_TASK_INIT);
        _core.taskInit = 1;
    }
    DEBUG_CORE(PSTR("Init Error %i"),_core.taskInit);

}

void CoreLoop(){
    _coreCallbackCommand(CORE_TASK_LOOP);
    
	uint32_t now = millis();
	if (now - _core.timer10second > CORE_TASK_10_SEC_MS){
    	_core.timer10second = now;
		_coreCallbackCommand(CORE_TASK_10_SEC);
		ESP.wdtFeed();
	}
	if (now - _core.timer15second > CORE_TASK_15_SEC_MS){
    	_core.timer15second = now;
		_coreCallbackCommand(CORE_TASK_15_SEC);
		ESP.wdtFeed();
	}
	if (now - _core.timer1minute > CORE_TASK_1_MINUTE_MS){
		_core.timer1minute = now;
		_coreCallbackCommand(CORE_TASK_1_MINUTE);
		ESP.wdtFeed();
	}
	
	ESP.wdtFeed();
}
