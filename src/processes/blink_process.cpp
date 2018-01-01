#include "blink_process.h"

#include <Arduino.h>

Blink_Process::Blink_Process(Scheduler &manager,
                             ProcPriority priority,
                             uint32_t period,
                             int iterations,
                             uint16_t overSchedThresh) :
    Process(manager, priority, period, iterations,  overSchedThresh)
{
    Serial.println("Blink_Process ctor");
    pinMode(LED_BUILTIN, OUTPUT);
}

Blink_Process::~Blink_Process()
{
    Serial.println("Blink_Process dtor");
}

void Blink_Process::service()
{
    //Serial.printf("Blink_Process service %d (%d)\n", getID(), getPeriod());
    bool led = digitalRead(BUILTIN_LED);
    digitalWrite(BUILTIN_LED, !led);
}
