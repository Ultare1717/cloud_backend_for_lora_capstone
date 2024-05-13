import requests
from time import sleep
from datetime import datetime, timedelta
from elasticsearch import Elasticsearch

# Global Settings
ELASTICSEARCH_LINK = "http://localhost:9200"
SYSTEM_NAME = "TestSystemDemo18"
CLEAR_ES = True
MAX_ENTRIES_SENT_IN_ONE_ITERATION = 1000
ES_REFRESH_TIME = 30

def get_data_from_aws():
    url = f"https://0q3f91nb63.execute-api.ca-central-1.amazonaws.com/prod/sensordata?systemName={SYSTEM_NAME}"

    try:
        # Send a GET request to the API
        response = requests.get(url)

        # Check if the request was successful (status code 200)
        if response.status_code == 200:
            # Convert the response to JSON format
            data = response.json()

            # Process the retrieved data
            print("Data retrieved successfully")
            return data
        else:
            # If the request was not successful, print the error code
            print(f"Error: {response.status_code}")
            return None
    except Exception as e:
        # Handle exceptions, if any
        print(f"An error occurred: {str(e)}")

# Helper Function to delete all values in a given index
def delete_es_index(es, index_name):
    try:
        response = es.indices.delete(index=index_name)
        print(f"Index '{index_name}' deleted successfully.")
    except Exception as e:
        print(f"Failed to delete index '{index_name}': {e}")

# Helper Function to delete an index pattern
def delete_index_pattern(auth, index_pattern_name):
    base_url = "http://localhost:5601"

    url = f"{base_url}/api/saved_objects/index-pattern/{index_pattern_name}"
    headers = {
        "kbn-xsrf": "true",
    }
    response = requests.delete(url, headers=headers, auth=auth)
    
    if response.status_code == 200:
        print("Index pattern deleted successfully.")
    else:
        print(f"Failed to delete index pattern. Status code: {response.status_code}")
        print(f"Response content: {response.text}")

# Helper Function to create an index pattern
def create_index_pattern(auth, index_pattern_name, sensor_names):
    base_url = "http://localhost:5601"

    url = f"{base_url}/api/saved_objects/index-pattern/{index_pattern_name}"
    headers = {
        "kbn-xsrf": "true",
        "Content-Type": "application/json",
    }

    # Generate the dynamic fields part of the query
    dynamic_fields_part = ',\n'.join([
        f'{{"name":"{sensor}","type":"float","count":0,"scripted":false,"searchable":true,"aggregatable":true,"readFromDocValues":false}}'
        for sensor in sensor_names
    ])

    # Static fields for 'node' and 'gateway'
    static_fields_part = """\
        {"name":"node","type":"string","count":0,"scripted":false,"searchable":true,"aggregatable":true,"readFromDocValues":false},
        {"name":"gateway","type":"string","count":0,"scripted":false,"searchable":true,"aggregatable":true,"readFromDocValues":false}
    """

    # Combine dynamic and static fields
    fields_part = f"[{dynamic_fields_part},\n{static_fields_part}]"

    # Create the data dictionary
    data = {
        "attributes": {
            "title": index_pattern_name,
            "timeFieldName": "@timestamp",  # Specify the time field name if applicable
            "fields": fields_part
        }
    }

    response = requests.post(url, json=data, headers=headers, auth=auth)
    
    if response.status_code == 200:
        print("Index pattern created successfully.")
    else:
        print(f"Failed to create index pattern. Status code: {response.status_code}")
        print(f"Response content: {response.text}")

# Helper Function to retrieve the latest entry registered in es
def retieve_latest_time_in_es(es, node):
    query = {
        "query": {
            "bool": {
                "must": [
                    {"match": {"node": node}}
                ]
            }
        },
        "sort": [
            {"@timestamp": {"order": "desc"}}
        ],
        "size": 1
    }

    try:
        # Execute the search
        search_result = es.search(index=SYSTEM_NAME.lower(), body=query)

        # Get the latest time entry
        latest_entry = search_result['hits']['hits'][0]['_source']['@timestamp']

        return datetime.strptime(latest_entry, "%Y-%m-%dT%H:%M:%S") + timedelta(hours=5)
    except Exception:
        return None

# Helper Function to update the es index with the provided data
def update_es_data(es, data):
    processed_data = {}
    for sensor_type in data:
        for entry in data[sensor_type]:
            if entry["NodeID"] not in processed_data:
                processed_data[ entry["NodeID"] ] = {}
            if entry["Time"] not in processed_data[ entry["NodeID"] ]:
                processed_data[ entry["NodeID"] ][ entry["Time"] ] = {}
            sensor_reading = float(entry[f"{sensor_type}_Reading"])
            processed_data[ entry["NodeID"] ][ entry["Time"] ][sensor_type] = sensor_reading

    for _, node in enumerate(processed_data):
        all_node_sensor_data = processed_data[node]
        latest_timestamp_in_es = retieve_latest_time_in_es(es, node)

        reversed_items = reversed(list(all_node_sensor_data.items()))
        for index, (date, node_sensor_data) in enumerate(reversed_items):
            if index == MAX_ENTRIES_SENT_IN_ONE_ITERATION:
                break

            timestamp = datetime.strptime(date, "%Y-%m-%d %H:%M:%S") + timedelta(hours=5)

            if latest_timestamp_in_es and timestamp <= latest_timestamp_in_es:
                # print(f"NEW TIMESTAMP: {timestamp}")
                continue

            node_sensor_data["@timestamp"] = timestamp.strftime("%Y-%m-%dT%H:%M:%S")
            node_sensor_data["node"] = node
            node_sensor_data["gateway"] = "gateway_1"
            # print(node_sensor_data)

            res = es.index(index=SYSTEM_NAME.lower(), body=node_sensor_data)


def main():
    # Connect to ES
    auth = ('elastic', input("Enter Password For ES: "))
    es = Elasticsearch(ELASTICSEARCH_LINK, basic_auth=auth)
    if CLEAR_ES:
        delete_es_index(es, SYSTEM_NAME.lower())
    
        data = None
        while not data:
            data = get_data_from_aws()
            if data is None:
                sleep(ES_REFRESH_TIME)
        
        delete_index_pattern(auth, SYSTEM_NAME.lower())
        create_index_pattern(auth, SYSTEM_NAME.lower(), data.keys())

    while True:
        # Update the ES instance with the up-to-date values from firebase
        print("Updating ES...")
        data = get_data_from_aws()

        # Update the es index if data exists
        if data is None:
            print("AWS DB is empty")
        else:
            update_es_data(es, data)

        print("Sleeping until refresh time is up")
        sleep(ES_REFRESH_TIME)


if __name__ == "__main__":
    main()