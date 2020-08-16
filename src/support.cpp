#include "support.h"
#include "prototype.h"
#include "config.h"

void DebugFormat(uint8_t data, PGM_P format_P, ...) {
#if !DEBUG_DISABLE_ALL
	uint32_t time = millis();
#if !DEBUG_DISABLE_SERIAL
	char prefix[4];
    switch(data){
        case 1:
            strcpy_P(prefix,PSTR("CORE"));
            break;
        case 2:
            strcpy_P(prefix,PSTR("INFO"));
            break;
        case 3:
            strcpy_P(prefix,PSTR("DATE"));
            break;
        default :
            strcpy_P(prefix,PSTR("----"));
            break;
    }
#endif
	char format[strlen_P(format_P)+1];
    memcpy_P(format, format_P, sizeof(format));

    va_list args;
    va_start(args, format_P);
    char test[1];
    int len = ets_vsnprintf(test, 1, format, args) + 1;
    char * buffer = new char[len];
    ets_vsnprintf(buffer, len, format, args);
    va_end(args);

	// if(data==0) MQTTPublishC_str((MQTTPrefix()+F(MQTT_TOPIC_P_DEBUG)).c_str(),buffer,RETRAIN_FALSE);
#if !DEBUG_DISABLE_SERIAL
	Serial.printf("%07u.%03u:[%s] %s \n",time / 1000, time % 1000, prefix,buffer);
#endif
    delete[] buffer;
#endif // DEBUG_DISABLE_ALL
}