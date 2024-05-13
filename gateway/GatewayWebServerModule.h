#ifndef GATEWAYWEBSERVERMODULE_H
#define GATEWAYWEBSERVERMODULE_H

#include <ESPAsyncWebServer.h>  // Include the ESPAsyncWebServer library
#include <AsyncTCP.h>  // Include the AsyncTCP library

class GatewayWebServerModule {
public:
    // Constructor: Initializes the web server with the specified port
    GatewayWebServerModule(int port);
    
    // Method to start the web server
    void begin();
    
    // Method to handle web server operations in the main loop
    void loop();
    
    // Method to add a custom route to the server
    void addRoute(const String& uri, WebRequestMethodComposite method, ArRequestHandlerFunction onRequest);
    
    // Method to generate and send sensor readings
    void generateAndSendSensorReadings(int currentNode, int parentNode, const int sensorReadings[], unsigned long timestamp); 
    
    // Method to get the number of sensors
    int getSensorCount();

private:
    AsyncWebServer server;  // Instance of the AsyncWebServer class for handling HTTP requests
    
    // Private methods for setting up routes and handling requests
    void setupRoutes();  // Method to set up routes for the server
    void handleRoot(AsyncWebServerRequest *request);  // Method to handle root request
    void handleWiFiConnection(AsyncWebServerRequest *request);  // Method to handle WiFi connection request
    void handleProvisioning(AsyncWebServerRequest *request);  // Method to handle provisioning request
    void sendWifiStatus(AsyncWebServerRequest *request);  // Method to send WiFi status
    void initializeAws(char thingName[]);  // Method to initialize AWS connection
    void sendAwsProvisioningStatus(AsyncWebServerRequest *request);  // Method to send AWS provisioning status
    void sendControlAndSensorInfo(AsyncWebServerRequest *request);  // Method to send control and sensor information
};

#endif /* GATEWAYWEBSERVERMODULE_H */
