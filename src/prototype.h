#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <Arduino.h>


enum coreCallbackCommand_e{
  CORE_RTC_MEMORY_LOAD ,
  CORE_RTC_MEMORY_SAVE , 
  CORE_TASK_10_SEC,
  CORE_TASK_15_SEC,
  CORE_TASK_1_MINUTE,
  CORE_TASK_INIT,
  CORE_TASK_LOOP 
  // CORE_TASK_10_MINUTE 
  // CORE_PRE_RESTART
};

typedef std::function<void(coreCallbackCommand_e command)> coreCallback_f;

// Support API
void DebugFormat(uint8_t data, PGM_P format_P, ...); 

// Core API
void CoreSetup();
void CoreLoop();
void CoreRegister(coreCallback_f callback);

#endif // PROTOTYPE_H