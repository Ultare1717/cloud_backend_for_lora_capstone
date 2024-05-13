import json
import boto3

# Create an IoT client
iot_client = boto3.client('iot-data')

def control_handler(event, context):
    # Print the received event
    print('Received event:', json.dumps(event, indent=2))

    try:
        # Parse the JSON body from the event
        body = json.loads(event.get('body', '{}'))

        # Extract sensor data from the parsed body
        systemID = body.get('systemID')
        gateway_id = body.get('gatewayID')
        sleepHours = body.get('sleepHours')

        # Print extracted data for logging
        print(f'System ID: {systemID}, Gateway ID: {gateway_id}, Sleep Hours: {sleepHours}')

        # Construct the message to publish
        message = {
            'systemID': systemID,
            'gatewayID': gateway_id,
            'sleepHours': sleepHours
        }

        # Construct the MQTT topic
        mqtt_topic = f'{systemID}/{gateway_id}/control'

        # Publish the message to the MQTT topic
        response = iot_client.publish(
            topic=mqtt_topic,
            qos=1,
            payload=json.dumps(message)
        )

        # Print the published message for logging
        print("Published message:", json.dumps(message))

        # Construct a success response
        response = {
            'statusCode': 200,
            'body': json.dumps({'message': 'Data received and published successfully!'})
        }
    except Exception as e:
        # Handle exceptions and construct an error response
        error_message = f'Error processing data: {str(e)}'
        print(error_message)

        response = {
            'statusCode': 500,
            'body': json.dumps({'error': 'Internal Server Error'})
        }

    return response