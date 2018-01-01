#include "mqtt_process.h"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "../mDebug.h"

Mqtt_Process::Mqtt_Process(const Configuration_Mqtt_struct &config,
                           Scheduler &manager,
                           ProcPriority priority,
                           uint32_t period,
                           int iterations,
                           uint16_t overSchedThresh)
    : Process (manager, priority, period, iterations, overSchedThresh),
      _config(config),
      _mqtt_client(nullptr),
      _espClient(nullptr)
{
    HERE;
}

Mqtt_Process::~Mqtt_Process()
{
    cleanup();
}

void Mqtt_Process::service()
{
    if(!WiFi.isConnected())
    {
        onDisable();
        return;
    }

    if(_mqtt_client == nullptr)
    {
        HERE;
        setup();

        if(isEnabled())
        {
            startMqtt();
        }
        return;
    }


    if(!_mqtt_client->connected())
    {
        setPeriod(SERVICE_SECONDLY);
        reconnect();
    }
    else
    {
        _mqtt_client->loop();
    }
}

void Mqtt_Process::setup()
{

    if(WiFi.isConnected())
    {
        START;
        if(_espClient == nullptr)
        {
            _espClient = new WiFiClient();
        }

        if(_mqtt_client == nullptr)
        {
            _mqtt_client = new PubSubClient(*_espClient);
        }
        END;
    }
}

void Mqtt_Process::cleanup()
{
    if(_mqtt_client != nullptr)
    {
        if(_mqtt_client->connected())
        {
            _mqtt_client->disconnect();
        }
        delete _mqtt_client;
        _mqtt_client = nullptr;
    }

    if(_espClient != nullptr)
    {
        delete _espClient;
        _espClient = nullptr;
    }
}

void Mqtt_Process::onEnable()
{
    if(WiFi.isConnected())
    {
        startMqtt();

        if(_mqtt_client != nullptr && !_mqtt_client->connected())
        {
            reconnect();
        }
    }
}

void Mqtt_Process::startMqtt()
{
    START;
    if(_mqtt_client != nullptr)
    {
        Serial.println(String("MQTT: ") + String(_config.mqtt_broker) + ":"+ _config.mqtt_port);
        _mqtt_client->setServer(_config.mqtt_broker, _config.mqtt_port);
        Serial.println("MQTT: Setting callback!");
        using namespace std::placeholders;
        _mqtt_client->setCallback(std::bind(&Mqtt_msg_Processor::processMqttMessages , _config.msg_processor, _1, _2, _3));
        reconnect();
    }
    END;
}

void Mqtt_Process::stopMqtt()
{
    if(_mqtt_client != nullptr)
    {
        _mqtt_client->disconnect();
    }
}

void Mqtt_Process::reconnect()
{
    auto client = _mqtt_client;
    if(client != nullptr && !client->connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client->connect("OTA_test"))
        {
            Serial.println("connected");
            // ... and resubscribe
            client->subscribe("/home/test");

            setPeriod(10);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client->state());
        }
    }
}


void Mqtt_Process::onDisable()
{
    stopMqtt();
}
