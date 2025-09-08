#include "mqtt_client.h"

MQTTClient::MQTTClient(const char* server, int port, const char* clientId, const char* username, const char* password) 
    : _server(server), _port(port), _clientId(clientId), _username(username), _password(password), _client(_wifiClient) {
    _client.setServer(_server, _port);
}

bool MQTTClient::connect() {
    if (_username && _password) {
        return _client.connect(_clientId, _username, _password);
    } else {
        return _client.connect(_clientId);
    }
}

bool MQTTClient::publish(const char* topic, const char* payload) {
    return _client.publish(topic, payload);
}

bool MQTTClient::subscribe(const char* topic) {
    return _client.subscribe(topic);
}

void MQTTClient::loop() {
    _client.loop();
}

bool MQTTClient::isConnected() {
    return _client.connected();
}

void MQTTClient::setCallback(void (*callback)(char*, uint8_t*, unsigned int)) {
    _client.setCallback(callback);
}
