
# Hardware Architecture

## Brief Description
The final user can visualize information about safety level of the roads,squares and Urban Areas, through a web-app. Essentially each station got sensors like : `photoresistor`, `sound sensors` and `infrared` . The board through Network module will send data to the Gateway and then to the cloud.
  
Obviously when the system will be installed it will needs a configuration setup that pick up all the data and processing it to ensure a better rappresentation of the data


## Components

IOT Device composed of a `Nucleo -f401re Board` , `Power Source` , `LoRa` module and following Sensors:

- [*Nucleo -f401re Board*](https://www.st.com/en/evaluation-tools/nucleo-f401re.html) is a 32-bit ARM based microcontroller. The board will run RIOT OS used to make it as easy as possible the coding of network functionalities and sensor drivers

- [*Lora Extension kit*](https://www.st.com/en/evaluation-tools/i-nucleo-lrwan1.html) This board is an integrated solution allowing anyone to learn and develop solutions using LoRa® technologies.

- Photoresistors like [*CdS photoresistor*](https://www.adafruit.com/product/161) used to evaluate the Light level of the specific Road or square during night time

- InfraRed Sensors like [*TSOP38238*](https://www.adafruit.com/product/157) to extrapolate how many people will pass through that street within night time frames

- Sound Sensors like [*LM393*](https://components101.com/modules/lm393-sound-detection-sensor-module) capturing Loudness of that area Data Captured 

- Antenna like [*AntennaKit*](https://www.adafruit.com/product/3340) that use integrate LoPy LoRA, up to 900MHz 


# Network Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/IoTDiagram.png)

## Brief Description
> After extracting Ambient parameters from sensors,The stations evaluate instantaneously safety level of the surroundings

> Then it upload new status of the road exchanging messages over LoRa to the AWS Cloud Application

> Cloud act as MQTT broker and visualizator of data

> ***Message Passing*** As LoRaWan and IoT seems to have a good integration with AWS services


> ***Client*** can access the service and visualize safe areas through REST-HTTP protocol
