#include "GatewayWebServerModule.h"  // Include the GatewayWebServerModule header file
#include "GatewayMqttManager.h"  // Include the GatewayMqttManager header file

GatewayWebServerModule gwServer(80);  // Create an instance of GatewayWebServerModule with port 80

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  gwServer.begin();  // Begin the web server
}

void loop() {
    gwServer.loop();  // Execute web server operations in the loop
    
    // Send sensor readings every 10 seconds
    if (millis() % 10000 == 0) {
        unsigned long timestamp = millis();  // Get current timestamp
        
        // Subtract 60 days from the current timestamp
        const unsigned long milliseconds_in_60_days = 60 * 24 * 60 * 60 * 1000UL;
        timestamp -= milliseconds_in_60_days;
        
        int current_node = random(100 + 1);  // Generate a random current node ID
        int parent_node = random(100 + 1);   // Generate a random parent node ID
        
        // Check if there are sensors available
        if (gwServer.getSensorCount() > 0) {
            int sensorReadings[gwServer.getSensorCount()];  // Array to store sensor readings
            
            // Generate random readings for each sensor
            for (int i = 0; i < gwServer.getSensorCount(); ++i) {
                sensorReadings[i] = random(1023 + 1);  // Generate a random sensor reading
            }
            
            // Generate and send sensor readings to the MQTT manager
            gwServer.generateAndSendSensorReadings(current_node, parent_node, sensorReadings, timestamp);
        }
    }
}
