#ifndef WIFI_PROCESS_H
#define WIFI_PROCESS_H

#include <ProcessScheduler.h>

class ESP8266WebServer;
class ESP8266HTTPUpdateServer;

class Network_Process : public Process
{

public:

    struct Configuration_Network_struct
    {
        const char* hostname;
        const char* ssid;
        const char* ssid_password;
        const char* updatePath;
        const char* updateUserName;
        const char* updatePassword;
        uint16_t updatePort;
    };

    Network_Process(const Configuration_Network_struct &net,
                Scheduler &manager,
                ProcPriority priority = HIGH_PRIORITY,
                uint32_t period = SERVICE_SECONDLY,
                int iterations = RUNTIME_FOREVER,
                uint16_t overSchedThresh = OVERSCHEDULED_NO_WARNING);

    virtual ~Network_Process();
    bool isOTAReady()
    {
        return _httpServer != nullptr && _updateServer != nullptr;
    }

protected:
    // called regularly
    void service();
    // called when added to scheduler
    void setup();
    // called when removed from scheduler
    void cleanup();

    void startWifi();
    void stopWifi();

    void startWebServer(uint16_t updatePort);
    void stopWebServer();

    void startOTAServer();
    void stopOTAServer();


private:

    String _update_credetials_update_path;
    String _update_credetials_username;
    String _update_credentials_password;

    String _hostname;
    ESP8266WebServer* _httpServer;
    ESP8266HTTPUpdateServer* _updateServer;

    Configuration_Network_struct _netConfig;
};

#endif // WIFI_PROCESS_H
