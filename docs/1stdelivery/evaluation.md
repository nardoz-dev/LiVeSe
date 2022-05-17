# Evaluation

The goal of this document is providing information about "evalutation" of Project. This evaluation is based on the follow constraints:
  - The evaluation of the performance of the network technologies.
  - The evaluation of the performance of the embedded devices in terms of power consumption and energy efficiency.
  - The evaluation of the response time from an end-user point of view.

## Performance Evaluation

Performance evaluation mainly concerns two aspects: evaluation of the performance of the cloud infrastructure and evaluation for the physical characteristics of the devices.

### Network Evaluation

#### LoRa

We provide the use of this tools : [`AirTime calculator`](https://avbentem.github.io/airtime-calculator/ttn/eu868/51) for LoRaWAN to calculate and optimize our airtime for a longer battery life and less gateway utilization.

> *Ipotethical tool test results *[^1]*:*
> ![](https://github.com/nardoz-dev/projectName/blob/main/docs/sharedpictures/1_LoraToolTest.png)

#### AWS
> Amount of Data collected, data rates exchanges with cloud platform and related Cost 

#### Devices

> Node computation of instant data and subsequent sent,
> packets lost/data Rate and Antenna Consumption.

### Power consuming and energy efficiency

Station power constraints:



Each devices drains energy from the battery so we must try to lighten as much as possible the workload on the station to avoid power overcharging.
This can be correctly done calculating sensing and sending times. 
Given that the station needs more or less 5Volt on input: fewer detections possible, fewer deliveries possible, lower will be the consumption
To be on.

| **Products** | **Power Consume on Active** | **Power Consume on Idle** |
| :---: | :---: | :---: |
| `Nucleo -f401re` | 300mA max | 100mA |
| `Infrared ZTP-135BS` | 0.45mA | 0.27mA |
| `SoundSensors TS-US-115-CA` | 4~5 mA | 4~5 mA |
| `Antenna` | 500mA |  *None* |

![](https://github.com/nardoz-dev/LiVeSe/blob/main/docs/sharedpictures/1_BatteryManagement.jpg)

Of course to gain a more efficent misuration about power energy will can use a specific tool like ammeter that we can misurate the powersupply on the device.  The board include a special pin like : Jumper JP5, labeled IDD, is used to measure the STM32 microcontroller consumption by removing the jumper and by connecting an ammeter:
- JP5 ON: STM32 is powered (default)
- JP5 OFF: an ammeter must be connected to measure the STM32 current. If there is no ammeter, the STM32 is not powered

### Evaluation of end-user experience
We focus on effectiveness of service and quality of knowledge extrapolated
1. We want to create a secure path through an urban area
2. we want to show a clear view of the state of urban Areas
3. light,loudness and volume of people passing as indicator of safety instead of obscure,quite and not very populated side streets

- Idea of "More people and light implies more secure areas" is effective?
- Are Density of pubs, bars and restaurants synonimus of safety?
- Can We measure Safety of Urban Areas through Ambiental Sensors and density of Points of interests in that area?

[^1]: The example is based on random value.
