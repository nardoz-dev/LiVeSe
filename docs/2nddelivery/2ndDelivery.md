## Addressing comments from 1th delivery

At the end of the first delivery we received the following comments :

1.  The connection of security to lights, sounds and "Peoples" should be better supported
      -  How do you realize whether indeed people consider the environment safer?
      -  Infrared use is interesting, but you never mention that the number of people is a key metric ...
2. The algorithm that classifies the streets based on the input was not presented properly
3. You show components, but they should be connected to have a reference architecture
4. What are the requirements in terms of operation time and consequently consumption 

### We address them as following: 

1. We explicit the connection between the problem of safety, what type of data we want to collect and finally the use of Survey in order to collect opinions from people and understand if sampled data will be relevant or not
2. We explicit requirements to address during the development as well as decisions taken
3. We define high level Logic and what Cloud services we want to integrate in our System : Google Maps and AWS Analytic
4. We Create our wiring architecture using [fritzing](https://fritzing.org/) tool
5. We address requirements and consumption in Evaluation doc. Showing problems encountered 

## Changes in the Concept and Evaluation

We understand our initial mistakes and addressed suggestions after the first delivery.

We correct our concept through a more explicit and *clear documentation*. We explicit intelligence expected and key metrics

As consequence, we define more clearly *our requirements and logic* of computation as well as the *wiring architecture* of our device

Finally, we dealt with the evaluation of power consumption trying *many approaches* in order to retrieve *the most reliable estimate possible*. Unfortunately we ran into difficulties

## Technical Work

Since the first delivery we focus our efforts on :
- define logic of devices
  - weight of measured quantity
- sample strategy adopted
  - duty cycle and sleep time 
- wire and test all sensors  
  - problems encountered with microphone (ky-037)
  - problems encountered with ADC line of Lora Discovery board 
- start integration with the things network and AWS services
  - connectivity between end device and AWS
- evaluation of energy consumption 
  - FIT iot lab
  - Ammeter tests

## Missing Functionalities for 3th Delivery  

- data Visualization via web dashboard 
- complete integration with AWS and Google maps APIs

## Evaluation progress and expected for 3th Delivery

- we evaluate power consumption of the sensors with different approaches 
- we evaluate possible sample frequencies related to the power consumption
- we evaluate quality of sensors in order to be effective for our measurement
- we evaluate logic and wiring of our device

For our end delivery we will focus on :

- a more reliable way to evaluate energy consumption of our device
- define an optimal sample frequency and related sleep-active cycle
- test if event-based wake-up of devices is efficient for define sleep-active cycle
- include stepper motor and test improvements of PIR sensor
- complete our development on the Lora Discovery kit and finalize our tests 

Lastly we will test our network performance and integration with Cloud services as soon as possible.

