#ifndef MDEBUG_H
#define MDEBUG_H

#include <Arduino.h>

#define START Serial.println(String(__FILE__) + "(" + __LINE__ + ") -->" + __func__ + " START")
#define END Serial.println(String(__FILE__) + "(" + __LINE__ + ") -->" + __func__ + " END")
#define HERE Serial.println(String(__FILE__) + "(" + __LINE__ + ") -->" + __func__)

namespace mDebug
{
    void printDebug(const String &msg);
};

#endif // MDEBUG_H
