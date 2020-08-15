#ifndef CONFIG_H
#define CONFIG_H

#define  SERIAL_BAUDRATE            115200


#define CORE_TASK_15_SEC_MS             15000  // 15 sec
#define CORE_TASK_10_SEC_MS             10000  // 10 sec    
#define CORE_TASK_1_MINUTE_MS           60000  // 1 mnt     
// #define CORE_TASK_5_MINUTE_MS           60000  // 1 mnt    


#define DEBUG_CORE(...)              DebugFormat(1,__VA_ARGS__);
#define DEBUG_CORE_LV1(...)          DebugFormat(1,__VA_ARGS__);
#define DEBUG_INFO(...)              DebugFormat(2,__VA_ARGS__);
#define DEBUG_INFO_LV1(...)          DebugFormat(2,__VA_ARGS__);


#ifndef DEBUG_CORE
#define DEBUG_CORE(...)
#endif  //DEBUG_CORE(...)

#ifndef DEBUG_CORE
#define DEBUG_CORE_LV1(...)
#endif  //DEBUG_CORE(...)

#ifndef DEBUG_INFO
#define DEBUG_INFO(...)
#endif  //DEBUG_CORE(...)

#ifndef DEBUG_INFO_LV1
#define DEBUG_INFO_LV1(...)
#endif  //DEBUG_CORE(...)


#endif //CONFIG_H