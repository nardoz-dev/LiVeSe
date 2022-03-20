
# Hardware Architecture

## Brief Description
  > The final user can view all the system information with an webapp. Essentialy each station got sensore like : `photoresistor`, `sound sensors` and `infrared` , and has a gateway `raspberry pi3` that receives the data from the node and then send it to the cloud
  >
  >Obviously when the system will be installed it needs a configuration setup that pick up all the data and processing it


## Components

IOT Device composed of a `Nucleo -f401re Board` , `Power Source` , `LoRa` module and following Sensors:

- [*Nucleo -f401re Board*](https://www.st.com/en/evaluation-tools/nucleo-f401re.html) is a 32-bit ARM based microcontroller. THe board will run RIOT OS used to make it as easy as possible the coding of network functionalities and sensor drivers

- Photoresistors like [*CdS photoresistor*](https://www.adafruit.com/product/161) used to evaluate the Light level of the specific Road or square during night time

- InfraRed Sensors like [*TSOP38238*](https://www.adafruit.com/product/157) to extrapolate how many people will pass through that street within night time frames

- Sound Sensors like [*LM393*](https://components101.com/modules/lm393-sound-detection-sensor-module) capturing Loudness of that area Data Captured 

- Antenna like [*AntennaKit*](https://www.adafruit.com/product/3340) that use integrate LoPy LoRA, up to 900MHz 


# Network Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/IoTDiagram.png)

## Brief Description
> Our station communicate via MQTT over LORA. Each sensor after extracting Ambient parameters from sensors, evaluate instantaneously safety level of the road-square. 

> Then it upload new status of the road on the Amazon Web Service

> Cloud act as MQTT-SN broker and visualizator of data

> Client can access the service through REST HTTP protocol
