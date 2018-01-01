#include "mqtt_msg_processor.h"

namespace Networking {
namespace Mqtt {


const std::array<String, Message_Processor::const_topicCount> &Message_Processor::getSubscriptions() const
{
    return _config.subscribed_topics;
}

Message_Processor::Message_Processor(const Configuration_Message_Processor &config,
                                     Scheduler &manager,
                                     ProcPriority priority,
                                     uint32_t period,
                                     int iterations,
                                     uint16_t overSchedThresh)
    :Process (manager, priority, period, iterations, overSchedThresh), _config(config)
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
