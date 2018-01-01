#include "mqtt_msg_processor.h"

#include <PubSubClient.h>

namespace Networking {
namespace Mqtt {

const std::array<String, Abstract_Message_Processor::const_topicCount> &Abstract_Message_Processor::getSubscriptions() const
{
    return _config.subscribed_topics;
}

Abstract_Message_Processor::Abstract_Message_Processor(const Configuration_Message_Processor &config,
                                     Scheduler &manager,
                                     ProcPriority priority,
                                     uint32_t period,
                                     int iterations,
                                     uint16_t overSchedThresh)
    :Process (manager, priority, period, iterations, overSchedThresh), _config(config)
{
    destroy();
}

void Abstract_Message_Processor::mqttMessageCallback(char *topic, uint8_t *payload, unsigned int length)
{
    for(auto it = _config.subscribed_topics.begin(); it != _config.subscribed_topics.end(); it++)
    {
        if(String(topic) == *it)
        {
            processMessage(String(topic), payload, length);
            return;
        }

    }
//    Serial.println(topic);
//    String msg;
//    for(unsigned int ctr = 0; ctr < length; ctr++)
//    {
//        msg += static_cast<char>(payload[ctr]);

//    }
//    Serial.println(msg);
}

Abstract_Message_Processor::~Abstract_Message_Processor()
{}

}}


void Networking::Mqtt::Abstract_Message_Processor::service()
{
}

void Networking::Mqtt::Abstract_Message_Processor::setup()
{
}

void Networking::Mqtt::Abstract_Message_Processor::cleanup()
{
}

void Networking::Mqtt::Abstract_Message_Processor::onEnable()
{
}

void Networking::Mqtt::Abstract_Message_Processor::onDisable()
{
}

void Networking::Mqtt::Abstract_Message_Processor::handleWarning(ProcessWarning warning)
{
}
