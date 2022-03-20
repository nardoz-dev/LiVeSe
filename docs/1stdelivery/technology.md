

# Hardware Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/1stdelivery/pictures/IoTDiagram.png)

## Brief Description
  > The final user can view all the system information with an webapp. Essentialy each station got sensore like : `photoresistor`, `sound sensors` and `infrared` , and has a gateway `raspberry pi3` that receives the data from the node and then send it to the cloud. 
  >
  >Obviously when the system will be installed it needs a configuration setup that pick up all the data and processing it.


## Components
> IOT Device composed of a Nucleo -f401re Board , Power Source , LoRaWAN module and following Sensors:
>Photoresistors like xxxx used to evaluate the Light level of the specific Road or square during night time
... descr of specific model....
> Passive Infrared Sensors like xxxx to extrapolate how many people will pass through that street within night time frames
... descr of specific model....
> Sound Sensors like xxxx capturing Loudness of that area 
Data Captured 
... descr of specific model....

>Rasberry pi model xxx as Proxy/Gateway consisting of 
- LoRa module 
- running a MQTT message broker 
- computing initial row data 
- Power By external source 


# Network Architecture

IOT device will communicate with the gateway 

