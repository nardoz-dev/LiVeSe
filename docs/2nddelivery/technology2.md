## Description

*Each device got : `photo resistor`, `sound` and `infrared` sensor; Through Network module integrated inside the `LoRa Discovery kit` it will send **update** messages on the state of the surroundings to `The Things Network` Infrastructure. After that messages will be forwarded to `AWS` and visualized via `dashboard` and integrated with `Google Maps` Navigation system*

## Wiring Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/STMLiVeSe.jpg)

## Components

- [*Nucleo -f401re Board*](https://www.st.com/en/evaluation-tools/nucleo-f401re.html) is a 32-bit ARM based microcontroller. The board will run RIOT OS used to make it as easy as possible the coding of network functionalities and sensor drivers

- Photoresistors [*GL 55 photoresistor*](https://www.kth.se/social/files/54ef17dbf27654753f437c56/GL5537.pdf) used to evaluate the Light level of the specific Road or square during night time

- InfraRed Sensors [*HC-SR501*](https://diyi0t.com/hc-sr501-pir-motion-sensor-arduino-esp8266-esp32/) to extrapolate how many people will pass through that street within night time frames

- Sound Sensors [*KY-037*](https://win.adrirobot.it/sensori/37_in_1/KY-037_KY-038-Microphone-sound-sensor-module.htm) capturing Loudness of that area Data Captured 


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

## Network 

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/2_NetDiagram.png)


We plan to update the data on the cloud each time the **LiveSe-Security variable changes**. This choice has been made considering the nature of the system which only needs to know the last measured LiveSe-Security. We’ll send to the cloud only our main variable, so we think that the bandwidth needed by each device is minimal. Having planned a **high update latency** implies fewer usage of the radio that can be turned off during sleep times saving energy.

We use LoRa communication protocol because of its low power consumption and long range. Its main constraint is the low bit rate but it is still suitable for our project.


## 
> Link to first delivery: [Technology](../1stdelivery/technology.md)

