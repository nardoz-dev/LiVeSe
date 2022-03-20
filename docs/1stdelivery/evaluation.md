# Evaluation

The goal of this document is to providing information about "evalutation" of Project. This evaluation is based on the follow constraints:
  - The evaluation of the performance of the network technologies.
  - The evaluation of the performance of the embedded devices in terms of power consumption and energy efficiency.
  - The evaluation of the response time from an end-user point of view.

## Performance Evaluation

Performance evaluation mainly concerns two aspects: evaluation of the performance of the cloud infrastructure and evaluation for the physical characteristics of the devices.

### Network Evaluation

#### LoRa

We provide the use of this tools : [`AirTime calculator`](https://avbentem.github.io/airtime-calculator/ttn/eu868/51) for LoRaWAN to calculate and optimize our airtime for a longer battery life and less gateway utilization.

> *Ipotethical tool test results *[^1]*:*
> ![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/LoraToolTest.png)

#### AWS
> Amount of Data collected, data rates exchanges with cloud platform and related Cost 

#### Devices

> packets lost/data Rate and Antenna Consumption.
> Node computation of instant data and subsequent sent

### Power consuming and energy efficiency

Station power constraints:



Each devices,drain energy on battery,so we must try to lighten as much as possible the workload on the station to avoid an overcharging of the battery. This can be done appropriately calculating sensing and sending times: fewer detections possible, fewer deliveries possible, lower will be the consumption
To be on,the station needs more or less an 5Volt on input.

| **Products** | **Power Consume on Active** | **Power Consume on Idle** |
| :---: | :---: | :---: |
| `Nucleo -f401re` | 300mA max | 100mA |
| `Infrared ZTP-135BS` | 0.45mA | 0.27mA |
| `SoundSensors TS-US-115-CA` | 4~5 mA | 4~5 mA |
| `Antenna` | 500mA |  *None* |

![](https://github.com/nardoz-dev/LiVeSe/blob/main/docs/sharedpictures/battery_management.jpg)

Of course to gain a more efficent misuration about power energy will can use a specific tool like ammeter that we can misurate the powersupply on the device.  The board include a special pin like : Jumper JP5, labeled IDD, is used to measure the STM32 microcontroller consumption by removing the jumper and by connecting an ammeter:
- JP5 ON: STM32 is powered (default)
- JP5 OFF: an ammeter must be connected to measure the STM32 current. If there is no ammeter, the STM32 is not powered

### Evaluation of end-user experience
We focus on effectiveness of service and knowledge extrapolated
1. We want to create a secure path through an urban area
2. light and croud as indicator of security instead of obscure and not populated side streets
3. Density of pubs, bars and restaurants as synonimus of secure

> Idea of "More people and light implies more secure areas" is effective? 
> Can We measure Safety of roads through Ambiental Sensors and density of Points of interests in the area?

[^1]: The example is based on random value.
