import boto3
from decimal import Decimal
from datetime import datetime, timedelta

# Initialize DynamoDB resource
dynamodb = boto3.resource('dynamodb', region_name='ca-central-1')

# Lambda function handler
def lambda_handler(event, context):
    systemName = event['systemName']

    # Retrieve tables
    gateway_mappings_table = dynamodb.Table('GatewayTopicMappingsTable')
    gateway_node_table = dynamodb.Table(systemName + 'GatewayNodeTable')
    sensor_table = dynamodb.Table(systemName + 'SensorTable')

    # Fetch sensor names dynamically from the {SystemName}SensorTable
    response = sensor_table.scan()
    items = response['Items']
    
    # Sort items based on the 'ID' attribute
    sorted_items = sorted(items, key=lambda x: x['ID'])
    
    # Extract sensor names from sorted items
    sensor_names = [item['SensorType'] for item in sorted_items]

    print(sensor_names)

    # Create sensor tables dynamically
    sensor_tables = {sensor_name: dynamodb.Table(systemName + '_' + sensor_name + '_Table') for sensor_name in sensor_names}
    print(sensor_tables)

    # Query the GatewayMappingsTable to get data based on GatewayID and TopicName
    response = gateway_mappings_table.get_item(
        Key={
            'Topic': event['topicName']
        }
    )
    
    gateway_id = response['Item'].get('GatewayID', '')
    
    # Obtain the current date
    sensor_datetime = datetime.utcnow() + timedelta(hours=-5)
    sensor_datetime = sensor_datetime.strftime("%Y-%m-%d %H:%M:%S")

    # Create a dictionary to store sensor readings
    sensor_reading = {}

    # Iterate over sensor names and add readings to the sensor_reading dictionary
    i = 1
    for sensor_name in sensor_names:
        sensor_reading[sensor_name] = event.get(f'sensor{i}Reading')
        if sensor_reading[sensor_name] is not None:
            sensor_reading[sensor_name] = Decimal(sensor_reading[sensor_name]) / Decimal(100.00)
        i = i+1
        
    print(event['sensor1Reading'])
    print(event.get('sensor1Reading'))

    # Obtain node_id and parent_node_id
    node_id = event.get('currentNodeID')
    parent_node_id = event.get('parentNodeID')

    # Add gateway node to DynamoDB
    add_to_dynamodb(systemName + 'GatewayNodeTable', {
        'GatewayID': str(gateway_id),
        'NodeID': str(node_id),
        'ParentNodeID': str(parent_node_id)
    })

    # Put sensor readings into respective tables
    for sensor_name, reading_value in sensor_reading.items():
        print(sensor_name)
        print(reading_value)
        if reading_value is not None:
            sensor_tables[sensor_name].put_item(
                Item={
                    'NodeID': str(node_id),
                    'Time': str(sensor_datetime),
                    sensor_name + '_Reading': str(reading_value)
                }
            )

    return 0
    
# Function to add an item to DynamoDB table
def add_to_dynamodb(table_name, item):
    table = dynamodb.Table(table_name)
    try:
        table.put_item(Item=item)
        return True
    except Exception as e:
        if table_name == 'SystemToGatewayTable':
            print("System already added to Table")
            return False
        print(f"Error adding item to DynamoDB: {e}")
        return False