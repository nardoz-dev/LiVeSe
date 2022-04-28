## Description

*Each device got : `photo resistor`, `sound` and `infrared` sensor; Through Network module integrated inside the `STM32L0 Discovery kit` it will send **update** on the state of road-square to `The Things Network Infrastructure`.
Then `AWS` will be used to Visualize via `dashboard` and integrate `Google Maps` Navigation system*

## Wiring Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/STM%LiVeSe.jpg)

## Components

IOT Device composed of a `Nucleo -f401re Board` , `Power Source` , `LoRa` module and following Sensors:

- [*Nucleo -f401re Board*](https://www.st.com/en/evaluation-tools/nucleo-f401re.html) is a 32-bit ARM based microcontroller. The board will run RIOT OS used to make it as easy as possible the coding of network functionalities and sensor drivers

- [*Lora Expansion kit*](https://www.st.com/en/evaluation-tools/i-nucleo-lrwan1.html) This board is an integrated solution allowing anyone to learn and develop solutions using LoRa® technologies.

- Photoresistors like [*CdS photoresistor*](https://www.adafruit.com/product/161) used to evaluate the Light level of the specific Road or square during night time

- InfraRed Sensors like [*TSOP38238*](https://www.adafruit.com/product/157) to extrapolate how many people will pass through that street within night time frames

- Sound Sensors like [*LM393*](https://components101.com/modules/lm393-sound-detection-sensor-module) capturing Loudness of that area Data Captured 

- Antenna like [*AntennaKit*](https://www.adafruit.com/product/3340) that use integrate LoPy LoRA, up to 900MHz 


## Duty Cycle - LOgics

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/IoTDiagram.png)


> After extracting Ambient parameters from sensors, the stations evaluate instantaneously safety level of the surroundings

> Then it upload new status of the road exchanging messages over LoRa to the AWS Cloud Application

> Cloud act as MQTT broker and visualizator of data

> ***Message Passing*** As LoRaWan and IoT seems to have a good integration with AWS services


> ***Client*** can access the service and visualize safe areas through REST-HTTP protocol







