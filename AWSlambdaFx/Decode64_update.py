import json
import base64 
import boto3


client = boto3.client('dynamodb')

def lambda_handler(event, context):
    
    # Read message from SQL query 
    # create new road if new instance 
    # or upload status of existing street-square inside DynamoDB    
    
    base64_message = event['statusB64']
    base64_bytes = base64_message.encode('ascii')
    message_bytes = base64.b64decode(base64_bytes)
    status = message_bytes.decode('ascii')
    
    data = client.scan(
        TableName='LiVeSeDB',
    )
    
    past_status = ''
    
    for elem in data['Items']:
        if elem['DevEUI']['S'] == event['device_eui']:
            past_status = elem['status']['S']

# create new row if new road
    response = client.update_item(
        
        TableName='LiVeSeDB',
        ReturnValues = 'ALL_NEW',
        
        Key = {
            'DevEUI':{
                'S': event['device_eui'],
            },
            'street':{
                'S': event['street'],
            }
        },
        ExpressionAttributeNames={
            '#C' : 'status',
            '#LS': 'last_status',
            '#T' : 'timestamp',
            
        },
        ExpressionAttributeValues={
            ':current' : {
                'S' : status,
                },
            ':time' : {
                'S' : event['time'],
                },
            ':last_status': {
                'S' : past_status,
            }
        },
        UpdateExpression = 'SET #C = :current, #T = :time, #LS = :last_status'
        
    )
    
    
    return {
        'statusCode': 200,        
        }
