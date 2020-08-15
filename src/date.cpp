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
    _date.upTime++;
    
    if(!_date.flagInitTime) return; // not yet

    
    if (!_dateIsSNTPValid(time(NULL))){
        _dateSNTPInit();
        for(uint8_t i=0; i<10; i++)  {
            delay(50);
            _date.time = time(NULL);
        }    
    } else {
        _date.time ++;
        DEBUG_DATE(PSTR("invalid time"));
    }
    DEBUG_DATE(PSTR("uptame %i, date %i"),_date.upTime,_date.time);
}

bool _dateIsSNTPValid(const time_t time){
  tm today;
  gmtime_r(&time, &today);
  if (today.tm_year < (2020 - 1900))  return false;// tahun kurang dari 2017
  else return true;
}

void _dateSNTPInit(){
  char server0 [16] ;
  char server1 [18] ;
  char server2 [18] ;
  strcpy_P(server0, PSTR("id.pool.ntp.org"));
  strcpy_P(server1, PSTR("0.id.pool.ntp.org"));
  strcpy_P(server2, PSTR("1.id.pool.ntp.org"));
  configTime(0, 0, server0,server1,server2);
  _date.flagInitTime = 1;
  DEBUG_DATE(PSTR("Init SNTP"));
}
void _dateInit(){
    _dateSNTPInit();
}

void _dateLoop(){

}


void DateSetup(){
    CoreRegister(_dateCoreCallback);
    _dateTicker.attach(1, _dateTick);
}
