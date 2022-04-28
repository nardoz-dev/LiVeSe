## Description

*Each device got : `photo resistor`, `sound` and `infrared` sensor; Through Network module integrated inside the `STM32L0 Discovery kit` it will send **update** on the state of road-square to `The Things Network Infrastructure`.
Then `AWS` will be used to Visualize via `dashboard` and integrate `Google Maps` Navigation system*

## Wiring Architecture

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/STMLiVeSe.jpg)

## Components

- [*Nucleo -f401re Board*](https://www.st.com/en/evaluation-tools/nucleo-f401re.html) is a 32-bit ARM based microcontroller. The board will run RIOT OS used to make it as easy as possible the coding of network functionalities and sensor drivers

- [*Lora Expansion kit*](https://www.st.com/en/evaluation-tools/i-nucleo-lrwan1.html) This board is an integrated solution allowing anyone to learn and develop solutions using LoRa® technologies.

- Photoresistors like [*CdS photoresistor*](https://www.adafruit.com/product/161) used to evaluate the Light level of the specific Road or square during night time

- InfraRed Sensors like [*TSOP38238*](https://www.adafruit.com/product/157) to extrapolate how many people will pass through that street within night time frames

- Sound Sensors like [*LM393*](https://components101.com/modules/lm393-sound-detection-sensor-module) capturing Loudness of that area Data Captured 

## Duty Cycle 

Our devices will be active during **night-time** for at least *10 hours every day*. During this time They alternate from sleep to active mode.

During the active mode all the component in our device start to capture specific ambient variable. Each variable has an own weight based on the pull form that we do, in order to normalize it correctly. 
Furthermore, this data will be pass through our algorithm that process this data and extrapulate the main variable  : "LiVeSe-Security". 
In depth the algorithm put the sum of the light_value, pir_value, mic_value in our defined threeshold : 

    RED (Not Secure)        => Final value from 0 to 33
    ORANGE (Almost Secure)  => Final value from 33 to 67
    GREEN (Secure)          => Final value from 67 to 100.

### Accuracy of the PIR components

> PIR

The measure of how many people will pass through that street is taken by the PIR. Its accuracy can be an issue since the sensor will capt the data every 2 second. As a consequence it could happen that the pir can't detect effectively if a person pass or not in front of our station position.
So in order to avoid this problem, in the future we want to apply a servomotor to improve the gradation of the angle that the pir occupies.
Taking into account that the servo motor could probably have a greater impact in terms of consumption.


## Network 

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/NetDiagram.png)





