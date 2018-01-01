#ifndef BLINK_PROCESS_H
#define BLINK_PROCESS_H

#include "networking/mqtt_msg_processor.h"

#include <ProcessScheduler.h>

class Blink_Process : public Networking::Mqtt::Abstract_Message_Processor
{
public:
    Blink_Process(const Configuration_Message_Processor &config,
                  Scheduler &manager,
                  ProcPriority priority = LOW_PRIORITY,
                  uint32_t period = SERVICE_SECONDLY,
                  int iterations=RUNTIME_FOREVER,
                  uint16_t overSchedThresh = OVERSCHEDULED_NO_WARNING);

    virtual ~Blink_Process();

protected:
    virtual void service();
    virtual void cleanup();

    // Abstract_Message_Processor interface
    virtual void processMessage(String topic, uint8_t *payload, unsigned int length);

};

#endif // BLINK_PROCESS_H
