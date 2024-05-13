import boto3
import json
import logging
from botocore.exceptions import ClientError

# Initialize logger
logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

# DynamoDB configuration
dynamodb = boto3.resource('dynamodb', region_name='ca-central-1')
lambda_client = boto3.client('lambda')
iot_client = boto3.client('iot', region_name='ca-central-1')

# Lambda function handler
def lambda_handler(event, context):
    try:
        # Extract necessary information from the event
        gateway_name = event['thingName']
        system_name = event['systemName']
        topic = event.get("topic")
        access_key = event.get('ak')
        secret_access_key = event.get('sak')

        # Check if required credentials are provided
        if not access_key or not secret_access_key or not topic:
            return publish_unauthorized_message(topic, gateway_name)

        # Create AWS session using provided credentials
        session = boto3.Session(
            aws_access_key_id=access_key,
            aws_secret_access_key=secret_access_key
        )

        # Check IAM access
        iam = session.client('iam')
        iam.list_users()  # Check IAM access
        
        # Add system to gateway mapping
        add_to_dynamodb('SystemToGatewayTable', {'SystemID': system_name, 'GatewayID': gateway_name})
        added_to_table = add_to_dynamodb('GatewayTopicMappingsTable', {'Topic': topic, 'GatewayID': gateway_name})

        # Create gateway node table if not exist
        create_tables_if_not_exist(system_name + 'GatewayNodeTable', 'GatewayID', 'NodeID')

        # Fetch sensor types and create sensor table if not exist
        sensor_types = event.get('sensorTypes', [])
        sensor_id_to_name = query_sensor_mapping_table(sensor_types)
        gateway_sensor_table = system_name + 'SensorTable'
        create_tables_if_not_exist(gateway_sensor_table, 'ID', 'SensorType', 'N', 'S')

        # Create sensor tables if not exist
        if is_dynamodb_table_empty(gateway_sensor_table):
            i = 1
            for sensor_id, sensor_name in sensor_id_to_name.items():
                sensor_name = sensor_name.replace(" ", "_")
                table_name = f"{system_name}_{sensor_name}_Table"
                create_tables_if_not_exist(table_name, 'NodeID', sensor_name + '_Reading')
                add_to_dynamodb(gateway_sensor_table, {'ID': i, 'SensorType': sensor_name})
                i = i + 1

        # Create IoT rule if mapping added successfully
        if added_to_table:
            create_iot_rule(system_name)

        # Publish confirmation message
        return publish_confirmation_message(topic, gateway_name, added_to_table)

    except (ValueError, KeyError) as e:
        # Handle value and key errors
        logger.error(f"An error occurred: {str(e)}")
        return publish_unauthorized_message(topic, gateway_name)
    except ClientError as e:
        # Handle client errors
        error_code = e.response.get("Error", {}).get("Code")
        if error_code == "AccessDenied" or error_code == "InvalidClientTokenId":
            return publish_unauthorized_message(topic, gateway_name)
        else:
            logger.error(f"A client error occurred: {str(e)}")
            return {'statusCode': 500, 'body': json.dumps({'message': 'Internal Server Error'})}

# Function to add an item to DynamoDB table
def add_to_dynamodb(table_name, item):
    table = dynamodb.Table(table_name)
    try:
        table.put_item(Item=item)
        return True
    except ClientError as e:
        if e.response['Error']['Code'] == 'ConditionalCheckFailedException':
            logger.warning(f"Item already exists in table {table_name}")
        else:
            logger.error(f"Error adding item to DynamoDB: {e}")
        return False

# Function to publish a confirmation message
def publish_confirmation_message(topic, thing_name, added_to_table):
    iot_data_client = boto3.client('iot-data', region_name='ca-central-1')
    publish_topic = topic + '/authorized'
    message = f"Gateway {thing_name} initialized successfully." if added_to_table \
        else f"Gateway {thing_name} already initialized."
    response = iot_data_client.publish(
        topic=publish_topic,
        qos=1,
        payload=json.dumps({'message': message})
    )
    return {'statusCode': 200, 'body': json.dumps({'message': message})}

# Function to publish an unauthorized message
def publish_unauthorized_message(topic, thing_name):
    iot_data_client = boto3.client('iot-data', region_name='ca-central-1')
    topic = topic + '/unauthorized'
    message = f"Gateway {thing_name} has invalid credentials."
    response = iot_data_client.publish(
        topic=topic,
        qos=1,
        payload=json.dumps({'message': message})
    )
    return {'statusCode': 403, 'body': json.dumps({'message': message})}

# Function to create an IoT rule
def create_iot_rule(system_name):
    iot_client = boto3.client('iot', region_name='ca-central-1')

    rule_name = f'{system_name}Rule'
    
    topic_rules_list = iot_client.list_topic_rules()
    existing_rule_names = [rule['ruleName'] for rule in topic_rules_list['rules']]

    if rule_name in existing_rule_names:
        print(f"Rule {rule_name} already exists")
        return rule_name
    
    rule_sql = f"SELECT * FROM '{system_name}/#'"
    # the fumctionArn in the clients case would be the GatewayDataHandler Lambdas Arn an example is provided in this code.
    params = {
        'ruleName': rule_name,
        'topicRulePayload': {
            'sql': rule_sql,
            'actions': [
                {
                    'lambda': {
                        'functionArn': 'arn:aws:lambda:ca-central-1:343033164476:function:NewGatewayDataHandler',
                    },
                },
            ],
        },
    }
    

    try:
        print(f"Creating IoT rule: {params}")
        iot_client.create_topic_rule(**params)
        print(f"IoT rule '{rule_name}' created successfully.")
        create_lambda_permission_for_iot_rule(rule_name, 'NewGatewayDataHandler')
    except Exception as e:
        print(f"Error creating IoT rule: {str(e)}")
        raise e

    return rule_name
    
# Function to create a Lambda permission for an IoT rule
def create_lambda_permission_for_iot_rule(rule_name, lambda_function_name):
    lambda_client = boto3.client('lambda')

    statement_id = f"{rule_name}LambdaInvokePolicy"
    action = "lambda:InvokeFunction"
    principal = "iot.amazonaws.com"
    source_arn = f"arn:aws:iot:ca-central-1:343033164476:rule/{rule_name}"

    try:
        response = lambda_client.add_permission(
            FunctionName=lambda_function_name,
            StatementId=statement_id,
            Action=action,
            Principal=principal,
            SourceArn=source_arn
        )
        print(f"Lambda permission for IoT rule '{rule_name}' created successfully.")
    except Exception as e:
        print(f"Error creating Lambda permission: {str(e)}")
        raise e

# Function to query sensor mapping table
def query_sensor_mapping_table(sensor_ids):
    # Initialize DynamoDB client
    table_name = 'SensorTypes'  # Replace 'SensorTypes' with your DynamoDB table name

    # Initialize the DynamoDB table resource
    table = dynamodb.Table(table_name)

    # Initialize an empty dictionary to store sensor mappings
    sensor_id_to_name = {}

    # Query the table for each sensor ID
    for sensor_id in sensor_ids:
        try:
            # Get item from DynamoDB table based on sensor ID
            response = table.get_item(Key={'SensorID': sensor_id})
            print(response)
            
            # Check if the item exists and has the 'SensorName' attribute
            if 'Item' in response and 'SensorType' in response['Item']:
                sensor_name = response['Item']['SensorType']
                sensor_id_to_name[sensor_id] = sensor_name
        except Exception as e:
            print(f"Error retrieving sensor mapping for sensor ID {sensor_id}: {str(e)}")
            
    print(sensor_id_to_name)

    return sensor_id_to_name

# Function to create tables if they don't exist
def create_tables_if_not_exist(table_name, primary_key, partition_key, primary_key_type='S', partition_key_type='S'):
    try:
        table = dynamodb.create_table(
            TableName=table_name,
            KeySchema=[
                {
                    'AttributeName': primary_key,
                    'KeyType': 'HASH'  #Partition_key
                },
                {
                    'AttributeName': partition_key,
                    'KeyType': 'RANGE'  #Sort_key
                }
            ],
            AttributeDefinitions=[
                {
                    'AttributeName': primary_key,
                    'AttributeType': primary_key_type
                },
                {
                    'AttributeName': partition_key,
                    'AttributeType': partition_key_type
                }
            ],
            ProvisionedThroughput={
                'ReadCapacityUnits': 10,
                'WriteCapacityUnits': 10
            }
        )
        print(f'{table_name} created')
    except ClientError as e:
        if e.response['Error']['Code'] == 'ResourceInUseException':
            print(f"Table '{table_name}' already exists.")
        else:
            print(f"An error occurred: {e}")

# Function to check if a DynamoDB table is empty
def is_dynamodb_table_empty(table_name):
    table = dynamodb.Table(table_name)
    
    response = table.scan()
    items = response.get('Items', [])
    
    return len(items) == 0
