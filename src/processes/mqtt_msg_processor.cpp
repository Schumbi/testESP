#include "mqtt_msg_processor.h"

Mqtt_msg_Processor::Mqtt_msg_Processor(Scheduler &manager,
                                                   ProcPriority priority,
                                                   uint32_t period,
                                                   int iterations,
                                                   uint16_t overSchedThresh)
    :Process (manager, priority, period, iterations, overSchedThresh)
{

}

Mqtt_msg_Processor::~Mqtt_msg_Processor()
{

}

void Mqtt_msg_Processor::processMqttMessages(char *topic, uint8_t *payload, unsigned int length)
{
    Serial.println(topic);
    String msg;
    for(unsigned int ctr = 0; ctr < length; ctr++)
    {
        msg += static_cast<char>(payload[ctr]);

    }
    Serial.println(msg);
}

void Mqtt_msg_Processor::service()
{
    ;
}
