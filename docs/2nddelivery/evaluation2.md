## Energy consumption 

| **Products** | **Power Consume** | **Power Consume on StandBy** | 
| :---: | :---: | :---: | 
| `Nucleo -f401re` | 300mA max | 100mA | 
| `Pir HC-SR501` | ~1 mA while motion is detected | ~40-60µAµA | 
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

> The main constraint is energy consumption: We want the battery to last for at least one year. 

> However, Our initial approach is **Oversampling** : we don't know yet what is the *best sampling rate*, we need more testing to understand how dynamic can be our phenomena. We will try to decrease Active time as much as possible.

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


