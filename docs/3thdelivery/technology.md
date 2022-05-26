## Description

*Each device got : `photo resistor`, `sound` and `infrared` sensor; Through Network module integrated inside the `LoRa Discovery kit` it will send **update** messages on the state of the surroundings to `The Things Network` Infrastructure. After that messages will be forwarded to `AWS` and visualized via `dashboard` and integrated with `Google Maps` Navigation system*

## Wiring Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/STMLiVeSe.jpg)

## Components

- [*Nucleo -f401re Board*](https://www.st.com/en/evaluation-tools/nucleo-f401re.html) is a 32-bit ARM based microcontroller. The board will run RIOT OS used to make it as easy as possible the coding of network functionalities and sensor drivers

- Photoresistors [*GL 55 photoresistor*](https://www.kth.se/social/files/54ef17dbf27654753f437c56/GL5537.pdf) used to evaluate the Light level of the specific Road or square during night time

- InfraRed Sensors [*HC-SR501*](https://diyi0t.com/hc-sr501-pir-motion-sensor-arduino-esp8266-esp32/) to extrapolate how many people will pass through that street within night time frames

- Sound Sensors [*KY-037*](https://win.adrirobot.it/sensori/37_in_1/KY-037_KY-038-Microphone-sound-sensor-module.htm) capturing Loudness of that area Data Captured 

#### Solar Panel Recharge + Alimentation 
- [*Solar Panel with small cell : 12V 1.5W*](https://www.amazon.it/gp/product/B077JJPK63/ref=ox_sc_act_title_5?smid=A26FRN1T6ZMEY7&psc=1#HLCXComparisonWidget_feature_div) with output of ~125mA.
- [*Diodo 1N4007*](https://www.amazon.it/Haobase-100pcs-IN4007-DO-41-diodo-raddrizzatore-1000/dp/B01F4SQ6KU/ref=sr_1_10?__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=3F94J5XG8YXWE&keywords=diodo+n4007&qid=1653065288&sprefix=diodo+%2Caps%2C76&sr=8-10), 1A 1kV
- [*Voltage Step Up Boost Module USB Charger Blue DC-DC 0.9V-5V*](https://www.amazon.com/gp/product/B00HG9SB7C/ref=as_li_tl?ie=UTF8&camp=1789&creative=390957&creativeASIN=B00HG9SB7C&linkCode=as2&tag=opegreene-20&linkId=FNKWH7VYDJEAXPOM)
- [*BatteryPack AA x4 `Ni-MH` 1.2V 2000mAh*](https://www.amazon.it/AmazonBasics-Ricaricabili-precaricate-confezione-Involucro/dp/B00CWNMR5Y/ref=sr_1_8?__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=SMYI12E16FTB&keywords=batteria%2Baa%2Bricaricabile&qid=1653128512&sprefix=batteria%2Baa%2Bricaricabile%2Caps%2C79&sr=8-8&th=1)

## Requirements and Logic 

Our devices will be active during **night-time** for at least *10 hours every day*

- During this time They alternate sleep-active mode
- We want devices to last at least for **one year** before changing batteries 

We know that these devices will be mainly placed **in urban environments** :

- Our stations will be installed in **elevated positions** and sensors must be able to capture ambient sensors at a given distance with respect to the road
- sound sensor must capture noise and sound at least from 5-8 meters  
- PIR sensor needs to be accurate in measure number of people passing through the streets

Battery consumption is our greatest concern as well as **Sample Frequency**, having to be used to integrate a navigation system such as google maps 
 
- optimal Sample frequency needs to be found 

Battery and Network performance are limitations that needs to be addressed through further testing 


During active mode all the component in our device start to capture specific ambient variable. Each variable has an own weight based on the pull form that we do, in order to normalize it correctly. 
Furthermore, this data will be pass through our algorithm that process extrapolate the main variable  : `LiVeSe-Security` 
In depth the algorithm put the sum of the light_value, pir_value, mic_value in our defined threeshold : 

    RED (Not Secure)        => Final value from 0 to 33
    ORANGE (Almost Secure)  => Final value from 33 to 67
    GREEN (Secure)          => Final value from 67 to 100.

## Cloud Integration

We plan to update the data on the cloud each time the **LiveSe-Security variable changes**. This choice has been made considering the nature of the system which only needs to know the last measured LiveSe-Security. We’ll send to the cloud only our main variable, so we think that the bandwidth needed by each device is minimal. Having planned a **high update latency** implies fewer usage of the radio that can be turned off during sleep times saving energy.

![image](../sharedpictures/IntegrationAWS.png)

The thing network, Amazon Wes Services and Google Maps API defines all the cloud Integration with our project, these are the single modules we adopted

- the Thing network Console 
- the Thing Network MQTT Broker to AWS IoT Core
- AWS IoT Core Rule Engine
- AWS Lambda Function
- AWS CloudWatch
- AWS DynamoDB
- AWS API Gateway
- AWS Amplify
- Google Maps API

Firstly, **Uplink messages** from the end Devices reach the Lora gateway in TTN. Here they are forwarded to AWS IOT Core module through the MQTT broker. Once They are forwarded messages are stored inside AWS CloudWatch for logs and then modulated by AWS **IoT Rule Engine** in order to fit inside a table of the AWS DynamoDB;In particular we decided to treat the device-ID as the name of the Road/square where the device is located. Instead, the payload of the messages `frm_payload` bring the current state computed by the end device inside the AWS Environment as statusB64. Device EUI and time-stamp of the message are also extrapolated from the uplink message.

```sql
-- SQL query over TTN uplink message
SELECT end_device_ids.dev_eui as device_eui, end_device_ids.device_id as street, uplink_message.frm_payload as statusB64, received_at as time 
FROM 'lorawan/+/uplink'
```
Once the message is received by the IoT Core it's passed to a Lambda Function **[Decode64_update.py](/AWSlambdaFx/Decode64_update.py)**. Where `statusB64` is converted from Base64 to string before being insert inside the Database.

AWS Dynamo Database is composed by a single table `LiVeSeDB(devEUI,street,last_status,lat,long,status,timestamp)`

*devEUI* is the primary key of the table and street is the sorting key. Using these 2 keys every message is identified by its device and then inserted inside the DB; Information stored are then accessed by another Lambda function **[get_table.py](/AWSlambdaFx/get_table.py)** that expose all the table over an https-REST endpoint, acting as a public API **[LiVeSeDB API endpoint](https://42lal2bea7b5ufnq42umzkhxxy0zuhki.lambda-url.eu-west-1.on.aws/)**.
Finally, AWS Amplify module hosts a web dashboard where information from end devices are merged and visualized using the Google Maps APIs.

## Dashboard and Visualization


The dashboard is available **[here](https://master.d3coclnags0r33.amplifyapp.com/)**



## 
> Link to second delivery: [Technology](../2nddelivery/technology2.md)

