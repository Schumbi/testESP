#ifndef MQTT_PROCESS_H
#define MQTT_PROCESS_H

#include <ProcessScheduler.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

#include "processes/mqtt_msg_processor.h"

class Mqtt_Process : public Process
{
public:

    struct Configuration_Mqtt_struct
    {
        const char* mqtt_broker;
        uint16_t mqtt_port;
        Mqtt_msg_Processor *msg_processor;
    };

    Mqtt_Process(const Configuration_Mqtt_struct &config,
                 Scheduler &manager,
                 ProcPriority priority = LOW_PRIORITY,
                 uint32_t period = SERVICE_SECONDLY,
                 int iterations = RUNTIME_FOREVER,
                 uint16_t overSchedThresh = OVERSCHEDULED_NO_WARNING);

    virtual ~Mqtt_Process();

    // Process interface
protected:
    void service();
    void setup();
    void cleanup();
    void onEnable();
    void onDisable();

    void startMqtt();
    void stopMqtt();
    void reconnect();

private:
    Configuration_Mqtt_struct _config;
    PubSubClient *_mqtt_client;
    WiFiClient *_espClient;
};



#endif // MQTT_PROCESS_H
