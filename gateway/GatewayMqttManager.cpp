#include "GatewayMqttManager.h"
#include "Secrets.h"
#include <vector>

GatewayMqttManager::GatewayMqttManager() : client(net), awsInitiated(false), gatewayInitialized(false), dataTransmissionStarted(false), unauthorized(false), sensorCount(0) {}

// Method to set the system name
void GatewayMqttManager::setSystemName(const String& name) {
    systemName = name;
}

// Method to get the system name
String GatewayMqttManager::getSystemName() const {
    return systemName;
}

// Method to set the private key
void GatewayMqttManager::setPrivateKey(const String& key) {
    privateKey = key;
}

// Method to get the private key
String GatewayMqttManager::getPrivateKey() const {
    return privateKey;
}

// Method to set the access key
void GatewayMqttManager::setAccessKey(const String& key) {
    accessKey = key;
}

// Method to get the access key
String GatewayMqttManager::getAccessKey() const {
    return accessKey;
}

// Method to set the gateway ID
void GatewayMqttManager::setGatewayId(const String& id) {
    gatewayId = id;
}

// Method to get the gateway ID
String GatewayMqttManager::getGatewayId() const {
    return gatewayId;
}

// Method to set the publish topic before initialization
void GatewayMqttManager::setPublishTopicBeforeInitialization(const String& topic) {
    this->publishTopicBeforeInitialization = topic;
}
    
// Method to get the publish topic before initialization
String GatewayMqttManager::getPublishTopicBeforeInitialization() const {
    return this->publishTopicBeforeInitialization;
}
    
// Method to set the publish topic after initialization
void GatewayMqttManager::setPublishTopicAfterInitialization(const String& topic) {
    this->publishTopicAfterInitialization = topic;
}
    
// Method to get the publish topic after initialization
String GatewayMqttManager::getPublishTopicAfterInitialization() const {
    return this->publishTopicAfterInitialization;
}

// Method to set sensor types
void GatewayMqttManager::setSensorTypes(const int types[], int count) {
    // Copy sensor types from the provided array
    for (int i = 1; i <= count && i < MAX_SENSOR_TYPES; i++) {
        sensorTypes[i] = types[i]+1;
        Serial.println(sensorTypes[i]);
    }
    sensorCount = min(count, MAX_SENSOR_TYPES); // Update sensor count
}

// Method to get sensor types
const int* GatewayMqttManager::getSensorTypes() const {
    return sensorTypes;
}

// Method to get the number of sensor types
int GatewayMqttManager::getSensorCount() const {
    return sensorCount;
}

// Method to get the latest control message
String GatewayMqttManager::getLatestControlMessage() {
    return latestControlMessage;
}

// Method to get the latest sensor message
String GatewayMqttManager::getLatestSensorMessage() {
    return latestSensorMessage;
}

// Method to update the control message
void GatewayMqttManager::updateControlMessage(const String& message) {
    latestControlMessage = message;
}

// Method to update the sensor message
void GatewayMqttManager::updateSensorMessage(const String& message) {
    latestSensorMessage = message;
}

// Method to publish initialization message
void GatewayMqttManager::publishInitializationMessage() {
    StaticJsonDocument<400> doc;
    doc["systemName"] = systemName;
    doc["thingName"] = gatewayId;
    doc["ak"] = accessKey;
    doc["sak"] = privateKey;
    doc["topic"] = this->publishTopicAfterInitialization;

    // Add sensor types to the JSON document
    JsonArray sensorArray = doc.createNestedArray("sensorTypes");
    for (int i = 1; i <= sensorCount; i++) {
        sensorArray.add(sensorTypes[i]);
    }

    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);
    client.publish(this->publishTopicBeforeInitialization.c_str(), jsonBuffer);
}

// Method to generate gateway ID
void GatewayMqttManager::generateGatewayId() {
    // Generate GatewayID
    uint32_t chipId = 0;
    for(int i = 0; i < 17; i += 8) {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    char gatewayIdBuffer[17];
    sprintf(gatewayIdBuffer, "Gateway%08X", chipId);
    setGatewayId(gatewayIdBuffer);
}

// Method to initialize MQTT client
void GatewayMqttManager::initializeClient() {
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);
    client.setServer(AWS_IOT_ENDPOINT, 8883);
    client.setCallback(messageReceived);
    //client.setBufferSize(10000);
    GatewayMqttManager* mqttInstance = getInstance();

    if (gatewayId.isEmpty()) {
        generateGatewayId();
    }
}

// Method to connect to AWS
void GatewayMqttManager::connectAWS(char thingName[]) {
    client.connect(thingName);
}

// Method to check if connected
bool GatewayMqttManager::isConnected() {
    return client.connected();
}

// Method to disconnect from MQTT broker
void GatewayMqttManager::disconnect() {
  client.disconnect();
}

// Method to subscribe to topics
void GatewayMqttManager::subscribeToTopics() {
    client.subscribe((systemName + "/" + gatewayId).c_str(), MQTTQOS0);
    client.subscribe((systemName + "/" + gatewayId + "/control").c_str() , MQTTQOS0);
    client.subscribe((systemName + "/" + gatewayId + "/authorized").c_str(), MQTTQOS0);
    client.subscribe((systemName + "/" + gatewayId + "/unauthorized").c_str(), MQTTQOS0);
    client.subscribe("esp32/sub", MQTTQOS0);
}

// Method to get singleton instance of GatewayMqttManager
GatewayMqttManager* GatewayMqttManager::getInstance() {
    static GatewayMqttManager instance;
    return &instance;
}

// Method called when a message is received
void GatewayMqttManager::messageReceived(char* topic, byte* payload, unsigned int length) {
    Serial.print("Received [");
    Serial.print(topic);
    Serial.print("]: ");
    String messagePayload;
    for (int i = 0; i < length; i++) {
        messagePayload += (char)payload[i];
    }
    Serial.print(messagePayload);
    GatewayMqttManager* mqttInstance = getInstance();
    if (mqttInstance != nullptr) {
      String authorizedTopic = mqttInstance->getSystemName() + "/" + mqttInstance->getGatewayId() + "/authorized";
      String unauthorizedTopic = mqttInstance->getSystemName() + "/" + mqttInstance->getGatewayId() + "/unauthorized";
      String controlTopic = mqttInstance->getSystemName() + "/" + mqttInstance->getGatewayId() + "/control";
      String sensorTopic = mqttInstance->getSystemName() + "/" + mqttInstance->getGatewayId();
        if (!mqttInstance->gatewayInitialized && strcmp(topic, unauthorizedTopic.c_str()) == 0) {
            mqttInstance->unauthorized = true;
            return;
        }
        else if (!mqttInstance->gatewayInitialized && strcmp(topic,  authorizedTopic.c_str()) == 0) {
            mqttInstance->gatewayInitialized = true;
        }

        // Check if the received topic corresponds to a control message
        else if (strcmp(topic, controlTopic.c_str()) == 0&& mqttInstance->dataTransmissionStarted) {
            // Update the latest control message
            mqttInstance->updateControlMessage(messagePayload);
        }
        // Check if the received topic corresponds to a sensor message
        else if (strcmp(topic, sensorTopic.c_str()) == 0 && mqttInstance->dataTransmissionStarted) {
            // Update the latest sensor message
            mqttInstance->updateSensorMessage(messagePayload);
        }
    }
}

// Method to construct and publish sensor reading message
void GatewayMqttManager::constructSensorReadingMessage(int currentNode, int parentNode, const int sensorReadings[], unsigned long timestamp) {
    DynamicJsonDocument doc(400);
    GatewayMqttManager* mqttInstance = getInstance();

    doc["systemName"] = systemName;
    doc["topicName"] = this->publishTopicAfterInitialization;
    doc["currentNodeID"] = currentNode;
    doc["parentNodeID"] = parentNode;
    doc["payloadSize"] = sensorCount; // Number of sensor readings
    doc["timestamp"] = timestamp;

    // Set sensor readings dynamically
    for (size_t i = 0; i < sensorCount; ++i) {
        char sensorName[20];
        sprintf(sensorName, "sensor%dReading", i + 1);
        doc[sensorName] = sensorReadings[i];
    }

    char payload[512];
    serializeJson(doc, payload);
    client.publish(this->publishTopicAfterInitialization.c_str(), payload);
}

// Method to handle MQTT client loop
void GatewayMqttManager::loop() {
    client.loop();
}
