#ifndef GATEWAY_MQTT_MANAGER_H
#define GATEWAY_MQTT_MANAGER_H

#include <WiFiClientSecure.h> // Include library for secure WiFi client
#include <PubSubClient.h>     // Include MQTT library
#include <ArduinoJson.h>      // Include library for JSON handling

#define MAX_SENSOR_TYPES 56   // Maximum number of sensor types

class GatewayMqttManager {
private:
    WiFiClientSecure net;                 // Secure WiFi client instance
    PubSubClient client;                  // MQTT client instance
    String systemName;                    // Name of the system
    String gatewayId;                     // ID of the gateway
    String privateKey;                    // Private key for authentication
    String accessKey;                     // Access key for authentication
    String publishTopicBeforeInitialization;  // Topic for publishing initialization message
    String publishTopicAfterInitialization;   // Topic for publishing messages after initialization
    String latestControlMessage;          // Latest control message received
    String latestSensorMessage;           // Latest sensor message received
    int sensorTypes[MAX_SENSOR_TYPES];    // Array to store sensor types
    int sensorCount;                      // Number of sensor types configured

    static void messageReceived(char* topic, byte* payload, unsigned int length);  // Static method to handle incoming MQTT messages

public:
    bool awsInitiated;            // Flag indicating AWS initialization status
    bool gatewayInitialized;      // Flag indicating gateway initialization status
    bool dataTransmissionStarted; // Flag indicating data transmission status
    bool unauthorized;            // Flag indicating unauthorized status

    GatewayMqttManager();         // Constructor
    static GatewayMqttManager* getInstance();  // Static method to get singleton instance
    void setSystemName(const String& name);    // Method to set system name
    String getSystemName() const;               // Method to get system name
    void setPrivateKey(const String& key);     // Method to set private key
    String getPrivateKey() const;              // Method to get private key
    void setAccessKey(const String& key);      // Method to set access key
    String getAccessKey() const;               // Method to get access key
    void setGatewayId(const String& id);       // Method to set gateway ID
    String getGatewayId() const;               // Method to get gateway ID
    void setPublishTopicBeforeInitialization(const String& publishTopicBeforeInitialization);  // Method to set publish topic before initialization
    String getPublishTopicBeforeInitialization() const;  // Method to get publish topic before initialization
    void setPublishTopicAfterInitialization(const String& publishTopicAfterInitialization);    // Method to set publish topic after initialization
    String getPublishTopicAfterInitialization() const;   // Method to get publish topic after initialization
    const int* getSensorTypes() const;          // Method to get sensor types
    void setSensorTypes(const int types[], int count);   // Method to set sensor types
    int getSensorCount() const;                  // Method to get the number of sensor types configured
    void generateGatewayId();                    // Method to generate gateway ID
    void initializeClient();                     // Method to initialize MQTT client
    void publishInitializationMessage();         // Method to publish initialization message
    void constructSensorReadingMessage(int currentNode, int parentNode, const int sensorReadings[], unsigned long timestamp);  // Method to construct and publish sensor reading message
    void connectAWS(char thingName[]);           // Method to connect to AWS
    bool isConnected();                          // Method to check if connected to MQTT broker
    void disconnect();                           // Method to disconnect from MQTT broker
    void subscribeToTopics();                    // Method to subscribe to MQTT topics
    String getLatestControlMessage();            // Method to get the latest control message
    String getLatestSensorMessage();             // Method to get the latest sensor message
    void updateControlMessage(const String& message);   // Method to update the latest control message
    void updateSensorMessage(const String& message);    // Method to update the latest sensor message
    void loop();                                // Method to handle MQTT client loop
};

#endif  // GATEWAY_MQTT_MANAGER_H
