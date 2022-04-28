# Energy consumption 

The main constraint is energy consumption: We want the battery to last for at least one year.
However, our initial approach is **Oversampling**. We read from each device every 2 seconds, and the board go to sleep mode for 4 seconds.
```


(active time of XXm in 1h)  x 10h a day : 

200 m per 1 gg === 3.3h al giorno attivo


 68 giorni (full 1h)  10h x gg
 250 giorni   (40m x 1h) 6.6h x gg
 550 giorni    (20m x 1h)  3.3h x gg 


66000 mah 
4 mah  
==
1650 Hours

```
The device is on duty during the night and not 24h. At least for *10 hours every day*. 
When the station is active :
- PIR : each 2 seconds goes on and need to compute how many people pass through the street.
- Mic : each 2 seconds goes on and try to catch the noise of the street.
- Photoresistor : each 2 seconds goes on and try to catch the light of the street.


| **Products** | **Power Consume ** | **Power Consume on StandBy** | 
| :---: | :---: | :---: | 
| `Nucleo -f401re` | 300mA max | 100mA | 
| `Pir HC-SR501` | ~1 mA while motion is detected | ~40-60µAµA | 
| `Mic KY-037` | ~1 mA | ~0 mA | 
| `Photoresistor like GL5516` | ~0mA |  ~0mA | 


We try to gain a more efficient measurement about power energy with a specific tool like ammeter. We put two boards on series and evaluate what's the power consumption of the board. The output of our ammeter says that we consume 0,004A = ~4mA. The main problem about this measure is that our ammeters give this results only if it's on a large scale of unit and so we think that it's broken.

So in order to estimate the value of our total energy consumption, we try to obtain the data sheet of our all component.

------After that we got the power consumption of all the component that we use we estrapulate the complessive power consumption of our device.

## Duty Cycle analysis 

per ora Oversampling 
110 gradi ci consente di seguirla .   
oversampling xche non sappiamo ancora quanto ci serve . anche se consumiamo di piu'


