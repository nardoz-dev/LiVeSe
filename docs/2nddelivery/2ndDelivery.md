## Addressing comments from 1th delivery

At the end of the first delivery we received the following comments :

1.  the connection of security to lights, sounds and "Peoples" should be better supported
      -  How do you realize whether indeed people consider the environment safer?
      -  infrared use is interesting, but you never mention that the number of people is a key metric ...
2. The algorithm that classifies the streets based on the input was not presented properly
3. You show components, but they should be connected to have a reference architecture
4. What are the requirements in terms of operation time and consequently consumption 

### We address them as following: 

1. We make explicit connection between the problem of safety, what type of data we want to collect and finally the use of Survey in order to understand opinions from other people about how our data will be relevant or not
2. We define high level Logic and Cloud services we want to integrate in our System as Google Maps and AWS Analytic
3. We Create our wiring architecture using [fritzing](https://fritzing.org/) tool
4. We address requirements and consumption in Evaluation doc. Showing problems encountered 

## Changes in the Concept and Evaluation

We understand our initial mistakes and correct our ideas about concept through a more explicit and clear documentation and presentation. As consequence, we dealt with the evaluation trying many approaches in order to be as precise as possible. Unfortunately we ran into difficulties.

## Technical Work

Since the first delivery we focus our efforts on :
- define logic and code of devices
  - weight of measured quantity
  - duty cycle and sleep time 
- wire and test all sensors  
  - problems encountered with microphone (ky-037)
  - problems encountered with ADC line of Lora Discovery board 
- start integration with the things network and AWS services
  - sending and receive data
  - test connectivity between end device and AWS
- experimentation and evaluation of energy consumption 
  - FIT iot lab and Ammeter tests

## 3th Delivery Roadmap 

- resolve Problem related to ADC line of Lora Discovery board
- find better microphone 
- define optimal sample frequency and related sleep-active cycle
- include servomotor and test improvements of PIR sensor
- address evaluation of consumption with working ammeter
- complete integration with AWS and GOOGLE maps APIs
- create web dashboard 

## Evaluation since 1th delivery and expected for 3th Delivery

- we evaluate power consumption of the sensors with different approaches 
- we evaluate possible sample frequencies related to the power consumption
- we evaluate quality of sensors in order to be effective for our measurement
- we evaluate logic and wiring of our device

We expect to test our network performance and integration with Cloud services as soon as possible.

We will focus on a more precise way to evaluate our energy consumption and explore other ways to recharge batteries 

Lastly we want to optimize as much as possible the code of devices in order to be efficient


