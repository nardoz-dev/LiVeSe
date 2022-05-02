## Energy consumption 

| **Products** | **Power Consume** | **Power Consume on StandBy** | 
| :---: | :---: | :---: | 
| `Nucleo -f401re` | 146µA max | 2.4µA | 
| `Pir HC-SR501` | ~1 mA while motion is detected | ~40-60µA | 
| `Mic KY-037` | ~1 mA | ~0 mA | 
| `Photoresistor like GL5516` | ~0mA |  ~0mA | 

We try to gain a more efficient measurement about power energy with a specific tool like ammeter. We put two boards on series and evaluate what's the power consumption of the board. The output of our ammeter says that we consume *0,004A = ~4mA*. The main problem about this measure is that our ammeters give this results only if it's on a large scale of unit and so we think that it's broken.

```
66000mAh Battery Capacity (3xAAA)
~4mA      Max Consumption
==
1650h Max Battery Life

expected ~10h of Duty time every day
```

|sleep-active cycle (sec)  |active time every h | active hours 1 day | Expected Battery Life |
|--|--|--|--|
|0-60 |60m|10h | 68 days |
|2-4|40m|6.6h | 250 days |
|4-2|20m|3.3h | 500 days |

So in order to estimate the value of our total energy consumption, we try to obtain the data sheet of our all component but not all components are available.

- The main constraint is energy consumption: We want the battery to last for at least one year.

However, Our initial approach is **Oversampling** : we don't know yet what is the *best sampling rate*

- We need more testing on *real scenarios* in order to understand how dynamic can be our phenomena. We will try to decrease Active time as much as possible for the next delivery

For now, we decide to read from each device every 2 seconds, and the board go to sleep mode for 4 seconds.

We Tried to experiment with FIT IOT lab and the average consumption was of *0.018A = ~18mA* as shown :

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/iotLabv2.jpg)

under the same cycle (2-4):
```
66000mAh Battery Capacity (3xAAA)
~18mA      Max Consumption
==
366.4h Max Battery Life (6 days)
expected ~10h of Duty time every day
6.6h of active hours every day
==
50 days Expected Battery Life
```
|sleep-active cycle (sec)  |active time every h | active hours 1 day | Expected Battery Life |
|--|--|--|--|
|2-4|40m|6.6h|50 days|

## Accuracy of the PIR component

The measure of how many people will pass through streets is taken by the PIR. Its accuracy can be an issue since the sensor will keep the data every 2 second. 
As a consequence it could happen that the PIR can't detect effectively if a person pass or not in front of our station position.

So in order to avoid this problem, in the future we want to apply a servo-motor\stepper-motor to improve the gradation of the angle that the PIR occupies.
Taking into account that could probably have a greater impact in terms of consumption.

## KY-037 microphone 

We tried to use this sensor in order to gain a good sample of sound in the surrounding. However, this sensor seems to be made from low quality components: even if it is considered as a sensor module with 'high sensitivity' it is not able to perceive sounds or noise farther than a few centimeters 

- We are currently searching for a new one 

## LoRa Discovery Kit

We encountered errors related to the **ADC-line** used by analog sensors when dealing with the Lora Discovery board, this has blocked our tests of network and slowed down integration with cloud services

 - We were not able to make further test on the physical board 

## Integration with Cloud Services 

The state of our integration with Cloud services is the following :

- We successfully be able to communicate with The Thing Network and AWS with our device 
- However we decide to concentrate our effort in the making of the device
  - We expect to complete the integration for the next delivery

##

> Link to first delivery [Evaluation](../1stdelivery/evaluation.md)
