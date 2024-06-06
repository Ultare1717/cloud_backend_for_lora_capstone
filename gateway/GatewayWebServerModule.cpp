#include "GatewayWebServerModule.h"
#include "GatewayMqttManager.h"
#include <WiFi.h>
#include <DNSServer.h>
#include <vector>
#include "index_html.h"  // Include HTML content

DNSServer dnsServer;
GatewayMqttManager gatewayMqttManager;  // Initialize MQTT manager instance
GatewayMqttManager* mqttInstance = gatewayMqttManager.getInstance();  // Get singleton instance
IPAddress apIP(192, 168, 1, 1);  // IP address for the SoftAP
char thingName[] = "";  // Name of the thing
int connected_counter = 0;  // Counter for connection attempts

// Constructor for GatewayWebServerModule
GatewayWebServerModule::GatewayWebServerModule(int port) : server(port) {}

// Begin method to start the web server
void GatewayWebServerModule::begin() {
    // Initialize serial communication for debugging
    WiFi.softAPdisconnect(true); // Disconnect any existing AP
    delay(100);

    Serial.println("Setting up SoftAP...");
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("ESP32-AP", "password");

    dnsServer.start(53, "*", apIP);
    Serial.println("DNS server started");

    setupRoutes();  // Set up routes for handling HTTP requests

    server.begin();
    Serial.println("Web server started");
}

// Loop method to handle DNS requests and MQTT client loop
void GatewayWebServerModule::loop() {
    dnsServer.processNextRequest();
    mqttInstance->loop();  // Handle MQTT client loop

    if(mqttInstance->awsInitiated) {  // If AWS initiated
        if(!mqttInstance->isConnected()) {  // If not connected to MQTT broker
            mqttInstance->connectAWS(thingName);  // Connect to AWS
            mqttInstance->initializeClient();  // Initialize MQTT client
            mqttInstance->subscribeToTopics();  // Subscribe to MQTT topics
            mqttInstance->setGatewayId(mqttInstance->getGatewayId());  // Set gateway ID
        }

        if(mqttInstance->isConnected() && (!mqttInstance->gatewayInitialized)) {  // If connected to MQTT broker and gateway not initialized
            if (connected_counter == 0) {
                Serial.println("Connected to AWS!!");
                mqttInstance->setPublishTopicBeforeInitialization("esp32/pub");
                mqttInstance->setPublishTopicAfterInitialization((mqttInstance->getSystemName() + "/" + mqttInstance->getGatewayId()));
                delay(2000);
            }
            mqttInstance->publishInitializationMessage();  // Publish initialization message
            delay(2000);
            connected_counter++;
        }
        else if(mqttInstance->dataTransmissionStarted) {
            // Handle data transmission
        }
    }
}

// Method to set up routes for handling HTTP requests
void GatewayWebServerModule::setupRoutes() {
    server.on("/", HTTP_GET, std::bind(&GatewayWebServerModule::handleRoot, this, std::placeholders::_1));
    server.on("/connect", HTTP_PUT, std::bind(&GatewayWebServerModule::handleWiFiConnection, this, std::placeholders::_1));
    server.on("/provision", HTTP_PUT, std::bind(&GatewayWebServerModule::handleProvisioning, this, std::placeholders::_1));
    server.on("/wifi-status", HTTP_GET, std::bind(&GatewayWebServerModule::sendWifiStatus, this, std::placeholders::_1));
    server.on("/aws-provisioning-status", HTTP_GET, std::bind(&GatewayWebServerModule::sendAwsProvisioningStatus, this, std::placeholders::_1));
    server.on("/control-sensor-info", HTTP_GET, std::bind(&GatewayWebServerModule::sendControlAndSensorInfo, this, std::placeholders::_1));
    Serial.println("Routes set up");
}

// Method to send WiFi status in response to a GET request to /wifi-status
void GatewayWebServerModule::sendWifiStatus(AsyncWebServerRequest *request) {
    Serial.println("Received GET Request: /wifi-status");
    if (WiFi.status() != WL_CONNECTED) {  // If not connected to WiFi
        Serial.println("Failed to connect to WiFi within timeout!");
        request->send(500, "text/plain", "Failed to connect to WiFi within timeout!");  // Send error response
    } else {
        Serial.println("Connected Successfully!!");
        request->send(200, "text/plain", "WiFi connected successfully!");  // Send success response
    }
}

// Method to handle root request, sending the root HTML content
void GatewayWebServerModule::handleRoot(AsyncWebServerRequest *request) {
    Serial.println("Handling root request");
    request->send_P(200, "text/html", html_content);  // Send HTML content as response
}

// Method to add a custom route to the server
void GatewayWebServerModule::addRoute(const String& uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest) {
    server.on(uri.c_str(), method, onRequest);  // Add route to the server
}

// Method to handle WiFi connection request
void GatewayWebServerModule::handleWiFiConnection(AsyncWebServerRequest *request) {
    Serial.println("Received /connect request");
    if (request->hasArg("ssid") && request->hasArg("password")) {  // Check if SSID and password are provided
        String ssid = request->arg("ssid");  // Get SSID
        String password = request->arg("password");  // Get password
        String is_enterprise = request->arg("is_enterprise");  // Check if enterprise authentication is used

        if (is_enterprise == "true") {  // If enterprise authentication
            String enterprise_username = request->arg("enterprise_username");  // Get enterprise username
            WiFi.begin(ssid.c_str(), WPA2_AUTH_PEAP, enterprise_username.c_str(), enterprise_username.c_str(), password.c_str());  // Connect with enterprise authentication
        } else {  // If not enterprise authentication
            WiFi.begin(ssid.c_str(), password.c_str());  // Connect without enterprise authentication
        }

        request->send(200, "text/plain", "Attempting to connect to WiFi...");  // Send response
        Serial.println("Sent response");
    } else {
        request->send(400, "text/plain", "Missing SSID or password");  // Send error response if SSID or password is missing
        Serial.println("Missing SSID or password");
    }
}

// Method to handle provisioning request
void GatewayWebServerModule::handleProvisioning(AsyncWebServerRequest *request) {
    if (request->hasArg("system_name") && request->hasArg("access_key") && request->hasArg("secret_access_key")) {  // Check if required parameters are provided
        String system_name = request->arg("system_name");  // Get system name
        String access_key = request->arg("access_key");  // Get access key
        String secret_access_key = request->arg("secret_access_key");  // Get secret access key
        int no_of_sensors = request->arg("number_of_sensors").toInt();  // Get number of sensors

        // Set system name, access key, and secret access key in MQTT instance
        mqttInstance->setSystemName(system_name);
        mqttInstance->setAccessKey(access_key);
        mqttInstance->setPrivateKey(secret_access_key);
        mqttInstance->awsInitiated = true;  // Set AWS initiated flag to true

        // Process dynamically added sensor arguments
        int sensor_types[no_of_sensors];  // Array to store sensor types
        for (int i = 1; i <= no_of_sensors; i++) {
            String sensor_arg_name = "sensor_" + String(i);
            int sensor_value = request->arg(sensor_arg_name).toInt();
            Serial.println(sensor_value);
            sensor_types[i] = sensor_value;  // Store sensor types in array
        }

        // Pass sensor types to the MQTT instance
        mqttInstance->setSensorTypes(sensor_types, no_of_sensors);

        request->send(200, "text/plain", "Connecting to AWS!!");  // Send response
        Serial.println("Sent response");
    } else {
        request->send(400, "text/plain", "Missing required parameters");  // Send error response if required parameters are missing
        Serial.println("Missing required parameters");
    }
    Serial.println("Received /provision request");
}

// Method to send AWS provisioning status in response to a GET request to /aws-provisioning-status
void GatewayWebServerModule::sendAwsProvisioningStatus(AsyncWebServerRequest *request) {
    Serial.println("Received GET Request: /aws-provisioning-status");
    if (mqttInstance->unauthorized) {  // If unauthorized user tried to initialize certificate
        Serial.println("Unauthorized User Tried To Initialize Certificate");
        request->send(500, "text/plain", "Unauthorized User Initializing Certificate");  // Send error response
        mqttInstance->unauthorized = false;
        mqttInstance->awsInitiated = false;  // Reset flags and disconnect MQTT client
        Serial.println("Fill Credentials To reinitiate!!");
        mqttInstance->disconnect();
    } else if (mqttInstance->gatewayInitialized && !mqttInstance->dataTransmissionStarted) {  // If device provisioned successfully
        Serial.println("Device Provisioned Successfully!!");
        request->send(200, "text/plain", "Device Provisioned connected successfully!");  // Send success response
        mqttInstance->dataTransmissionStarted = true;
    }
}

// Method to generate and send sensor readings
void GatewayWebServerModule::generateAndSendSensorReadings(int currentNode, int parentNode, const int sensorReadings[], unsigned long timestamp) {
    if (mqttInstance->dataTransmissionStarted)  // If data transmission started
        mqttInstance->constructSensorReadingMessage(currentNode, parentNode, sensorReadings, timestamp);  // Construct and send sensor readings
}

// Method to get the number of sensors
int GatewayWebServerModule::getSensorCount() {
    return mqttInstance->getSensorCount();  // Get the number of sensors from MQTT instance
}

// Method to send control and sensor information in response to a GET request to /control-sensor-info
void GatewayWebServerModule::sendControlAndSensorInfo(AsyncWebServerRequest *request) {
    Serial.println("Received GET Request: /control-sensor-info");

    // Get the latest control and sensor messages from MQTT instance
    String controlMessage = mqttInstance->getLatestControlMessage();
    String sensorMessage = mqttInstance->getLatestSensorMessage();

    Serial.println("Sensor Message is as follows:");
    Serial.println(sensorMessage);

    // Check if controlMessage is empty or not properly formatted JSON
    if (controlMessage.isEmpty()) {
        controlMessage = "{}"; // Provide default empty JSON object
    }

    // Check if sensorMessage is empty or not properly formatted JSON
    if (sensorMessage.isEmpty()) {
        sensorMessage = "{}"; // Provide default empty JSON object
    }

    // Construct the response JSON object
    String jsonResponse = "{\"controlMessage\": " + controlMessage + ", \"sensorMessage\": " + sensorMessage + "}";
    Serial.println(jsonResponse);

    // Send the JSON response to the client
    request->send(200, "application/json", jsonResponse);

    Serial.println("Sent control and sensor info to client");
}
