#include "blink_process.h"

#include <Arduino.h>

Blink_Process::Blink_Process(const Configuration_Message_Processor &config,
                             Scheduler &manager,
                             ProcPriority priority,
                             uint32_t period, // ms
                             int iterations,
                             uint16_t overSchedThresh) :
    Networking::Mqtt::Abstract_Message_Processor(config, manager, priority, period, iterations,  overSchedThresh)
{
    Serial.println("Blink_Process ctor");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

Blink_Process::~Blink_Process()
{
    Serial.println("Blink_Process dtor");
}

void Blink_Process::service()
{
    bool led = digitalRead(BUILTIN_LED);
    digitalWrite(BUILTIN_LED, !led);
}

void Blink_Process::cleanup()
{
    digitalWrite(BUILTIN_LED, HIGH);
}

uint32_t getPeriodFromBuf(uint8_t *payload, unsigned int length)
{
    String msg;
    for(unsigned int ctr = 0; ctr < length; ctr++)
    {
        msg += static_cast<char>(payload[ctr]);
    }
    auto peri = static_cast<uint32_t>(atol(msg.c_str()));
    return peri;
}

void Blink_Process::processMessage(String topic, uint8_t *payload, unsigned int length)
{
    topic = "";
    auto peri = getPeriodFromBuf(payload, length);
    if(peri < 10)
    {
        destroy();
    }
    else
    {
        if(isNotDestroyed() == false)
        {
            add(true);
        }

        if(!isEnabled())
        {
            enable();
        }
        this->setPeriod(peri);
    }
}
