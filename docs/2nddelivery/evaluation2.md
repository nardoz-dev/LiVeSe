# Energy consumption 

The main constraint is energy consumption. We want the battery to last for at least one year. Our assumption is that we read from each device every 2 seconds, and the board go to sleep mode for 4 seconds. This loop will start only on the night and not on 24/24h and it's active for at least 10 hours every day. 
When the station is on :
- Pir each 2 seconds goes on and need to compute how many people pass through the street.
- The Mic each 2 seconds goes on and try to catch the noyse of the street.
- The Photoresistor each 2 seconds goes on and try to catch the light of the street.


| **Products** | **Power Consume ** | **Power Consume on StandBy** | 
| :---: | :---: | :---: | 
| `Nucleo -f401re` | 300mA max | 100mA | 
| `Pir HC-SR501` | ~1 mA while motion is detected | ~40-60µAµA | 
| `Mic KY-037` | ~1 mA | ~0 mA | 
| `Photoresistor like GL5516` | ~0mA |  ~0mA | 


We try to gain a more efficient measurement about power energy with a specific tool like ammeter. We put two board on series and evaluate what's the power consumption of the board. The output of our ammeter says that we consume 0,004A = ~4mA. The main problem about this measure is that our ammeters give this results only if it's on a large scale of unit and so we thinking that it's broken.

So in order to "estimate" the value of our total energy consumption, we try to obtain the datasheet of our all component. After we got the power consumption of the all component that we use we estrapulate the complessive power consumption of our device.

##Analysis

