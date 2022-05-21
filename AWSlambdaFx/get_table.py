import json
import boto3

# extract table
client=boto3.client('dynamodb')

def lambda_handler(event, context):
    
    data = client.scan(
        TableName='LiVeSeDB',
    )
    
    return {
        'statusCode': 200,
        'body': json.dumps(data["Items"])
    }