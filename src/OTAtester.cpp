#include <Arduino.h>

#include <ProcessScheduler.h>
#include <ProcessScheduler/Config.h>

#include <ESP8266WiFi.h>

#include "processes/blink_process.h"
#include "processes/network_process.h"
#include "processes/mqtt_process.h"
#include "processes/mqtt_msg_processor.h"

#include "../../wlan.hpp"

#include "../../pwd.hpp"

void setup();
void loop();

// Scheduler
static Scheduler scheduler;


void setup()
{
    // Serial Stuff
    //Serial.begin(115200);
    Serial.begin(9600);
    Serial.setDebugOutput(true);
    Serial.println("Start...");
    delay(10);

    WiFi.mode(WIFI_OFF);

    Network_Process::Configuration_Network_struct config_network;
    config_network.ssid = network_configuration::ssid;
    config_network.ssid_password = network_configuration::ssid_password;
    config_network.updatePort = network_configuration::updatePort;
    config_network.updatePath = UPDATE_PATH;
    config_network.updateUserName = UPDATE_USERNAME;
    config_network.updatePassword = UPDATE_PASSWORT;
    (new Network_Process(config_network, scheduler))->add(true);

    Mqtt_Process::Configuration_Mqtt_struct config_mqtt;
    config_mqtt.mqtt_broker = "192.168.1.2";
    config_mqtt.mqtt_port = MAKELIGHT_MQTT_SERVER_PORT;
    config_mqtt.msg_processor = new Mqtt_msg_Processor(scheduler);
    (new Mqtt_Process(config_mqtt, scheduler))->add(true);

    // blinky process
    (new Blink_Process(scheduler))->add(true);

    Serial.println("Setup done!");
}

void loop()
{
    scheduler.run();
}
