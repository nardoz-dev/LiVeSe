# Evaluation

## Requirements: 

In our project we have four important requirements. All of them are specific for our porpuse, and can upgrade the efficiency of our system.

> 1. No Battery constraint!
> 2. Better Accuracy of the PIR!
> 3. Better Sample Frequency Rate
> 4. Small Network Usage.

1. The Battery constraint is an interesting point, because it takes into account the lifetime of our battery due to the constraint of the power consumption of the sensors installed in our device. In fact in order to improve the battery lifetime expectation of our device, we supposed to install a solar panel system. Of course we need to study how and what kind of solar panel we need to install for our purpose. Below we take into account a more detailed explanation [about that](#energy-consumption). 
2. Since the purpose of our PIR is to measure if a specific road is crowded or not, we use our sampling and algorithm idea in order to have an efficient evaluation of the data that has been readed from the component. [Here](#pir-accuracy) you can see the details. 
3. Sample Frequency Rate is very important because if it is small it can causes high peak of energy loss consumption, if it is too hight the purpose of the device can't be reached so it would be useless. Details [here](#sampling-frequency-analysis)
4. Of course also the size of the packet that we want to send over the internet need to be small, fast, and we want to avoid latency as much as possibile. [Details](#network-usage)

## Energy consumption 

#### What we found by visiting datasheet for each components : 

| **Products** | **Power Consume** | **Power Consume on StandBy** | 
| :---: | :---: | :---: | 
| `B-L072Z-LRWAN1` | 146µA | 2.4µA | 
| `Pir HC-SR501` | ~1 mA while motion is detected | ~40-60µA | 
| `Mic KY-037` | ~1 mA | ~0 µA | 
| `Photoresistor like GL5516` | ~0 µA |  ~0 µA | 

The major constraint that we have is energy consumption.
We try to gain a more efficient measurement about power energy with a specific tool like an ammeter with two boards on series and evaluating the current taken in input of the second board, where the first one is equipped with all the sensors. The output of our ammeter says that we consume *0,004A = ~4mA*. The main problem about this measure is that our ammeters give this results only if it's on a large scale of unit without fusibile.


#### This instead is a measure for the expectation lifetime of our devices that is power on with 3 battery AAA NiMh.

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

So, to estimate the value of the energy consumed, we used the information provided by the components datasheet.

#### Dissatisfied with the result we tried to experiment with FIT IOT lab and the average consumption was of *0.018A = ~18mA* as shown :

![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/2_IoTLabTest2.jpg)

under the same cycle (2 sleep mode off - 4sleep mode on):
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

The first way to improve the lifetime is to introduce something to produce energy.

## Solar Panel for Battery!

The main drawback of battery operated device is that it will be depleted after a certain time. This drawback can be eliminated by using natural resources like solar, wind or hydro energy. The most free source of energy to recharge the battery is solar energy. It is a relatively simple and cheap.

So we need to undestand first the type of battery, the common battery device are NiMH and Li-Ion. 
The first difference is that Li-Ion battery deliver higher voltage power than the NiMH.
The first facts to understand for battery charging is the thumb rule of 1/10th (commonly know as C/10). That means to charge the battery pack at 1/10th its rated current requires 16 hours of charge time. 

#### C/10 Rule 
Is a simple rule, for example if we have a 2xAA-sized 1300mAh battery pack 1.2V per cell, with cells in series, our pack output is 2.4V and 1300mAh. 
So we need to do this simple calculation :  
- C = 1300mAh
- C/10 = 130mAh
So to charge the above battery pack we need a higher voltage (2.4 to 3V) with a maximum current of 130mAh. In this example we need 16 hours to fully charge the battery pack. 

If we increase the current given by the C/10 rule the batteries will suffer a decreased lifetime.

#### Choose of solar panel
The main source for powering the sensor module is a solar panel. So it must be able to provide current for powering the board as well as current to charge the battery pack during the day. To choose the correct voltage of the panel we need to follow two simple tricks: 

> 1. Voltage : Choose 1.5 times the battery pack voltage (it is not an obligation it is only a recommendation)

> 2. Current : must be the current taken by the board plus the current for charging.

If we follow this simple tricks, in our case we use four battery AA (1.2 cad.) in series, that means we have 4.8V and the required voltage for solar panel is : 4.8 * 1.5 = ~7.2V. The quantity of current that the solar panel must generate is the current cost of the board ( previusly estimated to 100mA and the current needed to charge the battery pack : 2000mAh : C/10 Rule => 200mAh for a total to 300mAh).

#### Choose the type of battery 
As said before, this is a little problem, but don't worry we can use the same circuit to recharge NiMh and Li-Ion battery. The problem stands only for the Li-Ion batteries :
> You must take certain precautions when dealing with Lithium Ion Batteries. In order to maintain a very precise voltage when charging. For example the 4.8V batteries we're using need to have a charging volt of 7.2V. A vdifferent voltage  mean an out of control chemical reaction, which can lead to danger!

To resolve this problem it is possible to use Lithium Battery Charging Board that has the recharge protection. There are a lot of type of Lithium Battery Charging Boards, all turns off when finished to recharge the battery. The integrated protection circuit protects against overvoltage and polarity reversal. For that is important the wiring connection.

So to avoid this kind of problems with Li-Ion batteries we decided to switch to the Ni-MH.

So essentialy with this configuration we can no longer think about the problem of expected lifetime, again as we have installed an auto-energetic system. The most important difficulty is when for 1 month every day never appear the sun, but in on a realistic scenario there's a low possibility that it could happened. But if it's happened we can keep our device alive at most for 50 days if the battery are full charged.

## Sampling Frequency analysis

To compute our **environmental variable** we tried different approaches:
- Constant Sampling :
- -  It's the simplest one. In this case obviously we got the more accurate results but our lifetime cycle goes down to a few weeks, and the battery goes down very fast! Moreover, continuous sensing does not make much sense in our case, for example if we put our devices on a isolated street, the clamping of the output value it will be ever the same, so it doesn't make sense.
- Defined Sampling time
- - To do this we studied some real life cases: how much time a person need to pass through a distance of 20 meters?(the distance that our PIR can cover at a given distance with an angle of 110 degree) so we switched to a Sampling time of 7 seconds, constant, alternating 7 seconds of sleep and some milliseconds of running mode for the whole night. Clearly the power consumption was much better. Even in this case is not a very efficent solution because if we put a defined sampling time it could happen that the "off" period coincides with the moment in which a person walks in front of the device so the output of devices not changes but actually the road could be safer than first.
- Variable Sampling Time(No ML):
- - At this point we figured out that the variables that we measure don't change rapidly,so,why sample every 7 seconds without any reason? There are a lot of possible ways here,and we are still triying some of them to understand what fit better for our purpose. On of the idea is to use an very simple internal algorithm that store an aux variable for the last output, and compare it with other small parameters like a counter of the same hit output results.

### PIR Accuracy
The approaches that we tested more and seems more interesting are two:
- Pir Counter
- - In this approach the PIR Scan every 10 seconds to be accurate but in this case if he detects someone his thread initialize a counter that will stop the scanning time: this because we **DONT WANT TO COUNT HOW MANY PEOPLE passing through but we want to measure IF A SPECIFIC ROAD IS CROWDED OR NOT,** in principle we chosed the wrong approach cause of the accuracy of the testing,we don’t expect to detect all of the person,but THE TIME THAT “intercor” BETWEEN THE TWO EVENTS! 
Same principle for the photoresistor,a defined sampling rate doesn’t fit at all in this project,in this case we got the best results storing in a Variable the last value read,if them match the sampling rate become higher,obviusly with a maximum critical value.
At this point it’s really important specify that we explicity decided to avoid do ML because it need to add another layer on our networking,this only to do Federeting ML.
- RoadHistorySampling:
- - In this scenario we increment the sampling time based on the results given by the whole ambient scan. This works very well with light and noise,because of the semi-costant intrinsic nature of them,for the PIR it works very bad,in the worst case scenario is possible to don’t detect for a whole night cause of the sampling rate even lower.

## Network Usage

This architecture does not have any particular network constraint, because we planned to send data to the cloud only when the "SECURITY" level changes. And even if the security level changes, our board will send only a simple value that stand for : red - yellow - green. However, we must take into account that a lot of devices can send the value but should be supported by the gateway infrastructure. 

### Packets and Payload Size 

Taking into account our implementation, we sent a LoRa message with a payload of 3byte. Considering that a normal LoRa packet use 13 bytes as header, we have 16bytes of the toal packet size. Using the calculator provided by The Things Network we obtained that the Time on Air of a packet is 51.5 ms. 
We should improve better the Time on Air of the packet, considering to send only a LoRa message with a payload of 1byte. 


## Future improvements

We are still developing the one that in our idea is the best one,add a “bidirectional channel” using LoraWan,in this case we will be able to compute on the cloud,even with ML that obviusly performs better than a simple local logic AND allow us to develop a brand new feature,adapt the sampling rate on specific days,e.g. 1st of January,and even specific period,e.g. Covid-19 pandemic “”COPRIFUOCO”” and as a possibility,restart the board using Lora,generate Interrupt and a lot more.

The `dashboard` is under development as u can see there, we managed to integrate the google api.
![image](../sharedpictures/Dashboard.jpg)

The last important improvements it's the `mic sensor`. In our system we use the KY-037, but with this components we have a huge problems. This mic can listen only BIG CHANGE of volume, and for our purposes it is not so useful, because we should be able to "detect" the sound of the human voice. We tried replacing the microphone with "SPH04645 I2S Mic " but in this case is very hard to handle this component with the riot documentation. We still try it but it requires a lot of time.

The measure of how many people will pass through streets is taken by the `PIR`. Its accuracy can be an issue since the sensor will keep the data every 2 second.  As a consequence it could happen that the PIR can't detect effectively if a person pass or not in front of our station position.
So in order to avoid this problem, in the future we want to apply a servo-motor\stepper-motor to improve the gradation of the angle that the PIR occupies. Or maybe we could put more PIRS arranged sequentially but the problem goes to the wiring. 

##

> Link to second delivery [Evaluation](../2nddelivery/evaluation2.md)
