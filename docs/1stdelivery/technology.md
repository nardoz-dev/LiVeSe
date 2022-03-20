
# Hardware Architecture

## Brief Description
  > The final user can view all the system information with an webapp. Essentialy each station got sensore like : `photoresistor`, `sound sensors` and `infrared` , and has a gateway `raspberry pi3` that receives the data from the node and then send it to the cloud. 
  >
  >Obviously when the system will be installed it needs a configuration setup that pick up all the data and processing it.


## Components

IOT Device composed of a `Nucleo -f401re Board` , `Power Source` , `LoRa` module and following Sensors:

- [*Nucleo -f401re Board*](https://www.st.com/en/evaluation-tools/nucleo-f401re.html) is a 32-bit ARM based microcontroller. THe board will run RIOTOS used to make it as easy as possible the coding of network functionalities and sensor drivers

- Photoresistors like [*CdS photoresistor*](https://www.adafruit.com/product/161) used to evaluate the Light level of the specific Road or square during night time

- Passive Infrared Sensors like [*ZTP-135BS*](https://www.mouser.it/ProductDetail/Amphenol-Advanced-Sensors/ZTP-135BS?qs=w0nOqLG47DjVzY%252BqattwWw%3D%3D) to extrapolate how many people will pass through that street within night time frames

- Sound Sensors like [*TS-US-115-CA*](https://www.amazon.com/DAOKI-Sensitivity-Microphone-Detection-Arduino/dp/B00XT0PH10/ref=sr_1_3?keywords=Arduino+Sound+Sensor&qid=1647773484&sr=8-3) capturing Loudness of that area Data Captured 


Proxy consisting of [Rasberry pi 3 model B+](https://www.raspberrypi.com/products/raspberry-pi-3-model-b-plus/) computing initial row data including:
  - LoRa module 
  - MQTT-SN message broker 
  - Power By external source 


# Network Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/1stdelivery/pictures/IoTNetworkDiagram.png)

## Brief Description
> Our station communicate via MQTT over LORA. Each sensor node publishes over a different topic, one topic for one sensor. The gateway act as MQTT-SN broker.

> ProxyServer collect data from ambient sensor and push notification on the Amazon Web Service about safety.
