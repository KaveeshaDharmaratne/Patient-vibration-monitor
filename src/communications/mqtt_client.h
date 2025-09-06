#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>
#include <WiFiClient.h>

class MQTTClient {
public:
    MQTTClient(const char* server, int port, const char* clientId);
    bool connect();
    bool publish(const char* topic, const char* payload);
    bool subscribe(const char* topic);
    void loop();
    bool isConnected();
    void setCallback(void (*callback)(char*, uint8_t*, unsigned int));

private:
    WiFiClient _wifiClient;
    PubSubClient _client;
    const char* _server;
    int _port;
    const char* _clientId;
};

#endif
