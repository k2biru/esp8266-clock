#include "config.h"
#include "prototype.h"
#include "date.h"
#include <Arduino.h>


void _dateCoreCallback(coreCallbackCommand_e command){
    switch (command)
    {
    case CORE_TASK_INIT:
    DEBUG_DATE (PSTR("task init"));
        _dateInit();
        /* code */
        break;
    case CORE_TASK_LOOP:
        _dateLoop();
        /* code */
    
    default:
        break;
    }
}

void _dateTick(){
    uint32_t tmpTime = 0;
    _date.upTime++;
    if(!_date.ntpOk || _date.ntpForceSync){
        tmpTime = sntp_get_current_timestamp();//(NULL);
        if(_dateIsSNTPValid(tmpTime)){
            _date.ntpLastSync = tmpTime;
            _date.ntpForceSync = 0;
            _date.time = tmpTime;
            _date.ntpOk = 1;
            DEBUG_DATE_LV1(PSTR("SYNC"));
        }
    } else {
        _date.time ++;
        if(_date.time-_date.ntpLastSync >= 60*60*2){ // 2 hour resync
            _date.ntpForceSync = 1;
        }
    }
    DEBUG_DATE(PSTR("uptime %i, date %i, tmp %i"),_date.upTime,_date.time,tmpTime);
}

bool _dateIsSNTPValid(const time_t time){
  tm today;
  gmtime_r(&time, &today);
  return !(today.tm_year < (2020 - 1900)); 
}

void _dateSNTPInit(){
  sntp_setservername(0,"id.pool.ntp.org" );
  sntp_setservername(1,"0.id.pool.ntp.org" );
  sntp_setservername(2,"1.id.pool.ntp.org" );
  sntp_stop();  
  sntp_set_timezone(0);      // UTC time
  sntp_init();
  _date.time = 0;
//   _date.flagInitTime = 1;
//   _date.ntpInitDelay = 5;
  DEBUG_DATE(PSTR("Init SNTP"));
  _dateTicker.attach(1, _dateTick);
}
void _dateInit(){
}

void _dateLoop(){

}


void DateSetup(){
    CoreRegister(_dateCoreCallback);
    
    _dateSNTPInit();
}
