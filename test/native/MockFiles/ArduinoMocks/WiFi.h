// Header for Wifi Mock

#ifndef __Wifi_h__
#define __Wifi_h__

#include <gmock/gmock.h>
#include <stdint.h>

class WiFi_ {
  public:
    void on();  // turns on WiFi module
    void off();  // turns off WiFi module
    void connect();  // Attempts to connect to the WiFi network
    void disconnect(); // Disconnect from the Wifi network
    bool connecting(); // Return true once the Core is attempting to connect
    bool ready();  // Return true once Core is connected
    void listen();  // Enter listening mode
    bool listening();  // Return true once listen() has been called
    void setCredentials(); // Allows user to set credentials
    bool clearCredentials(); // Clear all saved credentials
    bool hasCredentials();  // Return true if credentials have been already stored in CC3000's memory
    uint8_t macAddress(); // Return Mac Address of the device
    char* SSID();  // return SSID of the network
    int RSSI();  // return signal strength
    void ping(char*); // ping an IP address
    void ping(char*,
              uint8_t); // ping an IP address with a specified number of times
    char* localIP();  // Return local IP address
    char* subnetMask(); // Return Subnet mask of the network
    char* gatewayIP();  // Return the gateway IP address
};
extern WiFi_ WiFi;

class WiFiMock {
  public:
    MOCK_METHOD(void, on, ());
    MOCK_METHOD(void, off, ());
    MOCK_METHOD(void, connect, ());
    MOCK_METHOD(void, disconnect, ());
    MOCK_METHOD(bool, connecting, ());
    MOCK_METHOD(bool, ready, ());
    MOCK_METHOD(void, listen, ());
    MOCK_METHOD(bool, listening, ());
    MOCK_METHOD(void, setCredentials, ());
    MOCK_METHOD(bool, clearCredentials, ());
    MOCK_METHOD(bool, hasCredentials, ());
    MOCK_METHOD(uint8_t, macAddress, ());
    MOCK_METHOD(char *, SSID, ());
    MOCK_METHOD(int, RSSI, ());
    MOCK_METHOD(void, ping, (char*));
    MOCK_METHOD(void, ping, (char*, uint8_t));
    MOCK_METHOD(char *, localIP, ());
    MOCK_METHOD(char *, subnetMask, ());
    MOCK_METHOD(char *, gatewayIP, ());
};

WiFiMock* WiFiMockInstance();
void releaseWiFiMock();

#endif
