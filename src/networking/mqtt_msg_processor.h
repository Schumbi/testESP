#ifndef MESSAGEPROCESSOR_PROCESS_H
#define MESSAGEPROCESSOR_PROCESS_H

#include <ProcessScheduler.h>
#include <array>

namespace Networking {
namespace Mqtt {

class Process;

class Abstract_Message_Processor : public ::Process
{
public:

    const static uint8_t const_topicCount = 8;

    struct Configuration_Message_Processor
    {
        std::array<String, const_topicCount> subscribed_topics;
        std::array<String, const_topicCount> publishing_topics;
    };

    const std::array<String, const_topicCount> &getSubscriptions() const;

    Abstract_Message_Processor(const Configuration_Message_Processor &config,
                      Scheduler &manager,
                      ProcPriority priority = LOW_PRIORITY,
                      uint32_t period = SERVICE_SECONDLY,
                      int iterations=RUNTIME_FOREVER,
                      uint16_t overSchedThresh = OVERSCHEDULED_NO_WARNING);


    virtual ~Abstract_Message_Processor();

protected:
    virtual void processMessage(String topic, uint8_t *payload, unsigned int length) = 0;


private:
    Configuration_Message_Processor _config;
    friend class Networking::Mqtt::Process;
    void mqttMessageCallback(char *topic, uint8_t *payload, unsigned int length);


    // Process interface
protected:
    virtual void service();
    virtual void setup();
    virtual void cleanup();
    virtual void onEnable();
    virtual void onDisable();
    virtual void handleWarning(ProcessWarning warning);
};
}}

#endif // MESSAGEPROCESSOR_PROCESS_H
