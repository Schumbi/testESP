#ifndef MESSAGEPROCESSOR_PROCESS_H
#define MESSAGEPROCESSOR_PROCESS_H

#include <ProcessScheduler.h>

namespace Networking {
namespace Mqtt {

class Message_Processor : public Process
{
public:
    Message_Processor(Scheduler &manager,
                      ProcPriority priority = LOW_PRIORITY,
                      uint32_t period = SERVICE_SECONDLY,
                      int iterations=RUNTIME_FOREVER,
                      uint16_t overSchedThresh = OVERSCHEDULED_NO_WARNING);

    virtual ~Message_Processor();

    void processMqttMessages(char *topic, uint8_t *payload, unsigned int length);

    // Process interface
protected:
    virtual void service();

};
}}
#endif // MESSAGEPROCESSOR_PROCESS_H
