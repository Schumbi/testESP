#include "mqtt_msg_processor.h"

namespace Networking {
namespace Mqtt {

Message_Processor::Message_Processor(Scheduler &manager,
                                     ProcPriority priority,
                                     uint32_t period,
                                     int iterations,
                                     uint16_t overSchedThresh)
    :Process (manager, priority, period, iterations, overSchedThresh)
{

}

Message_Processor::~Message_Processor()
{

}

void Message_Processor::processMqttMessages(char *topic, uint8_t *payload, unsigned int length)
{
    Serial.println(topic);
    String msg;
    for(unsigned int ctr = 0; ctr < length; ctr++)
    {
        msg += static_cast<char>(payload[ctr]);

    }
    Serial.println(msg);
}

void Message_Processor::service()
{
    ;
}

}}
