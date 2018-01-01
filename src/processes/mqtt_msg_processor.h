#ifndef MESSAGEPROCESSOR_PROCESS_H
#define MESSAGEPROCESSOR_PROCESS_H

#include <ProcessScheduler.h>
#include <array>

namespace Networking {
namespace Mqtt {

class Message_Processor : public Process
{
public:

    const static uint8_t const_topicCount = 32;

    struct Configuration_Message_Processor
    {
        std::array<String, const_topicCount> subscribed_topics;
        std::array<String, const_topicCount> publishing_topics;
    };

    const std::array<String, const_topicCount> &getSubscriptions() const;

    Message_Processor(const Configuration_Message_Processor &config,
                      Scheduler &manager,
                      ProcPriority priority = LOW_PRIORITY,
                      uint32_t period = SERVICE_SECONDLY,
                      int iterations=RUNTIME_FOREVER,
                      uint16_t overSchedThresh = OVERSCHEDULED_NO_WARNING);

    virtual ~Message_Processor();

    void processMqttMessages(char *topic, uint8_t *payload, unsigned int length);

    // Process interface
protected:
    virtual void service();

private:
    Configuration_Message_Processor _config;

};
}}
#endif // MESSAGEPROCESSOR_PROCESS_H
