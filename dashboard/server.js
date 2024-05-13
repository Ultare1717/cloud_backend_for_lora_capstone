// Import necessary modules
const express = require('express');
const { DynamoDBClient, ScanCommand } = require('@aws-sdk/client-dynamodb');
const path = require('path');

// Initialize Express app
const app = express();

// Initialize DynamoDB client
const dynamoDB = new DynamoDBClient({ region: 'ca-central-1' });

// Enable Cross-Origin Resource Sharing (CORS)
const cors = require("cors");
const corsOptions = {
    origin: '*',
    credentials: true,
    optionSuccessStatus: 200,
}
app.use(cors(corsOptions)); // Use CORS middleware
app.use(express.json()); // Use JSON parsing middleware

// Serve static files from the current directory
app.use(express.static(__dirname));

// Handle requests for favicon.ico
app.get('/favicon.ico', (req, res) => res.status(204)); // Respond with a 204 No Content status

// Handle requests for combineddata
app.get('/combineddata', async (req, res) => {
    try {
        // Fetch data from DynamoDB SystemToGatewayTable
        const [systemToGatewayData] = await Promise.all([
            dynamoDB.send(new ScanCommand({ TableName: 'SystemToGatewayTable' }))
        ]);

        // Initialize combinedData object
        const combinedData = {
            gatewayData: {}, // Object to hold gateway data for each system
            nodeData: {} // Object to hold node data for each gateway
        };

        // Process data from SystemToGateway table
        systemToGatewayData.Items.forEach(item => {
            const systemID = item.SystemID.S;
            const gatewayID = item.GatewayID.S;

            // Ensure the array exists for the systemID
            if (!combinedData.gatewayData[systemID]) {
                combinedData.gatewayData[systemID] = [];
            }

            // Push gatewayID to the array corresponding to the systemID
            combinedData.gatewayData[systemID].push(gatewayID);
        });

        // Send combinedData as JSON response
        res.json({ combinedData });
    } catch (error) {
        // Handle errors
        console.error('Error fetching combined data from DynamoDB:', error);
        res.status(500).json({ error: 'Internal Server Error' }); // Respond with a 500 Internal Server Error status
    }
});

// Set the port for the server to listen on
const PORT = 4084;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`); // Log that the server is running
});
