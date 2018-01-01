#include "mDebug.h"

namespace  {

void printDebug(const String &msg)
{
    if(Serial.isTxEnabled())
    {
        Serial.println(msg);
    }
}

}
