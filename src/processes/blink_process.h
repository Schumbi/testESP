#ifndef BLINK_PROCESS_H
#define BLINK_PROCESS_H

#include <ProcessScheduler.h>

class Blink_Process : public Process
{
public:
    Blink_Process(Scheduler &manager,
                  ProcPriority priority = LOW_PRIORITY,
                  uint32_t period = SERVICE_SECONDLY,
                  int iterations=RUNTIME_FOREVER,
                  uint16_t overSchedThresh = OVERSCHEDULED_NO_WARNING);

    virtual ~Blink_Process();

protected:
    virtual void service();

};

#endif // BLINK_PROCESS_H
