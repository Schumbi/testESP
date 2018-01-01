#include "network_process.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include "../mDebug.h"

Network_Process::Network_Process(const Configuration_Network_struct &net,
                                 Scheduler &manager,
                                 ProcPriority priority,
                                 uint32_t period,
                                 int iterations,
                                 uint16_t overSchedThresh) :
    Process(manager, priority, period, iterations,  overSchedThresh)
{
    _httpServer = nullptr;
    _updateServer = nullptr;

    _netConfig = net;
    Serial.println(String(__FILE__) + "(" + __LINE__ + ")");
}


Network_Process::~Network_Process()
{
    stopOTAServer();
}

void Network_Process::service()
{
    if(WiFi.status() != WL_CONNECTED)
    {
        Serial.println(".");
        setPeriod(SERVICE_SECONDLY);
        return;
    }

    if(WiFi.isConnected())
    {
        // update status
        if(isOTAReady())
        {
            _httpServer->handleClient();
            setPeriod(50);
        }
        else
        {
            HERE;
            setPeriod(SERVICE_SECONDLY);
            startOTAServer();
        }
        return;
    }

    Serial.println("Not connected!");
    stopOTAServer();
    setPeriod(1000);
    END;
}

void Network_Process::cleanup()
{
    Serial.println(String(__func__));
    stopOTAServer();
}

// gets started when process added to sched
void Network_Process::setup()
{
    Serial.println(String(__func__));
    startWifi();
    // setup OTA Server
    startOTAServer();
}

void Network_Process::startOTAServer()
{
    START;
    if(WiFi.isConnected())
    {
        startWebServer(_netConfig.updatePort);

        HERE;
        if(_httpServer == nullptr)
        {
            Serial.println("HTTP Server not yet started!");
            return;
        }
        HERE;

        if(_updateServer == nullptr)
        {
            Serial.println("Starting OTA Server");
            HERE;
            _updateServer = new ESP8266HTTPUpdateServer();
            HERE;
            Serial.printf("Update Info\n");
            Serial.printf("IP:   %s\n", WiFi.localIP().toString().c_str());
            Serial.printf("PORT: %d\n", _netConfig.updatePort);
            Serial.printf("PATH: %s\n", _netConfig.updatePath);
            Serial.printf("USER: %s\n", _netConfig.updateUserName);
            Serial.printf("PWD:  %s\n", _netConfig.updatePassword);
            HERE;
            _updateServer->setup(_httpServer,
                                 _netConfig.updatePath,
                                 _netConfig.updateUserName,
                                 _netConfig.updatePassword);
            HERE;
        }
    }
    END;
}

void Network_Process::stopOTAServer()
{
    if(_updateServer != nullptr)
    {
        delete _updateServer;
        _updateServer = nullptr;
        Serial.println("Stoped update server");
    }

    stopWebServer();
}

void Network_Process::startWebServer(uint16_t updatePort)
{
    START;
    if(_httpServer == nullptr)
    {
        HERE;
        Serial.println("Starting OTA Webserver");
        _httpServer = new ESP8266WebServer(updatePort);
        HERE;
    }

    if(_httpServer != nullptr)
    {
        _httpServer->begin();
    }
    else
    {
        Serial.println("Error starting Webserver");
    }
    END;
}

void Network_Process::stopWebServer()
{
    if(_httpServer != nullptr)
    {
        _httpServer->stop();
        delete _httpServer;
        _httpServer = nullptr;
    }
    Serial.println("Stoped webserver");
}

void Network_Process::startWifi()
{
    Serial.println("Start Wifi");

    WiFi.hostname(_netConfig.hostname);
    WiFi.mode(WiFiMode::WIFI_STA);
    WiFi.setPhyMode(WiFiPhyMode::WIFI_PHY_MODE_11N);
    WiFi.begin(_netConfig.ssid, _netConfig.ssid_password);
    WiFi.setAutoConnect(true);
    WiFi.setAutoReconnect(true);
}
