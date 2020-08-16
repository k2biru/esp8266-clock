#include "config.h"
#include "prototype.h"
#include <Arduino.h>
extern "C" {
#include <user_interface.h>
#include <sntp.h>
}
#include <Ticker.h>
// #include <time.h>    


struct date_t
{
  union {
      struct 
      {
        bool ntpOk:1;
        bool alarmLoadOK:1;
        bool flagInitTime:1 ;
        bool ntpCustom:1 ;
        bool ntpForceSync:1;
        // bool flagLoadSchedule ;
      };
    uint8_t flag;
  };
  time_t time; //  time right now (epoch)
  time_t ntpLastSync;
  uint32_t lastGetT;
  uint32_t upTime = 0;
  uint8_t ntpForceTimer;
  uint8_t lastMinute;
  uint8_t ntpInitDelay =0;
  uint8_t lastDayOfWeek = 0xFF;  
}_date;

Ticker _dateTicker;
void ClockSetup();
void _dateCoreCallback(coreCallbackCommand_e command);
void _dateLoop();
void _dateInit();
void _dateSNTPInit();
void _dateTick();
bool _dateIsSNTPValid(const time_t time);