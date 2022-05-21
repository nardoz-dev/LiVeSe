# AWS Integration

 ![image](../docs/sharedpictures/IntegrationAWS.png)

Uplink messages from The Thing Network are forwarded into IOT core module of AWS environment
```sql
-- SQL query over TTN message
SELECT end_device_ids.dev_eui as device_eui, end_device_ids.device_id as street, uplink_message.frm_payload as statusB64, received_at as time 
FROM 'lorawan/+/uplink'
```
IOTcore select some fields from the uplink message and pass it to CloudWatch logs and Lambda function for decoding of status and insertions in the DynamoDB of the new Device

> [Decode64_update.py](/AWSlambdaFx/Decode64_update.py)

LiVeSeDB is composed by single table with attributes: `devEUI,street,last_status,lat,long,status,timestamp`

Device information can be accessed by another Lambda function over a public API 

> [get_table.py](/AWSlambdaFx/get_table.py)

> [LiVeSeDB API endpoint](https://42lal2bea7b5ufnq42umzkhxxy0zuhki.lambda-url.eu-west-1.on.aws/)

Finally, AWS Amplify service allow us to host a simple Web App that merge device information with Google maps API for visualization of street status and location
